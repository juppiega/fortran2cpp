#ifndef FTN_ARRAYIMPLEMENTATIONS_H_
#define FTN_ARRAYIMPLEMENTATIONS_H_
#include "ftn_Array.h"

/* TODO:
 *
 *
 */

namespace ftn
{
template<class Scalar>
Array<Scalar>::Array (dim_type initVal)
{
	beginIndices.reserve(1);
	dimLengths.reserve(1);
	dim_type initLength = findInitializationValues(initVal);
#ifdef FTN_DEBUG
	checkNonNegativeConstructLength(initLength);
#endif
	dimLengths.push_back(initLength);

	if (initLength == 0)
	{
		isAllocated = false;
	}
	else
	{
		isAllocated = true;
	}

	mdArray = MDArrayRCP<Scalar>(tuple(initLength), Domi::FORTRAN_ORDER);
}

template<class Scalar>
Array<Scalar>::Array (span initVal)
{
	beginIndices.reserve(1);
	dimLengths.reserve(1);
	dim_type initLength = findInitializationValues(initVal);
#ifdef FTN_DEBUG
	checkNonNegativeConstructLength(initLength);
#endif
	dimLengths.push_back(initLength);

	if (initLength == 0)
	{
		isAllocated = false;
	}
	else
	{
		isAllocated = true;
	}

	mdArray = MDArrayRCP<Scalar>(tuple(initLength), Domi::FORTRAN_ORDER);
}

template<class Scalar>
template<class Derived, class Scalar2>
Array<Scalar>::Array (ArrayBase<Derived, Scalar2> const& array)
{
	isAllocated = true;
	int nDims = array.numDims();
	beginIndices.reserve(nDims);
	dimLengths.reserve(nDims);

	for (int i = 1; i <= nDims; i++)
	{
		beginIndices.push_back(array.lbound(i));
		dimLengths.push_back(array.size(i));
	}

	Teuchos::ArrayView<dim_type> dims(dimLengths);
	mdArray = MDArrayRCP<Scalar>(dims, Domi::FORTRAN_ORDER);

	dim_type length = array.size();
	for (int i = 0; i < length; i++)
	{
		mdArray.arrayRCP()[i] = array.linear(i + 1);
	}
}

template<class Scalar>
template<class Derived, class Scalar2>
Array<Scalar>& Array<Scalar>::operator= (ArrayBase<Derived, Scalar2> const& array)
{
	if (numDims() != array.numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to assign array of dimension: " << array.numDims() << " into array of dimension: " << numDims();
		throw std::domain_error(strStream.str());
	}

	if (!isAllocated || !(sameShape(array)))
	{
		int nDims = array.numDims();
		beginIndices.resize(nDims);
		dimLengths.resize(nDims);

		for (int i = 1; i <= nDims; i++)
		{
			int a = array.lbound(i);
			int b = array.size(i);
			beginIndices[i - 1] = a;
			dimLengths[i - 1] = b;
		}

		Teuchos::ArrayView<dim_type> dims(dimLengths);
		if (isAllocated)
			mdArray.resize(dims);
		else
			mdArray = MDArrayRCP<Scalar>(dims, Domi::FORTRAN_ORDER);

		isAllocated = true;
	}

	dim_type length = array.size();
	for (int i = 0; i < length; i++)
	{
		mdArray.arrayRCP()[i] = array.linear(i + 1);
	}

	return *this;
}

template<class Scalar>
Array<Scalar>& Array<Scalar>::operator= (Array<Scalar>& array)
{
	ArrayNonConstBase<Array<Scalar>, Scalar>& arrayBaseInstance = array;
	this->operator=(arrayBaseInstance);
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
		shape(i + 1) = dimLengths[i];
	}

	return shape;
}

template<class Scalar>
Array<dim_type> Array<Scalar>::lbound () const
{
	int n = numDims();
	Array<dim_type> lbounds(n);

	for (int i = 0; i < n; i++)
	{
		lbounds(i + 1) = beginIndices[i];
	}

	return lbounds;
}

template<class Scalar>
std::string Array<Scalar>::toString () const
{
	return mdArray.toString();
}

