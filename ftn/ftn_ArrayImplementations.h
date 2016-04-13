#ifndef FTN_ARRAYIMPLEMENTATIONS_H_
#define FTN_ARRAYIMPLEMENTATIONS_H_
#include "ftn_Array.h"
#include "ftn_nonMemberFunctions.h"

namespace ftn
{

template<class Scalar, int nDims, bool isAllocatable>
template<class T1, class ... OtherTypes>
Array<Scalar, nDims, isAllocatable>::Array(T1 m, OtherTypes ... otherInitVals)
{
	static_assert(!isFtnType<T1>::value && nDims == (1 + sizeof...(otherInitVals)), "Dimension specification template parameter must equal the number of constructor arguments!");
	static_assert(!isFtnType<T1>::value && nDims <= maxDims, "Ftn only supports arrays of dimension <= 4!");

	_isAllocated = true;

	_dimCounter = 0;
	_dimLengths =
	{	findInitializationValues(m), (findInitializationValues(otherInitVals))...};
	_dimCounter = 0;
	size_t numel = std::accumulate(_dimLengths.begin(),
			_dimLengths.begin() + nDims, 1, std::multiplies<size_t>());
	//std::cout << _dimLengths[1] << std::endl;

	_strides = computeArrayStrides(_dimLengths);

	_mdArray = new Scalar[numel];
	_numel = numel;
}

template<class Scalar, int nDims, bool isAllocatable>
template<class Derived, class Scalar2>
Array<Scalar, nDims, isAllocatable>::Array(ArrayBase<Derived, Scalar2> const& array) :
		_dimCounter(0)
{
	_isAllocated = true;

	for (int i = 1; i <= nDims; i++)
	{
		_beginIndices[i - 1] = (array.lbound(i));
		_dimLengths[i - 1] = (array.size(i));
	}

	_strides = computeArrayStrides(_dimLengths);

	_numel = array.size();
	Scalar* newArray = new Scalar[_numel];
	delete[] _mdArray;
	_mdArray = newArray;

	if (!array.isArrayView())
	{
		size_t length = array.size();
		for (size_t i = 0; i < length; i++)
		{
			_mdArray[i] = array.linear(i);
		}
	}
	else // ArrayViews do not provide a linear operator.
	{
		// These if-clauses will be optimized away at compile time.
		if (nDims == 1)
		{
			dim_type len1 = array.size(1);
			for (dim_type m = 0; m < len1; m++)
				zb(m) = array.zb(m);
		}
		else if (nDims == 2)
		{
			dim_type len1 = array.size(1);
			dim_type len2 = array.size(2);
			for (dim_type n = 0; n < len2; n++)
				for (dim_type m = 0; m < len1; m++)
					zb(m, n) = array.zb(m, n);
		}
		else if (nDims == 3)
		{
			dim_type len1 = array.size(1);
			dim_type len2 = array.size(2);
			dim_type len3 = array.size(3);
			for (dim_type o = 0; o < len3; o++)
				for (dim_type n = 0; n < len2; n++)
					for (dim_type m = 0; m < len1; m++)
						zb(m, n, o) = array.zb(m, n, o);
		}
		else if (nDims == 4)
		{
			dim_type len1 = array.size(1);
			dim_type len2 = array.size(2);
			dim_type len3 = array.size(3);
			dim_type len4 = array.size(4);
			for (dim_type p = 0; p < len4; p++)
				for (dim_type o = 0; o < len3; o++)
					for (dim_type n = 0; n < len2; n++)
						for (dim_type m = 0; m < len1; m++)
							zb(m, n, o, p) = array.zb(m, n, o, p);
		}
	}
}

template<class Scalar, int nDims, bool isAllocatable>
Array<Scalar, nDims, isAllocatable>::Array(Array<Scalar, nDims, isAllocatable>& array) :
		_dimCounter(0)
{
	_isAllocated = true;

	for (int i = 1; i <= nDims; i++)
	{
		_beginIndices[i - 1] = (array.lbound(i));
		_dimLengths[i - 1] = push_back(array.size(i));
	}

	_strides = computeArrayStrides(_dimLengths);

	_numel = array.size();
	Scalar* newArray = new Scalar[_numel];
	delete[] _mdArray;
	_mdArray = newArray;

	size_t length = array.size();
	for (size_t i = 0; i < length; i++)
	{
		_mdArray[i] = array.linear(i);
	}

}

template<class Scalar, int nDims, bool isAllocatable>
Array<Scalar, nDims, isAllocatable>::Array(Array<Scalar, nDims, isAllocatable> && other) noexcept : _dimCounter(0)
{
	_isAllocated = true;
	_dimLengths = std::move(other._dimLengths);
	_strides = std::move(other._strides);
	_beginIndices.fill(1);
	_numel = other._numel;
	_mdArray = other._mdArray;
	other._mdArray = nullptr;
}

template<class Scalar, int nDims, bool isAllocatable>
Array<Scalar, nDims, isAllocatable>& Array<Scalar, nDims, isAllocatable>::operator=(
		Array<Scalar, nDims, isAllocatable> && other) noexcept
{
#ifdef FTN_DEBUG
	if (numDims() != other.numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to assign array of dimension: " << other.numDims() << " into array of dimension: " << numDims();
		throw std::domain_error(strStream.str());
	}
#endif
	if (isAllocatable && (!_isAllocated || !sameShape(*this, other)))
	{
		_beginIndices.fill(1);
		_dimLengths = std::move(other._dimLengths);
		_strides = std::move(other._strides);

		_isAllocated = true;
		_numel = other._numel;
	}

	_mdArray = other._mdArray;
	other._mdArray = nullptr;

	return *this;
}

template<class Scalar, int nDims, bool isAllocatable>
template<class Derived, class Scalar2>
inline Array<Scalar, nDims, isAllocatable>& Array<Scalar, nDims, isAllocatable>::operator=(
		ArrayBase<Derived, Scalar2> const& array)
{
#ifdef FTN_DEBUG
	if (numDims() != array.numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to assign array of dimension: " << array.numDims() << " into array of dimension: " << numDims();
		throw std::domain_error(strStream.str());
	}
#endif

	if (isAllocatable && (!_isAllocated || !sameShape(*this, array)))
	{
		for (int i = 1; i <= nDims; i++)
		{
			_beginIndices[i - 1] = array.lbound(i);
			_dimLengths[i - 1] = array.size(i);
		}

		_numel = array.size();
		Scalar* newArray = new Scalar[_numel];
		delete[] _mdArray;
		_mdArray = newArray;

		_strides = computeArrayStrides(_dimLengths);

		_isAllocated = true;
	}

	if (!array.isArrayView())
	{
		size_t length = array.size();
		for (size_t i = 0; i < length; i++)
		{
			_mdArray[i] = array.linear(i);
		}
	}
	else // ArrayViews do not provide a linear operator.
	{
		// These if-clauses will be optimized away at compile time.
		if (nDims == 1)
		{
			dim_type len1 = array.size(1);
			for (dim_type m = 0; m < len1; m++)
				zb(m) = array.zb(m);
		}
		else if (nDims == 2)
		{
			dim_type len1 = array.size(1);
			dim_type len2 = array.size(2);
			for (dim_type n = 0; n < len2; n++)
				for (dim_type m = 0; m < len1; m++)
					zb(m, n) = array.zb(m, n);
		}
		else if (nDims == 3)
		{
			dim_type len1 = array.size(1);
			dim_type len2 = array.size(2);
			dim_type len3 = array.size(3);
			for (dim_type o = 0; o < len3; o++)
				for (dim_type n = 0; n < len2; n++)
					for (dim_type m = 0; m < len1; m++)
						zb(m, n, o) = array.zb(m, n, o);
		}
		else if (nDims == 4)
		{
			dim_type len1 = array.size(1);
			dim_type len2 = array.size(2);
			dim_type len3 = array.size(3);
			dim_type len4 = array.size(4);
			for (dim_type p = 0; p < len4; p++)
				for (dim_type o = 0; o < len3; o++)
					for (dim_type n = 0; n < len2; n++)
						for (dim_type m = 0; m < len1; m++)
							zb(m, n, o, p) = array.zb(m, n, o, p);
		}
	}

	return *this;
}

template<class Scalar, int nDims, bool isAllocatable>
Array<Scalar, nDims, isAllocatable>& Array<Scalar, nDims, isAllocatable>::operator=(
		Array<Scalar, nDims, isAllocatable>& array)
{
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>& arrayBaseInstance = array;
	this->operator=(arrayBaseInstance);
}

template<class Scalar, int nDims, bool isAllocatable>
int Array<Scalar, nDims, isAllocatable>::numDims() const
{
	return nDims;
}

template<class Scalar, int nDims, bool isAllocatable>
Array<dim_type, 1> Array<Scalar, nDims, isAllocatable>::shape() const
{
	Array<dim_type, 1> shape(nDims);

	for (int i = 0; i < nDims; i++)
	{
		shape(i + 1) = _dimLengths[i];
	}

	return shape;
}

template<class Scalar, int nDims, bool isAllocatable>
std::string Array<Scalar, nDims, isAllocatable>::toString() const
{
	std::ostringstream oss;
	if (_numel > 0)
		std::copy(_mdArray, _mdArray + _numel,
				std::ostream_iterator<Scalar>(oss, "    "));
	return oss.str();
}

template<class Scalar, int nDims, bool isAllocatable>
dim_type Array<Scalar, nDims, isAllocatable>::findInitializationValues(dim_type initVal)
{
	_beginIndices[_dimCounter] = 1;
	if (initVal == Dynamic)
	{
		_isAllocated = false;
		_dimCounter++;
		return 0;
	}
	else
	{
		if (initVal < 0)
			initVal = 0;
		if (initVal == 0)
			_isAllocated = false;
		_dimCounter++;
		return initVal;
	}
}

template<class Scalar, int nDims, bool isAllocatable>
dim_type Array<Scalar, nDims, isAllocatable>::findInitializationValues(span initVal)
{
	if (initVal.stop() == Dynamic)
	{
		if (initVal.start() != Dynamic)
			_beginIndices[_dimCounter] = (initVal.start());
		else
			_beginIndices[_dimCounter] = (1);
		_isAllocated = false;
		_dimCounter++;
		return 0;
	}
	else
	{
		dim_type length;
		if (initVal.start() != Dynamic)
		{
			if (initVal.start() <= initVal.stop())
			{
				_beginIndices[_dimCounter] = (initVal.start());
				length = initVal.stop() - initVal.start() + 1;
			}
			else
			{
				_beginIndices[_dimCounter] = (1);
				length = 0;
			}
		}
		else
		{
			_beginIndices[_dimCounter] = (1);
			if (initVal.stop() >= 0)
			{
				length = initVal.stop();
			}
			else
			{
				length = 0;
			}
		}
		if (length == 0)
			_isAllocated = false;
		_dimCounter++;
		return length;
	}
}

template<class Scalar, int nDims, bool isAllocatable>
dim_type Array<Scalar, nDims, isAllocatable>::lbound(dim_type dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "lbound argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return _beginIndices[dimNumber - 1];
}

template<class Scalar, int nDims, bool isAllocatable>
Array<dim_type, 1> Array<Scalar, nDims, isAllocatable>::lbound() const
{
	Array<dim_type, 1> lbounds(nDims);
	for (int i = 1; i <= nDims; i++)
	{
		lbounds(i) = lbound(i);
	}
	return lbounds;
}

template<class Derived, class Scalar>
void ArrayNonConstBase<Derived, Scalar>::indexOutOfBounds(dim_type index,
		int dimNumber) const
{
	if (index < lbound(dimNumber) || index > ubound(dimNumber))
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << lbound(dimNumber)
				<< ", " << ubound(dimNumber) << "]!";
		throw std::out_of_range(strStream.str());
	}
}

