/*
 * ftn_ArrayBase.h
 *
 *  Created on: Sep 12, 2015
 *      Author: juho
 */

#ifndef FTN_ARRAYNONCONSTBASE_H_
#define FTN_ARRAYNONCONSTBASE_H_
#include "ftn_ArrayBase.h"
#include "ftn_Span.h"

namespace ftn
{

template<class Scalar, int nDims>
class Array;

template<class RefType, int nDims, class Scalar>
class ArrayView;

template<class Derived, class Scalar>
class ArrayNonConstBase: public ArrayBase<ArrayNonConstBase<Derived, Scalar>,
		Scalar>
{
private:

public:
	size_t size() const
	{
		return static_cast<Derived const&>(*this).size();
	}
	size_t size(size_t dimNumber) const
	{
		return static_cast<Derived const&>(*this).size(dimNumber);
	}

	dim_type lbound(dim_type dimNumber) const
	{
		return static_cast<Derived const&>(*this).lbound(dimNumber);
	}

	template<class T1>
	ArrayView<ArrayNonConstBase<Derived, Scalar>, 1, Scalar> operator()(T1 m);

	template<class T1, class T2>
	ArrayView<ArrayNonConstBase<Derived, Scalar>, 2, Scalar> operator()(T1 m,
			T2 n);

	template<class T1, class T2, class T3>
	ArrayView<ArrayNonConstBase<Derived, Scalar>, 3, Scalar> operator()(T1 m,
			T2 n, T3 o);

	template<class T1, class T2, class T3, class T4>
	ArrayView<ArrayNonConstBase<Derived, Scalar>, 4, Scalar> operator()(T1 m,
			T2 n, T3 o, T4 p);

	template<class T1>
	ArrayView<ArrayNonConstBase<Derived, Scalar>, 1, Scalar> operator()(
			T1 m) const;

	template<class T1, class T2>
	ArrayView<ArrayNonConstBase<Derived, Scalar>, 2, Scalar> operator()(T1 m,
			T2 n) const;

	template<class T1, class T2, class T3>
	ArrayView<ArrayNonConstBase<Derived, Scalar>, 3, Scalar> operator()(T1 m,
			T2 n, T3 o) const;

	template<class T1, class T2, class T3, class T4>
	ArrayView<ArrayNonConstBase<Derived, Scalar>, 4, Scalar> operator()(T1 m,
			T2 n, T3 o, T4 p) const;

	Scalar zb(dim_type m) const
	{
		return static_cast<Derived const&>(*this).zb(m);
	}
	Scalar zb(dim_type m, dim_type n) const
	{
		return static_cast<Derived const&>(*this).zb(m, n);
	}
	Scalar zb(dim_type m, dim_type n, dim_type o) const
	{
		return static_cast<Derived const&>(*this).zb(m, n, o);
	}
	Scalar zb(dim_type m, dim_type n, dim_type o, dim_type p) const
	{
		return static_cast<Derived const&>(*this).zb(m, n, o, p);
	}

	Scalar& zb(dim_type m)
	{
		return static_cast<Derived&>(*this).zb(m);
	}
	Scalar& zb(dim_type m, dim_type n)
	{
		return static_cast<Derived&>(*this).zb(m, n);
	}
	Scalar& zb(dim_type m, dim_type n, dim_type o)
	{
		return static_cast<Derived&>(*this).zb(m, n, o);
	}
	Scalar& zb(dim_type m, dim_type n, dim_type o, dim_type p)
	{
		return static_cast<Derived&>(*this).zb(m, n, o, p);
	}

	Scalar operator()(dim_type m) const
	{
		return static_cast<Derived const&>(*this)(m);
	}
	Scalar operator()(dim_type m, dim_type n) const
	{
		return static_cast<Derived const&>(*this)(m, n);
	}
	Scalar operator()(dim_type m, dim_type n, dim_type o) const
	{
		return static_cast<Derived const&>(*this)(m, n, o);
	}
	Scalar operator()(dim_type m, dim_type n, dim_type o, dim_type p) const
	{
		return static_cast<Derived const&>(*this)(m, n, o, p);
	}

	Scalar& operator()(dim_type m)
	{
		return static_cast<Derived&>(*this)(m);
	}
	Scalar& operator()(dim_type m, dim_type n)
	{
		return static_cast<Derived&>(*this)(m, n);
	}
	Scalar& operator()(dim_type m, dim_type n, dim_type o)
	{
		return static_cast<Derived&>(*this)(m, n, o);
	}
	Scalar& operator()(dim_type m, dim_type n, dim_type o, dim_type p)
	{
		return static_cast<Derived&>(*this)(m, n, o, p);
	}

	Scalar linear(size_t index) const
	{
		return static_cast<Derived const&>(*this).linear(index);
	}

	Scalar& linear(size_t index)
	{
		return static_cast<Derived&>(*this).linear(index);
	}

	Array<dim_type, 1> shape() const;
	Array<dim_type, 1> lbound() const;
	Array<dim_type, 1> ubound() const;

	template<class OtherDimType, long unsigned int T>
	size_t sub2ind(std::array<OtherDimType, T>& ind)
	{
		return static_cast<Derived&>(*this).sub2ind(ind);
	}

	dim_type ubound(dim_type dimNumber) const
	{
		return static_cast<Derived const&>(*this).ubound(dimNumber);
	}

	size_t linearStride(dim_type dimNumber) const
	{
		return static_cast<Derived const&>(*this).linearStride(dimNumber);
	}

	int numDims() const
	{
		return static_cast<Derived const&>(*this).numDims();
	}
	std::string toString() const
	{
		return static_cast<Derived const&>(*this).toString();
	}

	operator Derived&()
	{
		return static_cast<Derived&>(*this);
	}
	operator Derived const&() const
	{
		return static_cast<const Derived&>(*this);
	}

	constexpr bool isArrayView() const
	{
		return static_cast<Derived const&>(*this).isArrayView();
	}

	// At ftn_ArrayImplementations.h
	void indexOutOfBounds(dim_type index, int dimNumber) const;
	void linearIndexOutOfBounds(size_t index) const;

	void wrongDimension(int dimNum) const;
};

}

#endif /* FTN_ARRAYNONCONSTBASE_H_ */