template<class Scalar>
dim_type Array<Scalar>::findInitializationValues (dim_type initVal)
{
	beginIndices.push_back(1);
	if (initVal == Dynamic)
	{
		dimLengths.push_back(Dynamic);
		return 0;
	}
	else
	{
		dimLengths.push_back(initVal);
		return initVal;
	}
}

template<class Scalar>
dim_type Array<Scalar>::findInitializationValues (span initVal)
{
	if (initVal.stop() == Dynamic)
	{
		dimLengths.push_back(Dynamic);
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
			dimLengths.push_back(length);
		}
		else
		{
			beginIndices.push_back(1);
			length = initVal.stop();
			dimLengths.push_back(length);
		}
		return length;
	}
}

template<class Scalar>
void Array<Scalar>::indexOutOfBounds (dim_type index, int dimNumber) const
{
	dim_type upperBound = beginIndices[dimNumber] + dimLengths[dimNumber] - 1;
	if (index < beginIndices[dimNumber] || index > upperBound)
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << beginIndices[dimNumber] << ", " << upperBound << "]!";
		throw std::out_of_range(strStream.str());
	}
}

template<class Scalar>
void Array<Scalar>::linearIndexOutOfBounds (dim_type index) const
{
	if (index < 1 || index > mdArray.size())
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << 1 << ", " << mdArray.size() << "]!";
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
Scalar Array<Scalar>::linear (dim_type index) const
{
#ifdef FTN_DEBUG
	linearIndexOutOfBounds(index);
#endif
	return mdArray.arrayRCP()[index - 1];
}

template<class Scalar>
Scalar& Array<Scalar>::linear (dim_type index)
{
#ifdef FTN_DEBUG
	linearIndexOutOfBounds(index);
#endif
	return mdArray.arrayRCP()[index - 1];
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
	return dimLengths[dimNumber - 1];
}

template<class Scalar>
dim_type Array<Scalar>::lbound (dim_type dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "Argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return beginIndices[dimNumber - 1];
}

//template<class Scalar>
//template<class Derived, class Scalar2>
//void Array<Scalar>::reshape (ArrayBase<Derived, Scalar2> const& newDims)
//{
//	std::vector<dim_type> newDimVec;
//	dim_type n = newDims.numDims();
//	newDimVec.reserve(n);
//
//	for (int i = 0; i < n; i++)
//	{
//		newDimVec.push_back(newDims.linear(i + 1));
//	}
//
//	Teuchos::ArrayView<dim_type> t(newDimVec);
//	mdArray.resize(t);
//}

template<class Scalar>
template<class Derived, class Scalar2>
bool Array<Scalar>::sameShapeAndContents (ArrayBase<Derived, Scalar2> const& array) const
{
	return sameShape(array) && sameContents(array);
}

template<class Scalar>
template<class Derived, class Scalar2>
bool Array<Scalar>::sameContents (ArrayBase<Derived, Scalar2> const& array) const
{
	size_t n = size();
	if (n == array.size())
	{
		for (size_t i = 1; i <= n; i++)
		{
			int a = linear(i);
			int b = array.linear(i);
			if (linear(i) != array.linear(i)) return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<class Scalar>
template<class Derived, class Scalar2>
bool Array<Scalar>::sameShape (ArrayBase<Derived, Scalar2> const& array) const
{
	return shape().sameContents(array.shape());
}

template<class Scalar>
Array<Scalar>& Array<Scalar>::operator= (const Scalar& x)
{
	mdArray.assign(x);
	return *this;
}

template<class Derived, class Scalar>
Array<dim_type> ArrayNonConstBase<Derived, Scalar>::shape () const
{
	return static_cast<Derived const&>(*this).shape();
}

template<class Derived, class Scalar>
Array<dim_type> ArrayBase<Derived, Scalar>::shape () const
{
	return static_cast<Derived const&>(*this).shape();
}

template<class Derived, class Scalar>
Array<dim_type> ArrayNonConstBase<Derived, Scalar>::lbound () const
{
	return static_cast<Derived const&>(*this).lbound();
}

template<class Derived, class Scalar>
Array<dim_type> ArrayBase<Derived, Scalar>::lbound () const
{
	return static_cast<Derived const&>(*this).lbound();
}

}

#endif /* FTN_ARRAYIMPLEMENTATIONS_H_ */
