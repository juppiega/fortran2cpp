#ifndef FTN_BINARYOPERATORIMPLEMENTATIONS_H_
#define FTN_BINARYOPERATORIMPLEMENTATIONS_H_
#include "ftn_BinaryOperatorBase.h"
#include "ftn_nonMemberFunctions.h"
#include <type_traits>
#include <boost/math/special_functions/bessel.hpp>

namespace ftn
{
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Sum of two Arrays
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar, class = typename std::enable_if<!std::is_fundamental<LeftSide>::value && !std::is_fundamental<RightSide>::value, bool>::type>
class ArraySum: public BinaryOperatorBase<ArraySum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first.linear(i) + this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArraySum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator+ (
		ArrayBase<LeftSide, Scalar> const& a, ArrayBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ArraySum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Sum of an Array and a primitive type.
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArrayScalarSum: public BinaryOperatorBase<ArrayScalarSum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first.linear(i) + this->second;
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArrayScalarSum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator+ (
		ArrayBase<LeftSide, Scalar> const& a, RightSide const& b)
{
	return BinaryOperatorBase<ArrayScalarSum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}

template<class LeftSide, class RightSide, class Scalar>
class ScalarArraySum: public BinaryOperatorBase<ScalarArraySum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first + this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ScalarArraySum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator+ (
		LeftSide const& a, ArrayBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ScalarArraySum<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Difference of two Arrays
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArrayDifference: public BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first.linear(i) - this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator- (
		ArrayBase<LeftSide, Scalar> const& a, ArrayBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Difference of an Array and a primitive type.
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArrayScalarDifference: public BinaryOperatorBase<ArrayScalarDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first.linear(i) - this->second;
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArrayScalarDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator- (
		ArrayBase<LeftSide, Scalar> const& a, RightSide const& b)
{
	return BinaryOperatorBase<ArrayScalarDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}

template<class LeftSide, class RightSide, class Scalar>
class ScalarArrayDifference: public BinaryOperatorBase<ScalarArrayDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first - this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ScalarArrayDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator- (
		LeftSide const& a, ArrayBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ScalarArrayDifference<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Elemental Product of two Arrays
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArrayProduct: public BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first.linear(i) * this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator* (
		ArrayBase<LeftSide, Scalar> const& a, ArrayBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Product of an Array and a primitive type.
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArrayScalarProduct: public BinaryOperatorBase<ArrayScalarProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first.linear(i) * this->second;
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArrayScalarProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator* (
		ArrayBase<LeftSide, Scalar> const& a, RightSide const& b)
{
	return BinaryOperatorBase<ArrayScalarProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}

template<class LeftSide, class RightSide, class Scalar>
class ScalarArrayProduct: public BinaryOperatorBase<ScalarArrayProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first * this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ScalarArrayProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator* (
		LeftSide const& a, ArrayBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ScalarArrayProduct<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Elemental Division of two Arrays
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArrayDivision: public BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first.linear(i) / this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator/ (
		ArrayBase<LeftSide, Scalar> const& a, ArrayBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Division of an Array and a primitive type.
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArrayScalarDivision: public BinaryOperatorBase<ArrayScalarDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first.linear(i) / this->second;
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArrayScalarDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator/ (
		ArrayBase<LeftSide, Scalar> const& a, RightSide const& b)
{
	return BinaryOperatorBase<ArrayScalarDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}

template<class LeftSide, class RightSide, class Scalar>
class ScalarArrayDivision: public BinaryOperatorBase<ScalarArrayDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return this->first / this->second.linear(i);
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ScalarArrayDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> const operator/ (
		LeftSide const& a, ArrayBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ScalarArrayDivision<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Arcus Tangent (2-arguments)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class Scalar>
class ArcTan2: public BinaryOperatorBase<ArcTan2<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return std::atan2(this->first.linear(i), this->second.linear(i));
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArcTan2<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> atan2 (
		ArrayBase<LeftSide, Scalar> const& a, ArrayBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ArcTan2<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Arcus Tangent (2-arguments). For some strange reason, the Fortran 2008 standard specifies a new
// arcus tangent function: atan(y,x), the behavior which is exactly the same as that of atan2(y,x)!
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// For fundamental types call the standard library function.
template<class T1, class T2, class = typename std::enable_if<std::is_fundamental<T1>::value && std::is_fundamental<T2>::value, bool>::type >
auto atan (T1 y, T2 x)
{
	return std::atan2(y, x);
}

// Else throw a new binary operator.
template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<ArcTan2<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> atan (
		ArrayBase<LeftSide, Scalar> const& a, ArrayBase<RightSide, Scalar> const& b)
{
	return BinaryOperatorBase<ArcTan2<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Bessel J_N
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class T2, class = typename std::enable_if<std::is_fundamental<T2>::value, bool>::type>
auto bessel_jn (T1 n, T2 x)
{
	return boost::math::cyl_bessel_j(n, x);
}

template<class LeftSide, class RightSide, class Scalar>
class Bessel_JN: public BinaryOperatorBase<Bessel_JN<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>
{
public:
	auto linear (dim_type i) const
	{
		return boost::math::cyl_bessel_j(this->first, this->second.linear(i));
	}
};

template<class LeftSide, class RightSide, class Scalar>
BinaryOperatorBase<Bessel_JN<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar> bessel_jn (
		LeftSide const& a, ArrayBase<RightSide, Scalar> const& b) // Exceptionally not ArrayBase<LeftSide, Scalar> const& a!
{
	return BinaryOperatorBase<Bessel_JN<LeftSide, RightSide, Scalar>, LeftSide, RightSide, Scalar>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

}


#endif /* FTN_BINARYOPERATORIMPLEMENTATIONS_H_ */
