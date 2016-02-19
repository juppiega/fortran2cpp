#ifndef FTN_ARRAYIMPLEMENTATIONS_H_
#define FTN_ARRAYIMPLEMENTATIONS_H_
#include "ftn_Array.h"
#include "ftn_nonMemberFunctions.h"

namespace ftn
{

template<class Scalar>
template<class T1, class ... OtherTypes>
Array<Scalar>::Array(T1 m, OtherTypes ... otherInitVals) : _nDims(1 + sizeof...(OtherTypes))
{
	_isAllocated = true;

	_dimLengths = {findInitializationValues(m), (findInitializationValues(otherInitVals))...};
	size_t numel = std::accumulate(_dimLengths.begin(), _dimLengths.begin()+_nDims, 1, std::multiplies<size_t>());
	//std::cout << _dimLengths[1] << std::endl;

	_strides = computeArrayStrides(_dimLengths);

	_mdArray = std::move(std::vector<Scalar>(numel));
}

template<class Scalar>
template<class Derived, class Scalar2>
Array<Scalar>::Array(ArrayBase<Derived, Scalar2> const& array)
{
	_isAllocated = true;
	_nDims = array.numDims();

	for (int i = 1; i <= _nDims; i++)
	{
		_beginIndices[i-1] = (array.lbound(i));
		_dimLengths[i-1] = (array.size(i));
	}

	_strides = computeArrayStrides(_dimLengths);

	_mdArray.resize(array.size());

	dim_type length = array.size();
	for (int i = 0; i < length; i++)
	{
		_mdArray[i] = array.linear(i + 1);
	}
}

template<class Scalar>
Array<Scalar>::Array(Array<Scalar>& array)
{
	_isAllocated = true;
	_nDims = array.numDims();

	for (int i = 1; i <= _nDims; i++)
	{
		_beginIndices[i-1] = (array.lbound(i));
		_dimLengths[i-1] = push_back(array.size(i));
	}

	_strides = computeArrayStrides(_dimLengths);

	_mdArray.resize(array.size());

	dim_type length = array.size();
	for (int i = 0; i < length; i++)
	{
		_mdArray[i] = array.linear(i + 1);
	}
}

template<class Scalar>
Array<Scalar>::Array(Array<Scalar> && other) noexcept
{
	_isAllocated = true;
	_nDims = other._nDims;
	_dimLengths = std::move(other._dimLengths);
	_strides = std::move(other._strides);
	_beginIndices.fill(1);
	_mdArray = std::move(other._mdArray);
}

template<class Scalar>
Array<Scalar>& Array<Scalar>::operator=(Array<Scalar> && other) noexcept
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

template<class Scalar>
template<class Derived, class Scalar2>
Array<Scalar>& Array<Scalar>::operator=(
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

		for (int i = 1; i <= _nDims; i++)
		{
			_beginIndices[i - 1] = array.lbound(i);
			_dimLengths[i - 1] = array.size(i);
		}

		_mdArray.resize(array.size());

		_strides = computeArrayStrides(_dimLengths);

		_isAllocated = true;
	}

	dim_type length = array.size();
	for (int i = 0; i < length; i++)
	{
		_mdArray[i] = array.linear(i + 1);
	}

	return *this;
}

template<class Scalar>
Array<Scalar>& Array<Scalar>::operator=(Array<Scalar>& array)
{
	ArrayNonConstBase<Array<Scalar>, Scalar>& arrayBaseInstance = array;
	this->operator=(arrayBaseInstance);
}

template<class Scalar>
int Array<Scalar>::numDims() const
{
	return _nDims;
}

template<class Scalar>
Array<dim_type> Array<Scalar>::shape() const
{
	int n = numDims();
	Array<dim_type> shape(n);

	for (int i = 0; i < n; i++)
	{
		shape(i + 1) = _dimLengths[i];
	}

	return shape;
}

template<class Scalar>
std::string Array<Scalar>::toString() const
{
	std::ostringstream oss;
	if (!_mdArray.empty())
		std::copy(_mdArray.begin(), _mdArray.end(),
				std::ostream_iterator<Scalar>(oss, "    "));
	return oss.str();
}

template<class Scalar>
dim_type Array<Scalar>::findInitializationValues(dim_type initVal)
{
	_beginIndices[dimNum()] = 1;
	if (initVal == Dynamic)
	{
		return 0;
		_isAllocated = false;
	}
	else
	{
		if (initVal < 0)
			initVal = 0;
		if (initVal == 0)
			_isAllocated = false;
		return initVal;
	}
}

