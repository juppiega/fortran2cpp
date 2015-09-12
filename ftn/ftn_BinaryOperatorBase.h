#ifndef FTN_BINARYOPERATORBASE_H_
#define FTN_BINARYOPERATORBASE_H_
#include "ftn_OperatorBase.h"

namespace ftn
{
template<class Derived, class LeftSide, class RightSide, class Scalar>
class BinaryOperatorBase: public OperatorBase<BinaryOperatorBase<Derived, LeftSide, RightSide, Scalar>, Scalar>
{
protected:
	LeftSide const& first;
	RightSide const& second;
public:
	BinaryOperatorBase (FtnBase<LeftSide, Scalar> const& a, FtnBase<RightSide, Scalar> const& b) :
			first(a), second(b)
	{
	}
	size_t size () const
	{
		return first.size();
	}
	size_t size (size_t dimNumber) const
	{
		return first.size(dimNumber);
	}
	int numDims () const
	{
		return first.numDims();
	}

	Scalar linear (dim_type index) const
	{
		return static_cast<Derived const&>(*this).linear(index);
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

#endif /* FTN_BINARYOPERATORBASE_H_ */
