/*
 * ftn_UnaryOperatorImplementation.h
 *
 *  Created on: Oct 10, 2015
 *      Author: juho
 */

#ifndef FTN_UNARYOPERATORIMPLEMENTATION_H_
#define FTN_UNARYOPERATORIMPLEMENTATION_H_
#include "ftn_UnaryOperatorBase.h"
#include <cmath>
#include <boost/math/special_functions/bessel.hpp>

namespace ftn
{
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Unary "-" (minus)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class UnaryMinus: public UnaryOperatorBase<UnaryMinus<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return -val;
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<UnaryMinus<Target, Scalar>, Target, Scalar> const operator- (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<UnaryMinus<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Cosine
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Cosine: public UnaryOperatorBase<Cosine<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::cos(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Cosine<Target, Scalar>, Target, Scalar> cos (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Cosine<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Sine
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Sine: public UnaryOperatorBase<Sine<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::sin(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Sine<Target, Scalar>, Target, Scalar> sin (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Sine<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Tangent function
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Tan: public UnaryOperatorBase<Tan<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::tan(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Tan<Target, Scalar>, Target, Scalar> tan (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Tan<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Abs
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Abs: public UnaryOperatorBase<Abs<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::abs(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Abs<Target, Scalar>, Target, Scalar> abs (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Abs<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Square root
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Sqrt: public UnaryOperatorBase<Sqrt<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::sqrt(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Sqrt<Target, Scalar>, Target, Scalar> sqrt (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Sqrt<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// trunc (aint in Fortran)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Trunc: public UnaryOperatorBase<Trunc<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::trunc(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Trunc<Target, Scalar>, Target, Scalar> trunc (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Trunc<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// ftrunc
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto ftrunc (T1 x)
{
	return (float) std::trunc(x);
}

template<class Target, class Scalar>
class Ftrunc: public UnaryOperatorBase<Ftrunc<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (float) std::trunc(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Ftrunc<Target, Scalar>, Target, Scalar> ftrunc (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Ftrunc<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// dtrunc
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto dtrunc (T1 x)
{
	return (double) std::trunc(x);
}

template<class Target, class Scalar>
class Dtrunc: public UnaryOperatorBase<Dtrunc<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (double) std::trunc(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Dtrunc<Target, Scalar>, Target, Scalar> dtrunc (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Dtrunc<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// ldtrunc
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto ldtrunc (T1 x)
{
	return (long double) std::trunc(x);
}

template<class Target, class Scalar>
class Ldtrunc: public UnaryOperatorBase<Ldtrunc<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (long double) std::trunc(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Ldtrunc<Target, Scalar>, Target, Scalar> ldtrunc (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Ldtrunc<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// round (anint in Fortran)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Round: public UnaryOperatorBase<Round<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::round(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Round<Target, Scalar>, Target, Scalar> round (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Round<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// fround
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto fround (T1 x)
{
	return (float) std::round(x);
}

template<class Target, class Scalar>
class Fround: public UnaryOperatorBase<Fround<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (float) std::round(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Fround<Target, Scalar>, Target, Scalar> fround (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Fround<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// dround
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto dround (T1 x)
{
	return (double) std::round(x);
}

template<class Target, class Scalar>
class Dround: public UnaryOperatorBase<Dround<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (double) std::round(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Dround<Target, Scalar>, Target, Scalar> dround (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Dround<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// ldround
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto ldround (T1 x)
{
	return (long double) std::round(x);
}

template<class Target, class Scalar>
class Ldround: public UnaryOperatorBase<Ldround<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (long double) std::round(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Ldround<Target, Scalar>, Target, Scalar> ldround (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Ldround<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// sround
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto sround (T1 x)
{
	return (x >= 0) ? (short) (x + 0.5) : (short) (x - 0.5);
}

template<class Target, class Scalar>
class Sround: public UnaryOperatorBase<Sround<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (val >= 0) ? (short) (val + 0.5) : (short) (val - 0.5);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Sround<Target, Scalar>, Target, Scalar> sround (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Sround<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// iround
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto iround (T1 x)
{
	return (x >= 0) ? (int) (x + 0.5) : (int) (x - 0.5);
}

template<class Target, class Scalar>
class Iround: public UnaryOperatorBase<Iround<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (val >= 0) ? (int) (val + 0.5) : (int) (val - 0.5);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Iround<Target, Scalar>, Target, Scalar> iround (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Iround<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// llround
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto llround (T1 x)
{
	return (x >= 0) ? (long long) (x + 0.5) : (long long) (x - 0.5);
}

template<class Target, class Scalar>
class Llround: public UnaryOperatorBase<Llround<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (val >= 0) ? (long long) (val + 0.5) : (long long) (val - 0.5);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Llround<Target, Scalar>, Target, Scalar> llround (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Llround<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Arcus sine
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class ArcSine: public UnaryOperatorBase<ArcSine<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::asin(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<ArcSine<Target, Scalar>, Target, Scalar> asin (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<ArcSine<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Arcus cosine
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class ArcCosine: public UnaryOperatorBase<ArcCosine<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::acos(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<ArcCosine<Target, Scalar>, Target, Scalar> acos (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<ArcCosine<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Arcus tangent
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class ArcTan: public UnaryOperatorBase<ArcTan<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::atan(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<ArcTan<Target, Scalar>, Target, Scalar> atan (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<ArcTan<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Hyperbolic sine
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class SinH: public UnaryOperatorBase<SinH<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::sinh(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<SinH<Target, Scalar>, Target, Scalar> sinh (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<SinH<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Hyperbolic cosine
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class CosH: public UnaryOperatorBase<CosH<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::cosh(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<CosH<Target, Scalar>, Target, Scalar> cosh (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<CosH<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Hyperbolic tangent
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class TanH: public UnaryOperatorBase<TanH<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::tanh(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<TanH<Target, Scalar>, Target, Scalar> tanh (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<TanH<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Hyperbolic arcus cosine
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class ArcCosH: public UnaryOperatorBase<ArcCosH<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::acosh(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<ArcCosH<Target, Scalar>, Target, Scalar> acosh (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<ArcCosH<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Hyperbolic arcus sine
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class ArcSinH: public UnaryOperatorBase<ArcSinH<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::asinh(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<ArcSinH<Target, Scalar>, Target, Scalar> asinh (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<ArcSinH<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Hyperbolic arcus tangent
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class ArcTanH: public UnaryOperatorBase<ArcTanH<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::atanh(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<ArcTanH<Target, Scalar>, Target, Scalar> atanh (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<ArcTanH<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Exponential function
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Exp: public UnaryOperatorBase<Exp<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::exp(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Exp<Target, Scalar>, Target, Scalar> exp (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Exp<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Logarithm function
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Log: public UnaryOperatorBase<Log<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::log(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Log<Target, Scalar>, Target, Scalar> log (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Log<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Log10
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Log10: public UnaryOperatorBase<Log10<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::log10(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Log10<Target, Scalar>, Target, Scalar> log10 (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Log10<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Log2
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Log2: public UnaryOperatorBase<Log2<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::log2(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Log2<Target, Scalar>, Target, Scalar> log2 (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Log2<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Gamma function
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto gamma (T1 x)
{
	return std::tgamma(x);
}

template<class Target, class Scalar>
class Gamma: public UnaryOperatorBase<Gamma<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::tgamma(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Gamma<Target, Scalar>, Target, Scalar> gamma (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Gamma<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Logarithm of the Gamma function.
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto log_gamma (T1 x)
{
	return std::lgamma(x);
}

template<class Target, class Scalar>
class Lgamma: public UnaryOperatorBase<Lgamma<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::tgamma(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Lgamma<Target, Scalar>, Target, Scalar> log_gamma (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Lgamma<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Error function
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Erf: public UnaryOperatorBase<Erf<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::erf(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Erf<Target, Scalar>, Target, Scalar> erf (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Erf<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Complementary error function
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class Erfc: public UnaryOperatorBase<Erfc<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::erfc(val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Erfc<Target, Scalar>, Target, Scalar> erfc (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Erfc<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Scaled complementary error function (Numerically inaccurate!)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto erfc_scaled (T1 x)
{
	return std::erfc(x) * std::exp(x*x);
}

template<class Target, class Scalar>
class Erfc_scaled: public UnaryOperatorBase<Erfc_scaled<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return std::erfc(val) * std::exp(val*val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Erfc_scaled<Target, Scalar>, Target, Scalar> erfc_scaled (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Erfc_scaled<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Bessel J_0
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto bessel_j0 (T1 x)
{
	return boost::math::cyl_bessel_j(0, x);
}

template<class Target, class Scalar>
class Bessel_J0: public UnaryOperatorBase<Bessel_J0<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return boost::math::cyl_bessel_j(0, val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Bessel_J0<Target, Scalar>, Target, Scalar> bessel_j0 (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Bessel_J0<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Bessel J_1
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto bessel_j1 (T1 x)
{
	return boost::math::cyl_bessel_j(1, x);
}

template<class Target, class Scalar>
class Bessel_J1: public UnaryOperatorBase<Bessel_J1<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return boost::math::cyl_bessel_j(1, val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Bessel_J1<Target, Scalar>, Target, Scalar> bessel_j1 (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Bessel_J1<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Bessel Y_0
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto bessel_y0 (T1 x)
{
	return boost::math::cyl_neumann(0, x);
}

template<class Target, class Scalar>
class Bessel_Y0: public UnaryOperatorBase<Bessel_Y0<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return boost::math::cyl_neumann(0, val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Bessel_Y0<Target, Scalar>, Target, Scalar> bessel_y0 (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Bessel_Y0<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Bessel Y_1
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto bessel_y1 (T1 x)
{
	return boost::math::cyl_neumann(1, x);
}

template<class Target, class Scalar>
class Bessel_Y1: public UnaryOperatorBase<Bessel_Y1<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return boost::math::cyl_neumann(1, val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Bessel_Y1<Target, Scalar>, Target, Scalar> bessel_y1 (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Bessel_Y1<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// sceil
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto sceil (T1 x)
{
	return (x < 0) ? (short) x : (short) (std::ceil(x) + 0.5);
}

template<class Target, class Scalar>
class Sceil: public UnaryOperatorBase<Sceil<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (val < 0) ? (short) val : (short) (std::ceil(val) + 0.5);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Sceil<Target, Scalar>, Target, Scalar> sceil (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Sceil<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// iceil
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto iceil (T1 x)
{
	return (x < 0) ? (int) x : (int) (std::ceil(x) + 0.5);
}

template<class Target, class Scalar>
class Iceil: public UnaryOperatorBase<Iceil<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (val < 0) ? (int) val : (int) (std::ceil(val) + 0.5);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Iceil<Target, Scalar>, Target, Scalar> iceil (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Iceil<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// llceil
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto llceil (T1 x)
{
	return (x < 0) ? (long long) x : (long long) (std::ceil(x) + 0.5);
}

template<class Target, class Scalar>
class Llceil: public UnaryOperatorBase<Llceil<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (val < 0) ? (long long) val : (long long) (std::ceil(val) + 0.5);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Llceil<Target, Scalar>, Target, Scalar> llceil (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Llceil<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// sfloor
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto sfloor (T1 x)
{
	return (x >= 0) ? (short) x : (short) (std::floor(x) - 0.5);
}

template<class Target, class Scalar>
class Sfloor: public UnaryOperatorBase<Sfloor<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (val >= 0) ? (short) val : (short) (std::floor(val) - 0.5);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Sfloor<Target, Scalar>, Target, Scalar> sfloor (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Sfloor<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// ifloor
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto ifloor (T1 x)
{
	return (x >= 0) ? (int) x : (int) (std::floor(x) - 0.5);
}

template<class Target, class Scalar>
class Ifloor: public UnaryOperatorBase<Ifloor<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (val >= 0) ? (int) val : (int) (std::floor(val) - 0.5);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Ifloor<Target, Scalar>, Target, Scalar> ifloor (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Ifloor<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// llfloor
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto llfloor (T1 x)
{
	return (x >= 0) ? (long long) x : (long long) (std::floor(x) - 0.5);
}

template<class Target, class Scalar>
class Llfloor: public UnaryOperatorBase<Llfloor<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return (val >= 0) ? (long long) val : (long long) (std::floor(val) - 0.5);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Llfloor<Target, Scalar>, Target, Scalar> llfloor (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Llfloor<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// asFloat (real(x,4) in Fortran)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto asFloat (T1 x)
{
	return static_cast<float> (x);
}

template<class Target, class Scalar>
class AsFloat: public UnaryOperatorBase<AsFloat<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return static_cast<float> (val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<AsFloat<Target, Scalar>, Target, Scalar> asFloat (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<AsFloat<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// asDouble (dble in Fortran)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto asDouble (T1 x)
{
	return static_cast<double> (x);
}

template<class Target, class Scalar>
class AsDouble: public UnaryOperatorBase<AsDouble<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return static_cast<double> (val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<AsDouble<Target, Scalar>, Target, Scalar> asDouble (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<AsDouble<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// asLongDouble (real(x,16) in Fortran)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto asLongDouble (T1 x)
{
	return static_cast<long double> (x);
}

template<class Target, class Scalar>
class AsLongDouble: public UnaryOperatorBase<AsLongDouble<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return static_cast<long double> (val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<AsLongDouble<Target, Scalar>, Target, Scalar> asLongDouble (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<AsLongDouble<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// asShort (int(x, 2) in Fortran)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto asShort (T1 x)
{
	return static_cast<short> (x);
}

template<class Target, class Scalar>
class AsShort: public UnaryOperatorBase<AsShort<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return static_cast<short> (val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<AsShort<Target, Scalar>, Target, Scalar> asShort (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<AsShort<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// asInt (int(x, 4) in Fortran)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto asInt (T1 x)
{
	return static_cast<int> (x);
}

template<class Target, class Scalar>
class AsInt: public UnaryOperatorBase<AsInt<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return static_cast<int> (val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<AsInt<Target, Scalar>, Target, Scalar> asInt (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<AsInt<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// asLongLong (int(x, 8) in Fortran)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<!isFtnType<T1>::value, bool>::type>
auto asLongLong (T1 x)
{
	return static_cast<long long> (x);
}

template<class Target, class Scalar>
class AsLongLong: public UnaryOperatorBase<AsLongLong<Target, Scalar>, Target, Scalar>
{
public:
	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return static_cast<long long> (val);
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<AsLongLong<Target, Scalar>, Target, Scalar> asLongLong (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<AsLongLong<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

}


#endif /* FTN_UNARYOPERATORIMPLEMENTATION_H_ */
