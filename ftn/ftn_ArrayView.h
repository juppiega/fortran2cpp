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
// TODO: funktiot sub2ind, linearStride.
template<class RefType, int nDims, class Scalar>
class ArrayView: public ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>
{
private:
	RefType& _arrayRef;
	std::array<dim_type, nDims> _start;
	std::array<dim_type, nDims> _stop;
	std::array<dim_type, nDims> _stride;
	int _dimCounter;

public:
	using ArrayNonConstBase<ArrayView<RefType, nDims, Scalar>, Scalar>::operator();

	template<class T1, class ... OtherTypes>
	ArrayView (RefType& arrayRef, T1& m, OtherTypes&... otherInitVals);

	template<class Derived, class Scalar2>
	ArrayView<RefType, nDims, Scalar>& operator= (ArrayBase<Derived, Scalar2> const& array);

	ArrayView<RefType, nDims, Scalar>& operator= (ArrayView<RefType, nDims, Scalar>& array);

	ArrayView (ArrayView<RefType, nDims, Scalar>&& other);

	Scalar zb(dim_type m) const;
	Scalar zb(dim_type m, dim_type n) const;
	Scalar zb(dim_type m, dim_type n, dim_type o) const;
	Scalar zb(dim_type m, dim_type n, dim_type o, dim_type p) const;

	Scalar& zb(dim_type m);
	Scalar& zb(dim_type m, dim_type n);
	Scalar& zb(dim_type m, dim_type n, dim_type o);
	Scalar& zb(dim_type m, dim_type n, dim_type o, dim_type p);

	Scalar operator() (dim_type m) const;
	Scalar operator() (dim_type m, dim_type n) const;
	Scalar operator() (dim_type m, dim_type n, dim_type o) const;
	Scalar operator() (dim_type m, dim_type n, dim_type o, dim_type p) const;

	Scalar& operator() (dim_type m);
	Scalar& operator() (dim_type m, dim_type n);
	Scalar& operator() (dim_type m, dim_type n, dim_type o);
	Scalar& operator() (dim_type m, dim_type n, dim_type o, dim_type p);

	Scalar linear (size_t index) const;
	Scalar& linear (size_t index);

	int numDims () const;

	Array<dim_type, 1> shape () const;

	Array<dim_type, 1> lbound () const;
	dim_type lbound (dim_type dimNumber) const;

	Array<dim_type, 1> ubound () const;
	dim_type ubound (dim_type dimNumber) const;

	size_t size () const;
	size_t size (int dimNumber) const;

	inline dim_type findStart (dim_type& ind)
	{
		_dimCounter++;
		return ind;
	}
	inline dim_type findStop (dim_type& ind)
	{
		_dimCounter++;
		return ind;
	}
	inline dim_type findStride (dim_type& ind) const
	{
		return 1;
	}

	constexpr bool isArrayView() const
	{
		return true;
	}

	inline dim_type findStart (span& sp);
	inline dim_type findStop (span& sp);
	inline dim_type findStride (span& sp) const;

	operator Scalar&();

//	template<class Derived, class Scalar2>
//	void reshape (ArrayBase<Derived, Scalar2> const& newDims); // Lisaa Ftn ja Operator Baseen

	template<class Scalar2>
	typename std::enable_if<!isFtnType<Scalar2>::value, ArrayView>::type& operator= (const Scalar2& x);

	std::string toString () const;
};
}

#endif /* FTN_ARRAYVIEW_H_ */
