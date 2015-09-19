#ifndef FTN_OPERATORBASE_H_
#define FTN_OPERATORBASE_H_
#include "ftn_Array.h"
#include "ftn_ArrayBase.h"

namespace ftn
{

template<class Derived, class Scalar>
class OperatorBase: public ArrayBase<OperatorBase<Derived, Scalar>, Scalar>
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

	Scalar linear (dim_type index) const
	{
		return static_cast<Derived const&>(*this).linear(index);
	}

	int numDims () const
	{
		return static_cast<Derived const&>(*this).numDims();
	}

	Array<dim_type> shape () const
	{
		return static_cast<Derived const&>(*this).shape();
	}

	Array<dim_type> lbound () const
	{
		return static_cast<Derived const&>(*this).lbound();
	}

	template<class Derived2, class Scalar2>
	bool sameShapeAndContents(ArrayBase<Derived2, Scalar2> const& array) const
	{
		return static_cast<Derived const&>(*this).sameShapeAndContents(array);
	}

	template<class Derived2, class Scalar2>
	bool sameShape(ArrayBase<Derived2, Scalar2> const& array) const
	{
		return static_cast<Derived const&>(*this).sameShape(array);
	}

	template<class Derived2, class Scalar2>
	bool sameContents(ArrayBase<Derived2, Scalar2> const& array) const
	{
		return static_cast<Derived const&>(*this).sameContents(array);
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

#endif /* FTN_OPERATORBASE_H_ */
