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
	MDArrayView<Scalar> mdArrayView;

	void indexOutOfBounds (dim_type index, int dimNumber) const;
	void linearIndexOutOfBounds (dim_type index) const;

public:

	ArrayView (MDArrayView<Scalar>& arrayView);

	template<class Derived, class Scalar2>
	ArrayView<Scalar>& operator= (ArrayBase<Derived, Scalar2> const& array);

	ArrayView<Scalar>& operator= (ArrayView<Scalar>& array);

	MDArrayView<Scalar> getMdArrayView() const;

	ArrayView (ArrayView<Scalar>&& other);

//	Scalar operator() (dim_type index) const;
//	Scalar& operator() (dim_type index);

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

//	template<class Derived, class Scalar2>
//	void reshape (ArrayBase<Derived, Scalar2> const& newDims); // Lisaa Ftn ja Operator Baseen

	ArrayView& operator= (const Scalar& x);

	std::string toString () const;
};
}

#endif /* FTN_ARRAYVIEW_H_ */
