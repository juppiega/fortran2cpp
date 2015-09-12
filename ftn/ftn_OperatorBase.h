#ifndef FTN_OPERATORBASE_H_
#define FTN_OPERATORBASE_H_
#include "ftn_FtnBase.h"

namespace ftn
{
template<class Derived, class Scalar>
class OperatorBase: public FtnBase<OperatorBase<Derived, Scalar>, Scalar>
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

	Scalar linear (dim_type index) const
	{
		return static_cast<Derived const&>(*this).linear(index);
	}

	int numDims () const
	{
		return static_cast<Derived const&>(*this).numDims();
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
