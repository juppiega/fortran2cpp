
#ifndef FTN_ARRAYVIEWIMPLEMENTATION_H_
#define FTN_ARRAYVIEWIMPLEMENTATION_H_
#include "ftn_nonMemberFunctions.h"
#include "ftn_Array.h"
#include "ftn_ArrayView.h"

namespace ftn
{
template<class RefType, int nDims, class Scalar>
template<class T1, class ... OtherTypes>
ArrayView<RefType, nDims, Scalar>::ArrayView(RefType& arrayRef, T1& m,
		OtherTypes&... otherInitVals) :
		_arrayRef(arrayRef)
{
	_dimCounter = 1;
	_start =
	{	findStart(m), (findStart(otherInitVals))...};
	_dimCounter = 1; // Reset counter.
	_stop =
	{	findStop(m), (findStop(otherInitVals))...};
	_stride =
	{	findStride(m), (findStride(otherInitVals))...};

	for (int i = 0; i < nDims; i++)
	{
		_dimLengths[i] = std::max(0, (_stop[i] - _start[i] + _stride[i]) / _stride[i]);
	}

	size_t cumulativeLength = 1;
	for (int i = 0; i < nDims; i++)
	{
		cumulativeLength *= _dimLengths[i];
		_cumDimLengths[i] = cumulativeLength;
	}

	_numel = _cumDimLengths[nDims-1];

	_firstInd = _arrayRef.sub2ind(_start);

	for (int i = 0; i < nDims; i++)
	{
		_linStrides[i] = _stride[i] * _arrayRef.linearStride(i+1);
	}
	// TODO: LISAA DEBUGGAUS-KOODIA!!!
}

template<class RefType, int nDims, class Scalar>
ArrayView<RefType, nDims, Scalar>::ArrayView(
		ArrayView<RefType, nDims, Scalar> && other) :
		_arrayRef(other._arrayRef), _numel(other._numel), _firstInd(other._firstInd), _dimCounter(other._dimCounter)
{
	_start = std::move(other._start);
	_stop = std::move(other._stop);
	_stride = std::move(other._stride);
	_dimLengths = std::move(other._dimLengths);
	_cumDimLengths = std::move(other._cumDimLengths);
	_linStrides = std::move(other._linStrides);
}

template<class RefType, int nDims, class Scalar>
template<class Derived, class Scalar2>
ArrayView<RefType, nDims, Scalar>& ArrayView<RefType, nDims, Scalar>::operator=(
		ArrayBase<Derived, Scalar2> const& array)
{
#ifdef FTN_DEBUG
	if (numDims() != array.numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to assign array of dimension: " << array.numDims() << " into array subobject of dimension: " << numDims();
		throw std::domain_error(strStream.str());
	}
	if (!sameShape(*this, array))
	{
		std::ostringstream strStream;
		strStream << "Left and right hand sides of the assignment are of different shape!";
		throw std::domain_error(strStream.str());
	}
#endif

	size_t length = array.size();
	for (size_t i = 1; i < length; i++)
	{
		linear(i) = array.linear(i);
	}

	return *this;
}

template<class RefType, int nDims, class Scalar>
ArrayView<RefType, nDims, Scalar>& ArrayView<RefType, nDims, Scalar>::operator=(
		ArrayView<RefType, nDims, Scalar>& array)
{
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>& arrayBaseInstance =
			array;
	this->operator=(arrayBaseInstance);
}

template<class RefType, int nDims, class Scalar>
int ArrayView<RefType, nDims, Scalar>::numDims() const
{
	return nDims;
}

template<class RefType, int nDims, class Scalar>
size_t ArrayView<RefType, nDims, Scalar>::size() const
{
	return _numel;
}

template<class RefType, int nDims, class Scalar>
size_t ArrayView<RefType, nDims, Scalar>::size(size_t dimNumber) const
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

template<class RefType, int nDims, class Scalar>
Scalar ArrayView<RefType, nDims, Scalar>::linear(size_t ind) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::linearIndexOutOfBounds(ind);
#endif
	size_t zb = ind - 1;
	size_t linInd = _firstInd + (zb % _dimLengths[0]) * _linStrides[0];
	for (int i = 1; i < nDims; i++)
	{
		linInd += ((zb / _cumDimLengths[i-1]) % _dimLengths[i]) * _linStrides[i];
	}
	return _arrayRef.linear(linInd);
}

template<class RefType, int nDims, class Scalar>
Scalar& ArrayView<RefType, nDims, Scalar>::linear(size_t ind)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::linearIndexOutOfBounds(ind);
#endif
	size_t zb = ind - 1;
	size_t linInd = _firstInd + (zb % _dimLengths[0]) * _linStrides[0];
	for (int i = 1; i < nDims; i++)
	{
		linInd += ((zb / _cumDimLengths[i-1]) % _dimLengths[i]) * _linStrides[i];
	}
	return _arrayRef.linear(linInd);
}

