#ifndef FTN_H_
#define FTN_H_

#include <Domi_MDVector.hpp>
#include <Domi_Slice.hpp>
#include <Domi_MDArrayView.hpp>
#include <Domi_MDArrayRCP.hpp>
#include <Tpetra_DefaultPlatform.hpp>
#include <Teuchos_RCP.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <sstream>

// Namespace of the Fortran emulator - ftn
namespace ftn
{
using Domi::MDComm;
using Domi::MDMap;
using Domi::MDVector;
using Domi::MDArrayView;
using Domi::MDArrayRCP;
using Teuchos::Comm;
using Teuchos::SerialComm;
using Teuchos::RCP;
using Teuchos::rcp;
using Teuchos::tuple;
typedef Domi::dim_type dim_type; // Define dim_type as a shorthand for Domi::dim_type
static const dim_type Dynamic = Domi::Slice::Default; // Create new keyword "Dynamic" for array operation emulation.

/* Class span
 * Inherits: Domi::Slice
 *
 * Fortran-like emulator of Domi::Slice better suited for variable lower bounds and slicing.
 */
class span: public Domi::Slice
{
public:
	span () :
			Domi::Slice(Dynamic, Dynamic)
	{
	}
	span (dim_type length) :
			Domi::Slice(Dynamic, length)
	{
	}
	span (dim_type beginIndex, dim_type endIndex) :
			Domi::Slice(beginIndex, endIndex)
	{
	}
	span (dim_type beginIndex, dim_type endIndex, dim_type stride) :
			Domi::Slice(beginIndex, endIndex, stride)
	{
	}
};
// Class span

template<class Derived, class Scalar>
class ArrayBase;

template<class Scalar>
class Array : public ArrayBase<Array<Scalar>, Scalar>
{
private:
	bool isAllocated;
	std::vector<dim_type> beginIndices;
	std::vector<dim_type> endIndices;
	MDArrayRCP<Scalar> mdArray;

	dim_type findInitializationValues (dim_type initVal);
	dim_type findInitializationValues (span initVal);

	void indexOutOfBounds (dim_type index, int dimNumber) const;

public:

	template<class Derived>
	Array (ArrayBase<Derived, Scalar> const& array);

	Array (dim_type initVal);

	Scalar operator() (dim_type index) const;
	Scalar& operator() (dim_type index);

	int numDims () const;

	Array<dim_type> shape () const;

	size_t size () const;
	size_t size (size_t dimNumber) const;

	Array& operator= (const Scalar& x);

	std::string toString() const;
};
// Class Array

/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 * OPERATORS
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */

template<class Derived, class OtherDerived, class Scalar>
class ArraySum : public ArrayBase<ArraySum<Derived, OtherDerived, Scalar>, Scalar>
{
private:
	Derived first;
	OtherDerived second;
public:
	ArraySum(ArrayBase<Derived, Scalar> const& a, ArrayBase<OtherDerived, Scalar> const& b) : first(a), second(b) {}
	size_t size () const {return first.size();}
	size_t size (size_t dimNumber) const {return first.size(dimNumber);}
	int numDims () const {return first.numDims();}
	Scalar operator() (dim_type i) const { return first(i) + second(i); }
};

template<class Derived, class OtherDerived, class Scalar>
ArraySum<Derived, OtherDerived, Scalar> const operator+ (ArrayBase<Derived, Scalar> const& a, ArrayBase<OtherDerived, Scalar> const& b)
{
	return ArraySum<Derived, OtherDerived, Scalar>(a,b);
}

/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 * ArrayBase
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */
template<class Derived, class Scalar>
class ArrayBase
{
public:
	size_t size () const
	{
		return static_cast<Derived const&>(*this).size();
	}
	size_t size (size_t dimNumber) const
	{
		return static_cast<Derived const&>(*this).size(dimNumber);
	}
	Scalar operator() (dim_type index) const
	{
		return static_cast<Derived const&>(*this)(index);
	}
	Scalar& operator() (dim_type index)
	{
		return static_cast<Derived&>(*this)(index);
	}
	Array<dim_type> shape () const
	{
		return static_cast<Derived const&>(*this).shape();
	}
	int numDims () const
	{
		return static_cast<Derived const&>(*this).numDims();
	}
	std::string toString () const
	{
		return static_cast<Derived const&>(*this).toString();
	}

