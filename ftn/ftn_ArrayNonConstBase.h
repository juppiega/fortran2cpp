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

template<class Scalar>
class Array;

template<class Scalar>
class ArrayView;

template<class Derived, class Scalar>
class ArrayNonConstBase: public ArrayBase<ArrayNonConstBase<Derived, Scalar>, Scalar>
{
private:
//	void sliceDomiView(MDArrayView<Scalar>& domiView, span& indexSpan, int dimNum) const;
//	void sliceDomiView(MDArrayView<Scalar>& domiView, dim_type index, int dimNum) const;

public:
	size_t size () const
	{
		return static_cast<Derived const&>(*this).size();
	}
	size_t size (size_t dimNumber) const
	{
		return static_cast<Derived const&>(*this).size(dimNumber);
	}

	dim_type lbound (dim_type dimNumber) const
	{
		return static_cast<Derived const&>(*this).lbound(dimNumber);
	}

//	MDArrayView<Scalar> getMdArrayView() const
//	{
//		return static_cast<Derived const&>(*this).getMdArrayView();
//	}

	template<class T1>
	ArrayView<Scalar> operator() (T1 m);

	template<class T1, class T2>
	ArrayView<Scalar> operator() (T1 m, T2 n);

	template<class T1, class T2, class T3>
	ArrayView<Scalar> operator() (T1 m, T2 n, T3 o);

	template<class T1, class T2, class T3, class T4>
	ArrayView<Scalar> operator() (T1 m, T2 n, T3 o, T4 p);

	template<class T1, class T2, class T3, class T4, class T5, class... OtherTypes>
	ArrayView<Scalar> operator() (T1 m, T2 n, T3 o, T4 p, T5 q, OtherTypes... otherSpans);

	template<class T1>
	ArrayView<Scalar> operator() (T1 m) const;

	template<class T1, class T2>
	ArrayView<Scalar> operator() (T1 m, T2 n) const;

	template<class T1, class T2, class T3>
	ArrayView<Scalar> operator() (T1 m, T2 n, T3 o) const;

	template<class T1, class T2, class T3, class T4>
	ArrayView<Scalar> operator() (T1 m, T2 n, T3 o, T4 p) const;

	template<class T1, class T2, class T3, class T4, class T5, class... OtherTypes>
	ArrayView<Scalar> operator() (T1 m, T2 n, T3 o, T4 p, T5 q, OtherTypes... otherSpans) const;

	Scalar operator() (dim_type m) const
	{
		return static_cast<Derived const&>(*this)(m);
	}
	Scalar operator() (dim_type m, dim_type n) const
	{
		return static_cast<Derived const&>(*this)(m,n);
	}
	Scalar operator() (dim_type m, dim_type n, dim_type o) const
	{
		return static_cast<Derived const&>(*this)(m,n,o);
	}
	Scalar operator() (dim_type m, dim_type n, dim_type o, dim_type p) const
	{
		return static_cast<Derived const&>(*this)(m,n,o,p);
	}
	Scalar operator() (dim_type m, dim_type n, dim_type o, dim_type p, dim_type q, va_list& args) const;

	Scalar& operator() (dim_type m)
	{
		return static_cast<Derived&>(*this)(m);
	}
	Scalar& operator() (dim_type m, dim_type n)
	{
		return static_cast<Derived&>(*this)(m,n);
	}
	Scalar& operator()(dim_type m, dim_type n, dim_type o)
	{
		return static_cast<Derived&>(*this)(m,n,o);
	}
	Scalar& operator() (dim_type m, dim_type n, dim_type o, dim_type p)
	{
		return static_cast<Derived&>(*this)(m,n,o,p);
	}
	Scalar& operator() (dim_type m, dim_type n, dim_type o, dim_type p, dim_type q, va_list& args);

	Scalar linear (dim_type index) const
	{
		return static_cast<Derived const&>(*this).linear(index);
	}

	Scalar& linear (dim_type index)
	{
		return static_cast<Derived&>(*this).linear(index);
	}

	Array<dim_type> shape () const;
	Array<dim_type> lbound () const;
	Array<dim_type> ubound () const;

	dim_type ubound (dim_type dimNumber) const
	{
		return static_cast<Derived const&>(*this).ubound(dimNumber);
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

	void indexOutOfBounds (dim_type index, int dimNumber) const;
	void linearIndexOutOfBounds (dim_type index) const;

	void wrongDimension(int dimNum) const;
};

}

#endif /* FTN_ARRAYNONCONSTBASE_H_ */