template<class RefType, int nDims, class Scalar>
dim_type ArrayView<RefType, nDims, Scalar>::lbound(dim_type dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "lbound argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return 1;
}

template<class RefType, int nDims, class Scalar>
Array<dim_type> ArrayView<RefType, nDims, Scalar>::shape() const
{
	int n = numDims();
	Array<dim_type> shape(n);

	for (int i = 1; i <= n; i++)
	{
		shape(i) = size(i);
	}

	return shape;
}

template<class RefType, int nDims, class Scalar>
Array<dim_type> ArrayView<RefType, nDims, Scalar>::lbound() const
{
	int n = numDims();
	Array<dim_type> lbounds(n);
	lbounds = 1;
	return lbounds;
}

// TODO: Scalarit eivat valttamatta samat!
template<class RefType, int nDims, class Scalar>
ArrayView<RefType, nDims, Scalar>& ArrayView<RefType, nDims, Scalar>::operator=(
		const Scalar& x)
{
	for (size_t i = 1; i <= _numel; i++)
	{
		linear(i) = x;
	}
	return *this;
}

template<class RefType, int nDims, class Scalar>
std::string ArrayView<RefType, nDims, Scalar>::toString() const
{
	Array<Scalar> outp = *this;
	return outp.toString();
}

template<class RefType, int nDims, class Scalar>
dim_type ArrayView<RefType, nDims, Scalar>::ubound(dim_type dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "ubound argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return size(dimNumber);
}

template<class RefType, int nDims, class Scalar>
Array<dim_type> ArrayView<RefType, nDims, Scalar>::ubound() const
{
	int n = numDims();
	Array<dim_type> ubounds(n);

	for (int i = 1; i <= n; i++)
	{
		ubounds(i) = ubound(i);
	}

	return ubounds;
}

template<class RefType, int nDims, class Scalar>
inline dim_type ArrayView<RefType, nDims, Scalar>::findStart (span& sp)
{
	dim_type start;
	if (sp.start() == Dynamic)
		start = _arrayRef.lbound(_dimCounter);
	else
		start = sp.start();
	_dimCounter++;
	return start;
}

template<class RefType, int nDims, class Scalar>
inline dim_type ArrayView<RefType, nDims, Scalar>::findStop (span& sp)
{
	dim_type stop;
	if (sp.stop() == Dynamic)
		stop = _arrayRef.ubound(_dimCounter);
	else
		stop = sp.stop();
	_dimCounter++;
	return stop;
}

template<class RefType, int nDims, class Scalar>
inline dim_type ArrayView<RefType, nDims, Scalar>::findStride (span& sp) const
{
	dim_type stride;
	if (sp.stride() == Dynamic)
		stride = 1;
	else
		stride = sp.stride();
#ifdef FTN_DEBUG
	if (stride == 0)
	{
		std::ostringstream strStream;
		strStream << "Stride of span cannot be zero!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return stride;
}

template<class RefType, int nDims, class Scalar>
Scalar ArrayView<RefType, nDims, Scalar>::zb(dim_type m) const
{
	return _arrayRef(_start[0] + m * _stride[0]);
}

template<class RefType, int nDims, class Scalar>
Scalar ArrayView<RefType, nDims, Scalar>::zb(dim_type m,
		dim_type n) const
{
	return _arrayRef(_start[0] + m * _stride[0],
			  _start[1] + n * _stride[1]);
}

template<class RefType, int nDims, class Scalar>
Scalar ArrayView<RefType, nDims, Scalar>::zb(dim_type m, dim_type n,
		dim_type o) const
{
	return _arrayRef(_start[0] + m * _stride[0],
			  _start[1] + n * _stride[1],
			  _start[2] + o * _stride[2]);
}

template<class RefType, int nDims, class Scalar>
Scalar ArrayView<RefType, nDims, Scalar>::zb(dim_type m, dim_type n,
		dim_type o, dim_type p) const
{
	return _arrayRef(_start[0] + m * _stride[0],
			  _start[1] + n * _stride[1],
			  _start[2] + o * _stride[2],
			  _start[3] + p * _stride[3]);
}

template<class RefType, int nDims, class Scalar>
Scalar& ArrayView<RefType, nDims, Scalar>::zb(dim_type m)
{
	return _arrayRef(_start[0] + m * _stride[0]);
}

template<class RefType, int nDims, class Scalar>
Scalar& ArrayView<RefType, nDims, Scalar>::zb(dim_type m, dim_type n)
{
	return _arrayRef(_start[0] + m * _stride[0],
			  _start[1] + n * _stride[1]);
}

template<class RefType, int nDims, class Scalar>
Scalar& ArrayView<RefType, nDims, Scalar>::zb(dim_type m, dim_type n,
		dim_type o)
{
	return _arrayRef(_start[0] + m * _stride[0],
			  _start[1] + n * _stride[1],
			  _start[2] + o * _stride[2]);
}

template<class RefType, int nDims, class Scalar>
Scalar& ArrayView<RefType, nDims, Scalar>::zb(dim_type m, dim_type n,
		dim_type o, dim_type p)
{
	return _arrayRef(_start[0] + m * _stride[0],
			  _start[1] + n * _stride[1],
			  _start[2] + o * _stride[2],
			  _start[3] + p * _stride[3]);
}

// @formatter:off
template<class RefType, int nDims, class Scalar>
Scalar ArrayView<RefType, nDims, Scalar>::operator()(dim_type m) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::wrongDimension(1);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(m, 1);
#endif
	return _arrayRef(_start[0] + (m - 1) * _stride[0]);
}

