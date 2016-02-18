/*
 * ftn_ArrayView.h
 *
 *  Created on: Sep 20, 2015
 *      Author: juho
 */

#ifndef FTN_ARRAYVIEW_H_
#define FTN_ARRAYVIEW_H_
#include "ftn_Array.h"

namespace ftn
{
template<class Scalar>
class ArrayView: public ArrayNonConstBase<ArrayView<Scalar>, Scalar>
{
private:
	std::vector<dim_type> beginIndices;

	void indexOutOfBounds (dim_type index, int dimNumber) const;
	void linearIndexOutOfBounds (dim_type index) const;

public:

	ArrayView (MDArrayView<Scalar>& arrayView);

	template<class Derived, class Scalar2>
	ArrayView<Scalar>& operator= (ArrayBase<Derived, Scalar2> const& array);

	ArrayView<Scalar>& operator= (ArrayView<Scalar>& array);

	MDArrayView<Scalar> getMdArrayView() const;

	ArrayView (ArrayView<Scalar>&& other);

	Scalar operator() (dim_type m) const;
	Scalar operator() (dim_type m, dim_type n) const;
	Scalar operator() (dim_type m, dim_type n, dim_type o) const;
	Scalar operator() (dim_type m, dim_type n, dim_type o, dim_type p) const;

	Scalar& operator() (dim_type m);
	Scalar& operator() (dim_type m, dim_type n);
	Scalar& operator() (dim_type m, dim_type n, dim_type o);
	Scalar& operator() (dim_type m, dim_type n, dim_type o, dim_type p);

	template<class T1, class... OtherTypes>
	ArrayView<Scalar> operator() (T1 m, OtherTypes... otherSpans)
	{
		return ArrayNonConstBase<Array<Scalar>, Scalar>::operator()(m,otherSpans...);
	}

	template<class T1, class... OtherTypes>
	ArrayView<Scalar> operator() (T1 m, OtherTypes... otherSpans) const
	{
		return ArrayNonConstBase<Array<Scalar>, Scalar>::operator()(m,otherSpans...);
	}

	Scalar linear (dim_type index) const;
	Scalar& linear (dim_type index);

	int numDims () const;

	Array<dim_type> shape () const;

	Array<dim_type> lbound () const;
	dim_type lbound (dim_type dimNumber) const;

	Array<dim_type> ubound () const;
	dim_type ubound (dim_type dimNumber) const;

	size_t size () const;
	size_t size (size_t dimNumber) const;

	operator Scalar&();

//	template<class Derived, class Scalar2>
//	void reshape (ArrayBase<Derived, Scalar2> const& newDims); // Lisaa Ftn ja Operator Baseen

	ArrayView& operator= (const Scalar& x);

	std::string toString () const;
};
}

#endif /* FTN_ARRAYVIEW_H_ */
