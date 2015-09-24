#ifndef FTN_ARRAYIMPLEMENTATIONS_H_
#define FTN_ARRAYIMPLEMENTATIONS_H_
#include "ftn_Array.h"
#include "ftn_nonMemberFunctions.h"

namespace ftn
{

template<class Scalar>
template<class T1, class... OtherTypes>
Array<Scalar>::Array (T1 m, OtherTypes... otherInitVals)
{
	constexpr int nDims = 1 + sizeof...(OtherTypes);
	isAllocated = true;
	beginIndices.reserve(nDims);

	dim_type dimLengths[nDims] = {findInitializationValues(m), (findInitializationValues(otherInitVals))...};

	Teuchos::ArrayView<dim_type> d(&dimLengths[0], nDims);
	mdArray = std::move(MDArrayRCP<Scalar>(d, Domi::FORTRAN_ORDER));
}

template<class Scalar>
template<class Derived, class Scalar2>
Array<Scalar>::Array (ArrayBase<Derived, Scalar2> const& array)
{
	isAllocated = true;
	int nDims = array.numDims();
	beginIndices.reserve(nDims);
	std::vector<dim_type> dimLengths;

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
Array<Scalar>::Array (Array<Scalar>& array)
{
	isAllocated = true;
	int nDims = array.numDims();
	beginIndices.reserve(nDims);
	std::vector<dim_type> dimLengths;

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
Array<Scalar>::Array (Array<Scalar> && other) noexcept
{
	isAllocated = true;
	beginIndices.assign(other.numDims(), 1);
	mdArray = std::move(other.mdArray);
}

template<class Scalar>
Array<Scalar>& Array<Scalar>::operator= (Array<Scalar> && other) noexcept
{
#ifdef FTN_DEBUG
	if (numDims() != other.numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to assign array of dimension: " << other.numDims() << " into array of dimension: " << numDims();
		throw std::domain_error(strStream.str());
	}
#endif
	if (!isAllocated || !sameShape(*this, other))
	{
		int nDims = other.numDims();
		beginIndices.assign(nDims, 1);

		Teuchos::ArrayView<dim_type> dims(other.mdArray.dimensions().view());
		if (isAllocated)
			mdArray.resize(dims);
		else
			mdArray = MDArrayRCP<Scalar>(dims, Domi::FORTRAN_ORDER);

		isAllocated = true;
	}

	mdArray = std::move(other.mdArray);

	return *this;
}

template<class Scalar>
template<class Derived, class Scalar2>
Array<Scalar>& Array<Scalar>::operator= (ArrayBase<Derived, Scalar2> const& array)
{
#ifdef FTN_DEBUG
	if (numDims() != array.numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to assign array of dimension: " << array.numDims() << " into array of dimension: " << numDims();
		throw std::domain_error(strStream.str());
	}
#endif

	std::vector<dim_type> dimLengths;
	if (!isAllocated || !(sameShape(*this, array)))
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
		shape(i + 1) = mdArray.dimension(i);
	}

	return shape;
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
		return 0;
		isAllocated = false;
	}
	else
	{
#ifdef FTN_DEBUG
		checkNonNegativeConstructLength(initVal);
#endif
		if (initVal == 0) isAllocated = false;
		return initVal;
	}
}

template<class Scalar>
dim_type Array<Scalar>::findInitializationValues (span initVal)
{
	if (initVal.stop() == Dynamic)
	{
		if (initVal.start() != Dynamic)
			beginIndices.push_back(initVal.start());
		else
			beginIndices.push_back(1);
		isAllocated = false;
		return 0;
	}
	else
	{
		dim_type length;
		if (initVal.start() != Dynamic)
		{
			beginIndices.push_back(initVal.start());
			length = initVal.stop() - initVal.start() + 1;
		}
		else
		{
			beginIndices.push_back(1);
			length = initVal.stop();
		}
#ifdef FTN_DEBUG
		checkNonNegativeConstructLength(length);
#endif
		if (length == 0) isAllocated = false;
		return length;
	}
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

template<class Scalar>
Array<dim_type> Array<Scalar>::lbound () const
{
	int n = numDims();
	Array<dim_type> lbounds(n);
	for (int i = 1; i <= n; i++)
	{
		lbounds(i) = lbound(i);
	}
	return lbounds;
}

template<class Scalar>
void Array<Scalar>::indexOutOfBounds (dim_type index, int dimNumber) const
{
	if (index < lbound(dimNumber) || index > ubound(dimNumber))
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << lbound(dimNumber) << ", " << ubound(dimNumber) << "]!";
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
	indexOutOfBounds(index, 1);
#endif
	return mdArray(index - beginIndices[0]);
}

template<class Scalar>
Scalar& Array<Scalar>::operator() (dim_type index)
{
#ifdef FTN_DEBUG
	indexOutOfBounds(index, 1);
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
	return mdArray.dimension(dimNumber - 1);
}

template<class Scalar>
dim_type Array<Scalar>::ubound (dim_type dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "Argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return beginIndices[dimNumber - 1] + mdArray.dimension(dimNumber - 1) - 1;
}

template<class Scalar>
Array<dim_type> Array<Scalar>::ubound () const
{
	int n = numDims();
	Array<dim_type> ubounds(n);

	for (int i = 1; i <= n; i++)
	{
		ubounds(i) = ubound(i);
	}

	return ubounds;
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