template<class Scalar>
dim_type Array<Scalar>::findInitializationValues(span initVal)
{
	if (initVal.stop() == Dynamic)
	{
		if (initVal.start() != Dynamic)
			_beginIndices[dimNum()] = (initVal.start());
		else
			_beginIndices[dimNum()] = (1);
		_isAllocated = false;
		return 0;
	}
	else
	{
		dim_type length;
		if (initVal.start() != Dynamic)
		{
			if (initVal.start() <= initVal.stop())
			{
				_beginIndices[dimNum()] = (initVal.start());
				length = initVal.stop() - initVal.start() + 1;
			}
			else
			{
				_beginIndices[dimNum()] = (1);
				length = 0;
			}
		}
		else
		{
			_beginIndices[dimNum()] = (1);
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
		return length;
	}
}

template<class Scalar>
dim_type Array<Scalar>::lbound(dim_type dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "Argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return _beginIndices[dimNumber - 1];
}

template<class Scalar>
Array<dim_type> Array<Scalar>::lbound() const
{
	int n = numDims();
	Array<dim_type> lbounds(n);
	for (int i = 1; i <= n; i++)
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
		dim_type index) const
{
	if (index < 1 || index > size())
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << 1 << ", "
				<< size() << "]!";
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

//template<class Scalar>
//Scalar Array<Scalar>::operator() (dim_type index) const
//{
//#ifdef FTN_DEBUG
//	indexOutOfBounds(index, 1);
//#endif
//	return mdArray(index - beginIndices[0]);
//}
//
//template<class Scalar>
//Scalar& Array<Scalar>::operator() (dim_type index)
//{
//#ifdef FTN_DEBUG
//	indexOutOfBounds(index, 1);
//#endif
//	return mdArray(index - beginIndices[0]);
//}

template<class Scalar>
Scalar Array<Scalar>::operator()(dim_type m) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar>, Scalar>::wrongDimension(1);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(m, 1);
#endif
	return _mdArray[m - _beginIndices[0]];
}

template<class Scalar>
Scalar Array<Scalar>::operator()(dim_type m, dim_type n) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar>, Scalar>::wrongDimension(2);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(n, 2);
#endif
	return _mdArray[(m - _beginIndices[0]) + (n - _beginIndices[1]) * _strides[1]];
}

template<class Scalar>
Scalar Array<Scalar>::operator()(dim_type m, dim_type n, dim_type o) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar>, Scalar>::wrongDimension(3);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(o, 3);
#endif
	return _mdArray[(m - _beginIndices[0]) + (n - _beginIndices[1]) * _strides[1]
			+ (o - _beginIndices[2]) * _strides[2]];
}

template<class Scalar>
Scalar Array<Scalar>::operator()(dim_type m, dim_type n, dim_type o,
		dim_type p) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar>, Scalar>::wrongDimension(4);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(o, 3);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(p, 4);
#endif
	return _mdArray[(m - _beginIndices[0]) + (n - _beginIndices[1])*_strides[1] + (o - _beginIndices[2])*_strides[2] + (p
			- _beginIndices[3])*_strides[3]];
}

template<class Scalar>
Scalar& Array<Scalar>::operator()(dim_type m)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar>, Scalar>::wrongDimension(1);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(m, 1);
#endif
	return _mdArray[m - _beginIndices[0]];
}

template<class Scalar>
Scalar& Array<Scalar>::operator()(dim_type m, dim_type n)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar>, Scalar>::wrongDimension(2);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(n, 2);
#endif
	return _mdArray[(m - _beginIndices[0]) + (n - _beginIndices[1]) * _strides[1]];
}

template<class Scalar>
Scalar& Array<Scalar>::operator()(dim_type m, dim_type n, dim_type o)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar>, Scalar>::wrongDimension(3);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(o, 3);
#endif
	return _mdArray[(m - _beginIndices[0]) + (n - _beginIndices[1]) * _strides[1]
				+ (o - _beginIndices[2]) * _strides[2]];
}

template<class Scalar>
Scalar& Array<Scalar>::operator()(dim_type m, dim_type n, dim_type o,
		dim_type p)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar>, Scalar>::wrongDimension(4);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(o, 3);
	ArrayNonConstBase<Array<Scalar>, Scalar>::indexOutOfBounds(p, 4);
#endif
	return _mdArray[(m - _beginIndices[0]) + (n - _beginIndices[1])*_strides[1] + (o - _beginIndices[2])*_strides[2] + (p
				- _beginIndices[3])*_strides[3]];
}

template<class Scalar>
Scalar Array<Scalar>::linear(dim_type index) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar>, Scalar>::linearIndexOutOfBounds(index);
#endif
	return _mdArray[index - 1];
}

template<class Scalar>
Scalar& Array<Scalar>::linear(dim_type index)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<Array<Scalar>, Scalar>::linearIndexOutOfBounds(index);
#endif
	return _mdArray[index - 1];
}

template<class Scalar>
size_t Array<Scalar>::size() const
{
	return _mdArray.size();
}

template<class Scalar>
size_t Array<Scalar>::size(size_t dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "Argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return _dimLengths[dimNumber - 1];
}

template<class Scalar>
dim_type Array<Scalar>::ubound(dim_type dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "Argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return _beginIndices[dimNumber - 1] + _dimLengths[dimNumber - 1] - 1;
}

template<class Scalar>
Array<dim_type> Array<Scalar>::ubound() const
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
Array<Scalar>& Array<Scalar>::operator=(const Scalar& x)
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
Array<dim_type> ArrayNonConstBase<Derived, Scalar>::shape() const
{
	return static_cast<Derived const&>(*this).shape();
}

template<class Derived, class Scalar>
Array<dim_type> ArrayBase<Derived, Scalar>::shape() const
{
	return static_cast<Derived const&>(*this).shape();
}

template<class Derived, class Scalar>
Array<dim_type> ArrayNonConstBase<Derived, Scalar>::lbound() const
{
	return static_cast<Derived const&>(*this).lbound();
}

template<class Derived, class Scalar>
Array<dim_type> ArrayBase<Derived, Scalar>::lbound() const
{
	return static_cast<Derived const&>(*this).lbound();
}

template<class Derived, class Scalar>
Array<dim_type> ArrayNonConstBase<Derived, Scalar>::ubound() const
{
	return static_cast<Derived const&>(*this).ubound();
}

}

#endif /* FTN_ARRAYIMPLEMENTATIONS_H_ */