template<class Derived, class Scalar>
void ArrayNonConstBase<Derived, Scalar>::linearIndexOutOfBounds(
		size_t index) const
{
	if (index < (size_t) 0 || index > size() - 1)
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << 0 << ", "
				<< size() - 1 << "]!";
		throw std::out_of_range(strStream.str());
	}
}

template<class Derived, class Scalar>
void ArrayNonConstBase<Derived, Scalar>::wrongDimension(int dimNum) const
{
	if (dimNum != numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to access array of dimension " << numDims()
				<< " by providing " << dimNum << " arguments to operator()!";
		throw std::out_of_range(strStream.str());
	}
}

//template<class Scalar, int nDims, bool isAllocatable>
//Scalar Array<Scalar, nDims, isAllocatable>::operator() (dim_type index) const
//{
//#ifdef FTN_DEBUG
//	indexOutOfBounds(index, 1);
//#endif
//	return mdArray(index - beginIndices[0]);
//}
//
//template<class Scalar, int nDims, bool isAllocatable>
//Scalar& Array<Scalar, nDims, isAllocatable>::operator() (dim_type index)
//{
//#ifdef FTN_DEBUG
//	indexOutOfBounds(index, 1);
//#endif
//	return mdArray(index - beginIndices[0]);
//}

template<class Scalar, int nDims, bool isAllocatable>
Scalar Array<Scalar, nDims, isAllocatable>::zb(dim_type m) const
{
	return _mdArray[m];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar Array<Scalar, nDims, isAllocatable>::zb(dim_type m, dim_type n) const
{
	return _mdArray[m + n * _strides[1]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar Array<Scalar, nDims, isAllocatable>::zb(dim_type m, dim_type n, dim_type o) const
{
	return _mdArray[m + n * _strides[1] + o * _strides[2]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar Array<Scalar, nDims, isAllocatable>::zb(dim_type m, dim_type n, dim_type o,
		dim_type p) const
{
	return _mdArray[m + n * _strides[1] + o * _strides[2] + p * _strides[3]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar& Array<Scalar, nDims, isAllocatable>::zb(dim_type m)
{
	return _mdArray[m];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar& Array<Scalar, nDims, isAllocatable>::zb(dim_type m, dim_type n)
{
	return _mdArray[m + n * _strides[1]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar& Array<Scalar, nDims, isAllocatable>::zb(dim_type m, dim_type n, dim_type o)
{
	return _mdArray[m + n * _strides[1] + o * _strides[2]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar& Array<Scalar, nDims, isAllocatable>::zb(dim_type m, dim_type n, dim_type o, dim_type p)
{
	return _mdArray[m + n * _strides[1] + o * _strides[2] + p * _strides[3]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar Array<Scalar, nDims, isAllocatable>::operator()(dim_type m) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::wrongDimension(1);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(m, 1);
#endif
	return _mdArray[m - _beginIndices[0]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar Array<Scalar, nDims, isAllocatable>::operator()(dim_type m, dim_type n) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::wrongDimension(2);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(n, 2);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar Array<Scalar, nDims, isAllocatable>::operator()(dim_type m, dim_type n,
		dim_type o) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::wrongDimension(3);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(o, 3);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]
			+ (o - _beginIndices[2]) * _strides[2]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar Array<Scalar, nDims, isAllocatable>::operator()(dim_type m, dim_type n, dim_type o,
		dim_type p) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::wrongDimension(4);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(o, 3);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(p, 4);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]
			+ (o - _beginIndices[2]) * _strides[2]
			+ (p - _beginIndices[3]) * _strides[3]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar& Array<Scalar, nDims, isAllocatable>::operator()(dim_type m)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::wrongDimension(1);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(m, 1);
#endif
	return _mdArray[m - _beginIndices[0]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar& Array<Scalar, nDims, isAllocatable>::operator()(dim_type m, dim_type n)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::wrongDimension(2);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(n, 2);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar& Array<Scalar, nDims, isAllocatable>::operator()(dim_type m, dim_type n, dim_type o)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::wrongDimension(3);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(o, 3);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]
			+ (o - _beginIndices[2]) * _strides[2]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar& Array<Scalar, nDims, isAllocatable>::operator()(dim_type m, dim_type n, dim_type o,
		dim_type p)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::wrongDimension(4);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(o, 3);
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::indexOutOfBounds(p, 4);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]
			+ (o - _beginIndices[2]) * _strides[2]
			+ (p - _beginIndices[3]) * _strides[3]];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar Array<Scalar, nDims, isAllocatable>::linear(size_t index) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::linearIndexOutOfBounds(index);
#endif
	return _mdArray[index];
}

template<class Scalar, int nDims, bool isAllocatable>
Scalar& Array<Scalar, nDims, isAllocatable>::linear(size_t index)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::linearIndexOutOfBounds(index);
#endif
	return _mdArray[index];
}

template<class Scalar, int nDims, bool isAllocatable>
size_t Array<Scalar, nDims, isAllocatable>::size() const
{
	return _numel;
}

template<class Scalar, int nDims, bool isAllocatable>
size_t Array<Scalar, nDims, isAllocatable>::size(int dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "size argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return _dimLengths[dimNumber - 1];
}

template<class Scalar, int nDims, bool isAllocatable>
template<class OtherDimType, long unsigned int T>
size_t Array<Scalar, nDims, isAllocatable>::sub2ind(std::array<OtherDimType, T>& ind)
{
	size_t linearInd = 0;
	for (int i = 0; i < numDims(); i++)
	{
		linearInd += (ind[i] - _beginIndices[i]) * _strides[i];
	}
	return linearInd + 1;
}

template<class Scalar, int nDims, bool isAllocatable>
size_t Array<Scalar, nDims, isAllocatable>::linearStride(dim_type dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "linearStride argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return _strides[dimNumber - 1];
}

template<class Scalar, int nDims, bool isAllocatable>
dim_type Array<Scalar, nDims, isAllocatable>::ubound(dim_type dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "ubound argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return _beginIndices[dimNumber - 1] + _dimLengths[dimNumber - 1] - 1;
}

template<class Scalar, int nDims, bool isAllocatable>
Array<dim_type, 1> Array<Scalar, nDims, isAllocatable>::ubound() const
{
	int n = numDims();
	Array<dim_type, 1> ubounds(n);

	for (int i = 1; i <= n; i++)
	{
		ubounds(i) = ubound(i);
	}

	return ubounds;
}

template<class Scalar, int nDims, bool isAllocatable>
Array<Scalar, nDims, isAllocatable>::~Array()
{
	delete[] _mdArray;
}

template<class Scalar, int nDims, bool isAllocatable>
template<class Scalar2>
typename std::enable_if<!isFtnType<Scalar2>::value, Array<Scalar, nDims, isAllocatable> >::type& Array<
		Scalar, nDims, isAllocatable>::operator=(const Scalar2& x)
{
#ifdef FTN_DEBUG
	if (!_isAllocated)
	{
		std::ostringstream strStream;
		strStream << "Attempted to assign a value to an unallocated array!";
		throw std::logic_error(strStream.str());
	}
#endif
	for (size_t i = 0; i < _numel; i++)
		_mdArray[i] = x;
	return *this;
}

template<class Derived, class Scalar>
Array<dim_type, 1> ArrayNonConstBase<Derived, Scalar>::shape() const
{
	return static_cast<Derived const&>(*this).shape();
}

template<class Derived, class Scalar>
Array<dim_type, 1> ArrayBase<Derived, Scalar>::shape() const
{
	return static_cast<Derived const&>(*this).shape();
}

template<class Derived, class Scalar>
Array<dim_type, 1> ArrayNonConstBase<Derived, Scalar>::lbound() const
{
	return static_cast<Derived const&>(*this).lbound();
}

template<class Derived, class Scalar>
Array<dim_type, 1> ArrayBase<Derived, Scalar>::lbound() const
{
	return static_cast<Derived const&>(*this).lbound();
}

template<class Derived, class Scalar>
Array<dim_type, 1> ArrayNonConstBase<Derived, Scalar>::ubound() const
{
	return static_cast<Derived const&>(*this).ubound();
}

}

#endif /* FTN_ARRAYIMPLEMENTATIONS_H_ */