	operator Derived& ()
	{
		return static_cast<Derived&>(*this);
	}
	operator Derived const& () const
	{
		return static_cast<const Derived&>(*this);
	}

	template<class T1, class T2>
	friend std::ostream& operator<< (std::ostream & os, const ArrayBase<T1, T2>& arr);
};

template<class Derived, class Scalar>
std::ostream& operator<< (std::ostream & os, const ArrayBase<Derived, Scalar>& arr)
{
	os << arr.toString();
	return os;
}

/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 * IMPLEMENTATIONS: Class ftn::Array
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */


template<class Scalar>
Array<Scalar>::Array (dim_type initVal)
{
	beginIndices.reserve(1);
	endIndices.reserve(1);
	dim_type initLength = findInitializationValues(initVal);

	if (initLength == 0)
	{
		isAllocated = false;
	}
	else
	{
		isAllocated = true;
	}

	mdArray = MDArrayRCP<Scalar>(tuple(initLength)); // Alustaa alkiot!
}

template<class Scalar>
template<class Derived>
Array<Scalar>::Array (ArrayBase<Derived, Scalar> const& array)
{
	isAllocated = true;
	int nDims = array.numDims();
	beginIndices.assign(nDims, 1);
	endIndices.reserve(nDims);

	for (int i = 0; i < nDims; i++)
	{
		endIndices[i] = array.size(i + 1);
	}

	dim_type length = array.size();
	mdArray = MDArrayRCP<Scalar>(tuple(length)); // Alustaa alkiot!
	for (int i = 0; i < length; i++)
	{
		mdArray(i) = array(i+1);
	}
}

template<class Scalar>
int Array<Scalar>::numDims () const
{
	return beginIndices.size();
}

template<class Scalar>
Array<dim_type> Array<Scalar>::shape () const
{
	int n = numDims();
	Array<dim_type> shape(n);

	for (int i = 0; i < n; i++)
	{
		shape(i + 1) = endIndices[i] - beginIndices[i] + 1;
	}

	return shape;
}

template<class Scalar>
std::string Array<Scalar>::toString() const
{
	return mdArray.toString();
}

template<class Scalar>
dim_type Array<Scalar>::findInitializationValues (dim_type initVal)
{
	beginIndices.push_back(1);
	if (initVal == Dynamic)
	{
		endIndices.push_back(Dynamic);
		return 0;
	}
	else
	{
		endIndices.push_back(initVal);
		return initVal;
	}
}

template<class Scalar>
dim_type Array<Scalar>::findInitializationValues (span initVal)
{
	if (initVal.stop() == Dynamic)
	{
		endIndices.push_back(Dynamic);
		if (initVal.start() != Dynamic)
			beginIndices.push_back(initVal.start());
		else
			beginIndices.push_back(1);
		return 0;
	}
	else
	{
		dim_type length;
		if (initVal.start() != Dynamic)
		{
			beginIndices.push_back(initVal.start());
			length = initVal.stop() - initVal.start() + 1;
			endIndices.push_back(initVal.start() + length - 1);
		}
		else
		{
			beginIndices.push_back(1);
			length = initVal.stop();
			endIndices.push_back(length);
		}
		return length;
	}
}

template<class Scalar>
void Array<Scalar>::indexOutOfBounds (dim_type index, int dimNumber) const
{
	if (index < beginIndices[dimNumber] || index > endIndices[dimNumber])
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << beginIndices[dimNumber] << ", " << endIndices[dimNumber] << "]!";
		throw std::out_of_range(strStream.str());
	}
}

template<class Scalar>
Scalar Array<Scalar>::operator() (dim_type index) const
{
#ifdef FTN_DEBUG
	indexOutOfBounds(index, 0);
#endif
	return mdArray(index - beginIndices[0]);
}

template<class Scalar>
Scalar& Array<Scalar>::operator() (dim_type index)
{
#ifdef FTN_DEBUG
	indexOutOfBounds(index, 0);
#endif
	return mdArray(index - beginIndices[0]);
}

template<class Scalar>
size_t Array<Scalar>::size () const
{
	return mdArray.size();
}

template<class Scalar>
size_t Array<Scalar>::size (size_t dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "Argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return endIndices[dimNumber - 1] - beginIndices[dimNumber - 1] + 1;
}

template<class Scalar>
Array<Scalar>& Array<Scalar>::operator= (const Scalar& x)
{
	mdArray.assign(x);
	return *this;
}

} // namespace ftn

#endif /* FTN_H_ */
