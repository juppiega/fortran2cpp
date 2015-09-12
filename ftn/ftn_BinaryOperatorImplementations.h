#ifndef FTN_BINARYOPERATORIMPLEMENTATIONS_H_
#define FTN_BINARYOPERATORIMPLEMENTATIONS_H_
#include "ftn_BinaryOperatorBase.h"

namespace ftn
{
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Sum of two Arrays
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArraySum: public BinaryOperatorBase<ArraySum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	Scalar linear (dim_type i) const
	{
		return this->first.linear(i) + this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArraySum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator+ (
		FtnBase<LeftSide, Scalar> const& a, FtnBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ArraySum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Difference of two Arrays
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArrayDifference: public BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	Scalar linear (dim_type i) const
	{
		return this->first.linear(i) - this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator- (
		FtnBase<LeftSide, Scalar> const& a, FtnBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Elemental Product of two Arrays
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArrayProduct: public BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	Scalar linear (dim_type i) const
	{
		return this->first.linear(i) * this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator% (
		FtnBase<LeftSide, Scalar> const& a, FtnBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Elemental Division of two Arrays
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArrayDivision: public BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	Scalar linear (dim_type i) const
	{
		return this->first.linear(i) * this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator/ (
		FtnBase<LeftSide, Scalar> const& a, FtnBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

}


#endif /* FTN_BINARYOPERATORIMPLEMENTATIONS_H_ */
