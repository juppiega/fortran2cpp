/*
 * UnaryOperatorBase.h
 *
 *  Created on: Oct 10, 2015
 *      Author: juho
 */

#ifndef FTN_UNARYOPERATORBASE_H_
#define FTN_UNARYOPERATORBASE_H_
#include "ftn_OperatorBase.h"

namespace ftn
{
template<class Derived, class Target, class Scalar>
class UnaryOperatorBase: public OperatorBase<UnaryOperatorBase<Derived, Target, Scalar>, Scalar>
{
protected:
	Target const& target;
public:
	UnaryOperatorBase (ArrayBase<Target, Scalar> const& a) :
			target(a)
	{
	}
	size_t size () const
	{
		return target.size();
	}
	size_t size (size_t dimNumber) const
	{
		return target.size(dimNumber);
	}

	dim_type lbound (dim_type dimNumber) const
	{
#ifdef FTN_DEBUG
		if (dimNumber < 1 || dimNumber > numDims())
		{
			std::ostringstream strStream;
			strStream << "Argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
			throw std::invalid_argument(strStream.str());
		}
#endif
		return 1;
	}

	template<class T1>
	inline auto eval (T1 const& val) const
	{
		return static_cast<Derived const&>(*this).eval(val);
	}

	auto zb(dim_type m) const
	{
		return target(m);
	}

	auto zb(dim_type m, dim_type n) const
	{
		return target(m, n);
	}

	auto zb(dim_type m, dim_type n, dim_type o) const
	{
		return target(m, n, o);
	}

	auto zb(dim_type m, dim_type n, dim_type o, dim_type p) const
	{
		return target(m, n, o, p);
	}

	auto linear (size_t index) const
	{
		return eval(target.linear(index));
	}

	int numDims () const
	{
		return target.numDims();
	}

	Array<dim_type, 1> shape () const
	{
		return target.shape();
	}

	Array<dim_type, 1> lbound () const
	{
		Array<dim_type, 1> lbounds(numDims());
		lbounds = 1;
		return lbounds;
	}

	operator Derived& ()
	{
		return static_cast<Derived&>(*this);
	}
	operator Derived const& () const
	{
		return static_cast<const Derived&>(*this);
	}

	constexpr bool isArrayView() const
	{
		return target.isArrayView();
	}
};
}

#endif /* FTN_UNARYOPERATORBASE_H_ */
