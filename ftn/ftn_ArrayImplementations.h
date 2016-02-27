#ifndef FTN_ARRAYIMPLEMENTATIONS_H_
#define FTN_ARRAYIMPLEMENTATIONS_H_
#include "ftn_Array.h"
#include "ftn_nonMemberFunctions.h"


namespace ftn
{

template<class Scalar, int nDims>
template<class T1, class ... OtherTypes>
Array<Scalar, nDims>::Array(T1 m, OtherTypes ... otherInitVals)
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

	_mdArray = std::move(std::vector<Scalar>(numel));
}

template<class Scalar, int nDims>
template<class Derived, class Scalar2>
Array<Scalar, nDims>::Array(ArrayBase<Derived, Scalar2> const& array) :
		_dimCounter(0)
{
	_isAllocated = true;

	for (int i = 1; i <= nDims; i++)
	{
		_beginIndices[i - 1] = (array.lbound(i));
		_dimLengths[i - 1] = (array.size(i));
	}

	_strides = computeArrayStrides(_dimLengths);

	_mdArray.resize(array.size());

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

template<class Scalar, int nDims>
Array<Scalar, nDims>::Array(Array<Scalar, nDims>& array) :
		_dimCounter(0)
{
	_isAllocated = true;

	for (int i = 1; i <= nDims; i++)
	{
		_beginIndices[i - 1] = (array.lbound(i));
		_dimLengths[i - 1] = push_back(array.size(i));
	}

	_strides = computeArrayStrides(_dimLengths);

	_mdArray.resize(array.size());

	size_t length = array.size();
	for (size_t i = 0; i < length; i++)
	{
		_mdArray[i] = array.linear(i);
	}

}

template<class Scalar, int nDims>
Array<Scalar, nDims>::Array(Array<Scalar, nDims> && other) noexcept : _dimCounter(0)
{
	_isAllocated = true;
	_dimLengths = std::move(other._dimLengths);
	_strides = std::move(other._strides);
	_beginIndices.fill(1);
	_mdArray = std::move(other._mdArray);
}

template<class Scalar, int nDims>
Array<Scalar, nDims>& Array<Scalar, nDims>::operator=(
		Array<Scalar, nDims> && other) noexcept
{
#ifdef FTN_DEBUG
	if (numDims() != other.numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to assign array of dimension: " << other.numDims() << " into array of dimension: " << numDims();
		throw std::domain_error(strStream.str());
	}
#endif
	if (!_isAllocated || !sameShape(*this, other))
	{
		_beginIndices.fill(1);
		_dimLengths = std::move(other._dimLengths);
		_strides = std::move(other._strides);

		_isAllocated = true;
	}

	_mdArray = std::move(other._mdArray);

	return *this;
}

template<class Scalar, int nDims>
template<class Derived, class Scalar2>
Array<Scalar, nDims>& Array<Scalar, nDims>::operator=(
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

	if (!_isAllocated || !(sameShape(*this, array)))
	{

		for (int i = 1; i <= nDims; i++)
		{
			_beginIndices[i - 1] = array.lbound(i);
			_dimLengths[i - 1] = array.size(i);
		}

		_mdArray.resize(array.size());

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

template<class Scalar, int nDims>
Array<Scalar, nDims>& Array<Scalar, nDims>::operator=(
		Array<Scalar, nDims>& array)
{
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>& arrayBaseInstance = array;
	this->operator=(arrayBaseInstance);
}

template<class Scalar, int nDims>
int Array<Scalar, nDims>::numDims() const
{
	return nDims;
}

template<class Scalar, int nDims>
Array<dim_type, 1> Array<Scalar, nDims>::shape() const
{
	Array<dim_type, 1> shape(nDims);

	for (int i = 0; i < nDims; i++)
	{
		shape(i + 1) = _dimLengths[i];
	}

	return shape;
}

template<class Scalar, int nDims>
std::string Array<Scalar, nDims>::toString() const
{
	std::ostringstream oss;
	if (!_mdArray.empty())
		std::copy(_mdArray.begin(), _mdArray.end(),
				std::ostream_iterator<Scalar>(oss, "    "));
	return oss.str();
}

template<class Scalar, int nDims>
dim_type Array<Scalar, nDims>::findInitializationValues(dim_type initVal)
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

template<class Scalar, int nDims>
dim_type Array<Scalar, nDims>::findInitializationValues(span initVal)
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

template<class Scalar, int nDims>
dim_type Array<Scalar, nDims>::lbound(dim_type dimNumber) const
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

template<class Scalar, int nDims>
Array<dim_type, 1> Array<Scalar, nDims>::lbound() const
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
	if (index < (size_t) 0 || index > size()-1)
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << 0 << ", "
				<< size()-1 << "]!";
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

//template<class Scalar, int nDims>
//Scalar Array<Scalar, nDims>::operator() (dim_type index) const
//{
//#ifdef FTN_DEBUG
//	indexOutOfBounds(index, 1);
//#endif
//	return mdArray(index - beginIndices[0]);
//}
//
//template<class Scalar, int nDims>
//Scalar& Array<Scalar, nDims>::operator() (dim_type index)
//{
//#ifdef FTN_DEBUG
//	indexOutOfBounds(index, 1);
//#endif
//	return mdArray(index - beginIndices[0]);
//}

template<class Scalar, int nDims>
Scalar Array<Scalar, nDims>::zb(dim_type m) const
{
	return _mdArray[m];
}

template<class Scalar, int nDims>
Scalar Array<Scalar, nDims>::zb(dim_type m, dim_type n) const
{
	return _mdArray[m + n * _strides[1]];
}

template<class Scalar, int nDims>
Scalar Array<Scalar, nDims>::zb(dim_type m, dim_type n, dim_type o) const
{
	return _mdArray[m + n * _strides[1] + o * _strides[2]];
}

template<class Scalar, int nDims>
Scalar Array<Scalar, nDims>::zb(dim_type m, dim_type n, dim_type o,
		dim_type p) const
{
	return _mdArray[m + n * _strides[1] + o * _strides[2] + p * _strides[3]];
}

template<class Scalar, int nDims>
Scalar& Array<Scalar, nDims>::zb(dim_type m)
{
	return _mdArray[m];
}

template<class Scalar, int nDims>
Scalar& Array<Scalar, nDims>::zb(dim_type m, dim_type n)
{
	return _mdArray[m + n * _strides[1]];
}

template<class Scalar, int nDims>
Scalar& Array<Scalar, nDims>::zb(dim_type m, dim_type n, dim_type o)
{
	return _mdArray[m + n * _strides[1] + o * _strides[2]];
}

template<class Scalar, int nDims>
Scalar& Array<Scalar, nDims>::zb(dim_type m, dim_type n, dim_type o, dim_type p)
{
	return _mdArray[m + n * _strides[1] + o * _strides[2] + p * _strides[3]];
}

template<class Scalar, int nDims>
Scalar Array<Scalar, nDims>::operator()(dim_type m) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::wrongDimension(1);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(m, 1);
#endif
	return _mdArray[m - _beginIndices[0]];
}

template<class Scalar, int nDims>
Scalar Array<Scalar, nDims>::operator()(dim_type m, dim_type n) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::wrongDimension(2);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(n, 2);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]];
}

