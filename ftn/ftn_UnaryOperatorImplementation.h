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
	Scalar linear (dim_type i) const
	{
		return -this->target.linear(i);
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
	Scalar linear (dim_type i) const
	{
		return std::cos(this->target.linear(i));
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
	Scalar linear (dim_type i) const
	{
		return std::sin(this->target.linear(i));
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
	Scalar linear (dim_type i) const
	{
		return std::tan(this->target.linear(i));
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
	Scalar linear (dim_type i) const
	{
		return std::abs(this->target.linear(i));
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Abs<Target, Scalar>, Target, Scalar> abs (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Abs<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Arcus sine
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class Target, class Scalar>
class ArcSine: public UnaryOperatorBase<ArcSine<Target, Scalar>, Target, Scalar>
{
public:
	Scalar linear (dim_type i) const
	{
		return std::asin(this->target.linear(i));
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
	Scalar linear (dim_type i) const
	{
		return std::acos(this->target.linear(i));
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
	Scalar linear (dim_type i) const
	{
		return std::atan(this->target.linear(i));
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
	Scalar linear (dim_type i) const
	{
		return std::sinh(this->target.linear(i));
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
	Scalar linear (dim_type i) const
	{
		return std::cosh(this->target.linear(i));
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
	Scalar linear (dim_type i) const
	{
		return std::tanh(this->target.linear(i));
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
	Scalar linear (dim_type i) const
	{
		return std::acosh(this->target.linear(i));
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
	Scalar linear (dim_type i) const
	{
		return std::asinh(this->target.linear(i));
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
	Scalar linear (dim_type i) const
	{
		return std::atanh(this->target.linear(i));
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<ArcTanH<Target, Scalar>, Target, Scalar> atanh (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<ArcTanH<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Bessel J_0
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class = typename std::enable_if<std::is_fundamental<T1>::value, bool>::type>
auto bessel_j0 (T1 x)
{
	return boost::math::cyl_bessel_j(0, x);
}

template<class Target, class Scalar>
class Bessel_J0: public UnaryOperatorBase<Bessel_J0<Target, Scalar>, Target, Scalar>
{
public:
	Scalar linear (dim_type i) const
	{
		return boost::math::cyl_bessel_j(0, this->target.linear(i));
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
template<class T1, class = typename std::enable_if<std::is_fundamental<T1>::value, bool>::type>
auto bessel_j1 (T1 x)
{
	return boost::math::cyl_bessel_j(1, x);
}

template<class Target, class Scalar>
class Bessel_J1: public UnaryOperatorBase<Bessel_J1<Target, Scalar>, Target, Scalar>
{
public:
	Scalar linear (dim_type i) const
	{
		return boost::math::cyl_bessel_j(1, this->target.linear(i));
	}
};

template<class Target, class Scalar>
UnaryOperatorBase<Bessel_J1<Target, Scalar>, Target, Scalar> bessel_j1 (ArrayBase<Target, Scalar> const& a)
{
	return UnaryOperatorBase<Bessel_J1<Target, Scalar>, Target, Scalar>(a);
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

}


#endif /* FTN_UNARYOPERATORIMPLEMENTATION_H_ */
