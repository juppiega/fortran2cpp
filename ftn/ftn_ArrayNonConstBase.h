/*
 * ftn_ArrayBase.h
 *
 *  Created on: Sep 12, 2015
 *      Author: juho
 */

#ifndef FTN_ARRAYNONCONSTBASE_H_
#define FTN_ARRAYNONCONSTBASE_H_
#include "ftn_ArrayBase.h"

namespace ftn
{

template<class Scalar>
class Array;

template<class Derived, class Scalar>
class ArrayNonConstBase: public ArrayBase<ArrayNonConstBase<Derived, Scalar>, Scalar>
{
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

	Scalar operator() (dim_type index) const
	{
		return static_cast<Derived const&>(*this)(index);
	}
	Scalar& operator() (dim_type index)
	{
		return static_cast<Derived&>(*this)(index);
	}

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
};

}

#endif /* FTN_ARRAYNONCONSTBASE_H_ */