template<class RefType, int nDims, class Scalar>
Scalar ArrayView<RefType, nDims, Scalar>::operator()(dim_type m,
		dim_type n) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::wrongDimension(2);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(n, 2);
#endif
	return _arrayRef(_start[0] + (m - 1) * _stride[0],
			  _start[1] + (n - 1) * _stride[1]);
}

template<class RefType, int nDims, class Scalar>
Scalar ArrayView<RefType, nDims, Scalar>::operator()(dim_type m, dim_type n,
		dim_type o) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::wrongDimension(3);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(o, 3);
#endif
	return _arrayRef(_start[0] + (m - 1) * _stride[0],
			  _start[1] + (n - 1) * _stride[1],
			  _start[2] + (o - 1) * _stride[2]);
}

template<class RefType, int nDims, class Scalar>
Scalar ArrayView<RefType, nDims, Scalar>::operator()(dim_type m, dim_type n,
		dim_type o, dim_type p) const
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::wrongDimension(4);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(o, 3);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(p, 4);
#endif
	return _arrayRef(_start[0] + (m - 1) * _stride[0],
			  _start[1] + (n - 1) * _stride[1],
			  _start[2] + (o - 1) * _stride[2],
			  _start[3] + (p - 1) * _stride[3]);
}

template<class RefType, int nDims, class Scalar>
Scalar& ArrayView<RefType, nDims, Scalar>::operator()(dim_type m)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::wrongDimension(1);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(m, 1);
#endif
	return _arrayRef(_start[0] + (m - 1) * _stride[0]);
}

template<class RefType, int nDims, class Scalar>
Scalar& ArrayView<RefType, nDims, Scalar>::operator()(dim_type m, dim_type n)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::wrongDimension(2);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(n, 2);
#endif
	return _arrayRef(_start[0] + (m - 1) * _stride[0],
			  _start[1] + (n - 1) * _stride[1]);
}

template<class RefType, int nDims, class Scalar>
Scalar& ArrayView<RefType, nDims, Scalar>::operator()(dim_type m, dim_type n,
		dim_type o)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::wrongDimension(3);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(o, 3);
#endif
	return _arrayRef(_start[0] + (m - 1) * _stride[0],
			  _start[1] + (n - 1) * _stride[1],
			  _start[2] + (o - 1) * _stride[2]);
}

template<class RefType, int nDims, class Scalar>
Scalar& ArrayView<RefType, nDims, Scalar>::operator()(dim_type m, dim_type n,
		dim_type o, dim_type p)
{
#ifdef FTN_DEBUG
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::wrongDimension(4);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(m, 1);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(n, 2);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(o, 3);
	ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::indexOutOfBounds(p, 4);
#endif
	return _arrayRef(_start[0] + (m - 1) * _stride[0],
			  _start[1] + (n - 1) * _stride[1],
			  _start[2] + (o - 1) * _stride[2],
			  _start[3] + (p - 1) * _stride[3]);
}

template<class RefType, int nDims, class Scalar>
ArrayView<RefType, nDims, Scalar>::operator Scalar&()
{
#ifdef FTN_DEBUG
	if (size() != 1)
	{
		std::ostringstream strStream;
		strStream << "Trying to convert an array subobject of size " << size() << " into scalar!";
		throw std::domain_error(strStream.str());
	}
#endif
	return linear(1);
}
// @formatter:on

/*
 * ArrayNonConstBase functions depending on ArrayView implementation:
 */

template<class Derived, class Scalar>
template<class T1>
ArrayView<ArrayNonConstBase<Derived, Scalar>, 1, Scalar> ArrayNonConstBase<Derived, Scalar>::operator()(
		T1 m)
{
	constexpr int thisDims = 1;
#ifdef FTN_DEBUG
	if (thisDims != numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to reference an array of dimension: " << numDims() << " by providing " << 1 << " parameters to operator()!";
		throw std::domain_error(strStream.str());
	}
#endif

	return ArrayView<ArrayNonConstBase<Derived, Scalar>, thisDims, Scalar> (*this, m);
}