template<class Scalar, int nDims>
Scalar Array<Scalar, nDims>::operator()(dim_type m, dim_type n,
		dim_type o) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::wrongDimension(3);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(o, 3);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]
			+ (o - _beginIndices[2]) * _strides[2]];
}

template<class Scalar, int nDims>
Scalar Array<Scalar, nDims>::operator()(dim_type m, dim_type n, dim_type o,
		dim_type p) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::wrongDimension(4);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(o, 3);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(p, 4);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]
			+ (o - _beginIndices[2]) * _strides[2]
			+ (p - _beginIndices[3]) * _strides[3]];
}

template<class Scalar, int nDims>
Scalar& Array<Scalar, nDims>::operator()(dim_type m)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::wrongDimension(1);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(m, 1);
#endif
	return _mdArray[m - _beginIndices[0]];
}

template<class Scalar, int nDims>
Scalar& Array<Scalar, nDims>::operator()(dim_type m, dim_type n)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::wrongDimension(2);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(n, 2);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]];
}

template<class Scalar, int nDims>
Scalar& Array<Scalar, nDims>::operator()(dim_type m, dim_type n, dim_type o)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::wrongDimension(3);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(o, 3);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]
			+ (o - _beginIndices[2]) * _strides[2]];
}

template<class Scalar, int nDims>
Scalar& Array<Scalar, nDims>::operator()(dim_type m, dim_type n, dim_type o,
		dim_type p)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::wrongDimension(4);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(o, 3);
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::indexOutOfBounds(p, 4);
#endif
	return _mdArray[(m - _beginIndices[0])
			+ (n - _beginIndices[1]) * _strides[1]
			+ (o - _beginIndices[2]) * _strides[2]
			+ (p - _beginIndices[3]) * _strides[3]];
}

template<class Scalar, int nDims>
Scalar Array<Scalar, nDims>::linear(size_t index) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::linearIndexOutOfBounds(index);
#endif
	return _mdArray[index];
}

template<class Scalar, int nDims>
Scalar& Array<Scalar, nDims>::linear(size_t index)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar, nDims>, Scalar>::linearIndexOutOfBounds(index);
#endif
	return _mdArray[index];
}

template<class Scalar, int nDims>
size_t Array<Scalar, nDims>::size() const
{
	return _mdArray.size();
}

template<class Scalar, int nDims>
size_t Array<Scalar, nDims>::size(int dimNumber) const
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

template<class Scalar, int nDims>
template<class OtherDimType, long unsigned int T>
size_t Array<Scalar, nDims>::sub2ind(std::array<OtherDimType, T>& ind)
{
	size_t linearInd = 0;
	for (int i = 0; i < numDims(); i++)
	{
		linearInd += (ind[i] - _beginIndices[i]) * _strides[i];
	}
	return linearInd + 1;
}

template<class Scalar, int nDims>
size_t Array<Scalar, nDims>::linearStride(dim_type dimNumber) const
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

template<class Scalar, int nDims>
dim_type Array<Scalar, nDims>::ubound(dim_type dimNumber) const
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

template<class Scalar, int nDims>
Array<dim_type, 1> Array<Scalar, nDims>::ubound() const
{
	int n = numDims();
	Array<dim_type, 1> ubounds(n);

	for (int i = 1; i <= n; i++)
	{
		ubounds(i) = ubound(i);
	}

	return ubounds;
}

template<class Scalar, int nDims>
template<class Scalar2>
typename std::enable_if<!isFtnType<Scalar2>::value, Array<Scalar, nDims> >::type& Array<Scalar, nDims>::operator=(const Scalar2& x)
{
#ifdef FTN_DEBUG
	if (!_isAllocated)
	{
		std::ostringstream strStream;
		strStream << "Attempted to assign a value to an unallocated array!";
		throw std::logic_error(strStream.str());
	}
#endif
	_mdArray.assign(size(), x);
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
