#ifndef FTN_OPERATORBASE_H_
#define FTN_OPERATORBASE_H_
#include "ftn_Array.h"
#include "ftn_ArrayBase.h"
#include "ftn_traits.h"

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
	size_t size (int dimNumber) const
	{
		return static_cast<Derived const&>(*this).size(dimNumber);
	}

	dim_type lbound (dim_type dimNumber) const
	{
		return static_cast<Derived const&>(*this).lbound(dimNumber);
	}

	auto zb(dim_type m) const
	{
		return static_cast<Derived const&>(*this).zb(m);
	}
	auto zb(dim_type m, dim_type n) const
	{
		return static_cast<Derived const&>(*this).zb(m, n);
	}
	auto zb(dim_type m, dim_type n, dim_type o) const
	{
		return static_cast<Derived const&>(*this).zb(m, n, o);
	}
	auto zb(dim_type m, dim_type n, dim_type o, dim_type p) const
	{
		return static_cast<Derived const&>(*this).zb(m, n, o, p);
	}

	auto linear (size_t index) const
	{
		return static_cast<Derived const&>(*this).linear(index);
	}

	int numDims () const
	{
		return static_cast<Derived const&>(*this).numDims();
	}

	Array<dim_type, 1> shape () const
	{
		return static_cast<Derived const&>(*this).shape();
	}

	Array<dim_type, 1> lbound () const
	{
		return static_cast<Derived const&>(*this).lbound();
	}

	constexpr bool isArrayView() const
	{
		return static_cast<Derived const&>(*this).isArrayView();
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