template<class Derived, class Scalar>
template<class T1, class T2>
ArrayView<ArrayNonConstBase<Derived, Scalar>, 2, Scalar> ArrayNonConstBase<Derived, Scalar>::operator()(
		T1 m, T2 n)
{
	constexpr int thisDims = 2;
#ifdef FTN_DEBUG
	if (thisDims != numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to reference an array of dimension: " << numDims() << " by providing " << 1 << " parameters to operator()!";
		throw std::domain_error(strStream.str());
	}
#endif

	return ArrayView<ArrayNonConstBase<Derived, Scalar>, thisDims, Scalar> (*this, m, n);
}

template<class Derived, class Scalar>
template<class T1, class T2, class T3>
ArrayView<ArrayNonConstBase<Derived, Scalar>, 3, Scalar> ArrayNonConstBase<Derived, Scalar>::operator()(
		T1 m, T2 n, T3 o)
{
	constexpr int thisDims = 3;
#ifdef FTN_DEBUG
	if (thisDims != numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to reference an array of dimension: " << numDims() << " by providing " << 1 << " parameters to operator()!";
		throw std::domain_error(strStream.str());
	}
#endif

	return ArrayView<ArrayNonConstBase<Derived, Scalar>, thisDims, Scalar> (*this, m, n, o);
}

template<class Derived, class Scalar>
template<class T1, class T2, class T3, class T4>
ArrayView<ArrayNonConstBase<Derived, Scalar>, 4, Scalar> ArrayNonConstBase<Derived, Scalar>::operator()(
		T1 m, T2 n, T3 o, T4 p)
{
	constexpr int thisDims = 4;
#ifdef FTN_DEBUG
	if (thisDims != numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to reference an array of dimension: " << numDims() << " by providing " << 1 << " parameters to operator()!";
		throw std::domain_error(strStream.str());
	}
#endif

	return ArrayView<ArrayNonConstBase<Derived, Scalar>, thisDims, Scalar> (*this, m, n, o, p);
}


template<class Derived, class Scalar>
template<class T1>
ArrayView<ArrayNonConstBase<Derived, Scalar>, 1, Scalar> ArrayNonConstBase<Derived, Scalar>::operator()(
		T1 m) const
{
	constexpr int thisDims = 1;
#ifdef FTN_DEBUG
	if (thisDims != numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to reference an array of dimension: " << numDims() << " by providing " << 1 << " parameters to operator()!";
		throw std::domain_error(strStream.str());
	}
#endif

	return ArrayView<ArrayNonConstBase<Derived, Scalar>, thisDims, Scalar> (*this, m);
}

template<class Derived, class Scalar>
template<class T1, class T2>
ArrayView<ArrayNonConstBase<Derived, Scalar>, 2, Scalar> ArrayNonConstBase<Derived, Scalar>::operator()(
		T1 m, T2 n) const
{
	constexpr int thisDims = 2;
#ifdef FTN_DEBUG
	if (thisDims != numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to reference an array of dimension: " << numDims() << " by providing " << 1 << " parameters to operator()!";
		throw std::domain_error(strStream.str());
	}
#endif

	return ArrayView<ArrayNonConstBase<Derived, Scalar>, thisDims, Scalar> (*this, m, n);
}

template<class Derived, class Scalar>
template<class T1, class T2, class T3>
ArrayView<ArrayNonConstBase<Derived, Scalar>, 3, Scalar> ArrayNonConstBase<Derived, Scalar>::operator()(
		T1 m, T2 n, T3 o) const
{
	constexpr int thisDims = 3;
#ifdef FTN_DEBUG
	if (thisDims != numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to reference an array of dimension: " << numDims() << " by providing " << 1 << " parameters to operator()!";
		throw std::domain_error(strStream.str());
	}
#endif

	return ArrayView<ArrayNonConstBase<Derived, Scalar>, thisDims, Scalar> (*this, m, n, o);
}

template<class Derived, class Scalar>
template<class T1, class T2, class T3, class T4>
ArrayView<ArrayNonConstBase<Derived, Scalar>, 4, Scalar> ArrayNonConstBase<Derived, Scalar>::operator()(
		T1 m, T2 n, T3 o, T4 p) const
{
	constexpr int thisDims = 4;
#ifdef FTN_DEBUG
	if (thisDims != numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to reference an array of dimension: " << numDims() << " by providing " << 1 << " parameters to operator()!";
		throw std::domain_error(strStream.str());
	}
#endif

	return ArrayView<ArrayNonConstBase<Derived, Scalar>, thisDims, Scalar> (*this, m, n, o, p);
}

} // namespace ftn

#endif /* FTN_ARRAYVIEWIMPLEMENTATION_H_ */
