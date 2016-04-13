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
template<class LeftSide, class RightSide, class ScalarL, class ScalarR>
class ArraySum: public BinaryOperatorBase<ArraySum<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>
{
public:
	template<class T1, class T2>
	inline auto eval (T1 const& left, T2 const& right) const
	{
		return left + right;
	}
};

template<class LeftSide, class RightSide, class ScalarL, class ScalarR, class = typename std::enable_if<isFtnType<LeftSide>::value && isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArraySum<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator+ (
		ArrayBase<LeftSide, ScalarL> const& a, ArrayBase<RightSide, ScalarR> const& b)
{
	return BinaryOperatorBase<ArraySum<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Sum of an Array and a Scalar.
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class ScalarL, class ScalarR = RightSide, class = typename std::enable_if<isFtnType<LeftSide>::value && !isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArraySum<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator+ (
		ArrayBase<LeftSide, ScalarL> const& a, RightSide const& b)
{
	return BinaryOperatorBase<ArraySum<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}

template<class LeftSide, class RightSide, class ScalarR, class ScalarL = LeftSide, class = typename std::enable_if<!isFtnType<LeftSide>::value && isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArraySum<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator+ (
		LeftSide const& a, ArrayBase<RightSide, ScalarR> const& b)
{
	return BinaryOperatorBase<ArraySum<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Difference of two Arrays
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class ScalarL, class ScalarR>
class ArrayDifference: public BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>
{
public:
	template<class T1, class T2>
	inline auto eval (T1 const& left, T2 const& right) const
	{
		return left - right;
	}
};

template<class LeftSide, class RightSide, class ScalarL, class ScalarR, class = typename std::enable_if<isFtnType<LeftSide>::value && isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator- (
		ArrayBase<LeftSide, ScalarL> const& a, ArrayBase<RightSide, ScalarR> const& b)
{
	return BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Difference of an Array and a primitive type.
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

template<class LeftSide, class RightSide, class ScalarL, class ScalarR = RightSide, class = typename std::enable_if<isFtnType<LeftSide>::value && !isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator- (
		ArrayBase<LeftSide, ScalarL> const& a, RightSide const& b)
{
	return BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}

template<class LeftSide, class RightSide, class ScalarR, class ScalarL = LeftSide, class = typename std::enable_if<!isFtnType<LeftSide>::value && isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator- (
		LeftSide const& a, ArrayBase<RightSide, ScalarR> const& b)
{
	return BinaryOperatorBase<ArrayDifference<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Elemental Product of two Arrays
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class ScalarL, class ScalarR>
class ArrayProduct: public BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>
{
public:
	template<class T1, class T2>
	inline auto eval (T1 const& left, T2 const& right) const
	{
		return left * right;
	}
};

template<class LeftSide, class RightSide, class ScalarL, class ScalarR, class = typename std::enable_if<isFtnType<LeftSide>::value && isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator* (
		ArrayBase<LeftSide, ScalarL> const& a, ArrayBase<RightSide, ScalarR> const& b)
{
	return BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Product of an Array and a primitive type.
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

template<class LeftSide, class RightSide, class ScalarL, class ScalarR = RightSide, class = typename std::enable_if<isFtnType<LeftSide>::value && !isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator* (
		ArrayBase<LeftSide, ScalarL> const& a, RightSide const& b)
{
	return BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}

template<class LeftSide, class RightSide, class ScalarR, class ScalarL = LeftSide, class = typename std::enable_if<!isFtnType<LeftSide>::value && isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator* (
		LeftSide const& a, ArrayBase<RightSide, ScalarR> const& b)
{
	return BinaryOperatorBase<ArrayProduct<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Elemental Division of two Arrays
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class ScalarL, class ScalarR>
class ArrayDivision: public BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>
{
public:
	template<class T1, class T2>
	inline auto eval (T1 const& left, T2 const& right) const
	{
		return left / right;
	}
};

template<class LeftSide, class RightSide, class ScalarL, class ScalarR, class = typename std::enable_if<isFtnType<LeftSide>::value && isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator/ (
		ArrayBase<LeftSide, ScalarL> const& a, ArrayBase<RightSide, ScalarR> const& b)
{
	return BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Division of an Array and a primitive type.
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

template<class LeftSide, class RightSide, class ScalarL, class ScalarR = RightSide, class = typename std::enable_if<isFtnType<LeftSide>::value && !isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator/ (
		ArrayBase<LeftSide, ScalarL> const& a, RightSide const& b)
{
	return BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}

template<class LeftSide, class RightSide, class ScalarR, class ScalarL = LeftSide, class = typename std::enable_if<!isFtnType<LeftSide>::value && isFtnType<RightSide>::value, bool>::type>
BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> const operator/ (
		LeftSide const& a, ArrayBase<RightSide, ScalarR> const& b)
{
	return BinaryOperatorBase<ArrayDivision<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Arcus Tangent (2-arguments)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class LeftSide, class RightSide, class ScalarL, class ScalarR>
class ArcTan2: public BinaryOperatorBase<ArcTan2<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>
{
public:
	template<class T1, class T2>
	inline auto eval (T1 const& left, T2 const& right) const
	{
		return std::atan2(left, right);
	}
};

template<class LeftSide, class RightSide, class ScalarL, class ScalarR>
BinaryOperatorBase<ArcTan2<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> atan2 (
		ArrayBase<LeftSide, ScalarL> const& a, ArrayBase<RightSide, ScalarR> const& b)
{
	return BinaryOperatorBase<ArcTan2<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Arcus Tangent (2-arguments). For some strange reason, the Fortran 2008 standard specifies a new
// arcus tangent function: atan(y,x), the behavior which is exactly the same as that of atan2(y,x)!
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// For fundamental types call the standard library function.
template<class T1, class T2, class = typename std::enable_if<!isFtnType<T1>::value && !isFtnType<T2>::value, bool>::type>
auto atan (T1 y, T2 x)
{
	return std::atan2(y, x);
}

// Else throw a new binary operator.
template<class LeftSide, class RightSide, class ScalarL, class ScalarR>
BinaryOperatorBase<ArcTan2<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> atan (
		ArrayBase<LeftSide, ScalarL> const& a, ArrayBase<RightSide, ScalarR> const& b)
{
	return BinaryOperatorBase<ArcTan2<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Bessel J_N
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class T2, class = typename std::enable_if<!isFtnType<T2>::value, bool>::type>
auto bessel_jn (T1 n, T2 x)
{
	return boost::math::cyl_bessel_j(n, x);
}

template<class LeftSide, class RightSide, class ScalarL, class ScalarR>
class Bessel_JN: public BinaryOperatorBase<Bessel_JN<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>
{
public:
	template<class T1, class T2>
	inline auto eval (T1 const& left, T2 const& right) const
	{
		return boost::math::cyl_bessel_j(left, right);
	}
};

template<class LeftSide, class RightSide, class ScalarR, class ScalarL = LeftSide>
BinaryOperatorBase<Bessel_JN<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> bessel_jn (
		LeftSide const& a, ArrayBase<RightSide, ScalarR> const& b) // Exceptionally not ArrayBase<LeftSide, Scalar> const& a!
{
	return BinaryOperatorBase<Bessel_JN<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Bessel Y_N
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class T2, class = typename std::enable_if<!isFtnType<T2>::value, bool>::type>
auto bessel_yn (T1 n, T2 x)
{
	return boost::math::cyl_neumann(n, x);
}

template<class LeftSide, class RightSide, class ScalarL, class ScalarR>
class Bessel_YN: public BinaryOperatorBase<Bessel_YN<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>
{
public:
	template<class T1, class T2>
	inline auto eval (T1 const& left, T2 const& right) const
	{
		return boost::math::cyl_neumann(left, right);
	}
};

template<class LeftSide, class RightSide, class ScalarR, class ScalarL = LeftSide>
BinaryOperatorBase<Bessel_YN<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR> bessel_yn (
		LeftSide const& a, ArrayBase<RightSide, ScalarR> const& b) // Exceptionally not ArrayBase<LeftSide, Scalar> const& a!
{
	return BinaryOperatorBase<Bessel_YN<LeftSide, RightSide, ScalarL, ScalarR>, LeftSide, RightSide, ScalarL, ScalarR>(a, b);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

}


#endif /* FTN_BINARYOPERATORIMPLEMENTATIONS_H_ */
