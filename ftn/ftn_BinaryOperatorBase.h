#ifndef FTN_BINARYOPERATORBASE_H_
#define FTN_BINARYOPERATORBASE_H_
#include "ftn_OperatorBase.h"
#include <type_traits>

/* TODO
 *
 */

namespace ftn
{

template<class Derived, class LeftSide, class RightSide, class ScalarL, class ScalarR>
class BinaryOperatorBase: public OperatorBase<BinaryOperatorBase<Derived, LeftSide, RightSide, ScalarL, ScalarR>, ScalarL>
{
	template<typename T> struct type { };
protected:
	LeftSide const& first;
	RightSide const& second;
public:
	BinaryOperatorBase (ArrayBase<LeftSide, ScalarL> const& a, ArrayBase<RightSide, ScalarR> const& b) :
			first(a), second(b)
	{
#ifdef FTN_DEBUG
		if (!sameShape(a, b))
		{
			std::ostringstream strStream;
			strStream << "Trying to apply a binary operator between shapes: " << a.shape() << " and " << b.shape() << "!";
			throw std::domain_error(strStream.str());
		}
#endif
	}
	BinaryOperatorBase (LeftSide const& a, ArrayBase<RightSide, ScalarR> const& b) :
			first(a), second(b){}
	BinaryOperatorBase (ArrayBase<LeftSide, ScalarL> const& a, RightSide const& b) :
			first(a), second(b){}

	size_t size () const
	{
		return size(std::is_fundamental<LeftSide>());
	}
	size_t size (int dimNumber) const
	{
		return size(dimNumber, std::is_fundamental<LeftSide>());
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

	int numDims () const
	{
		return numDims(std::is_fundamental<LeftSide>());
	}

	template<class T1, class T2>
	inline auto eval (T1 const& left, T2 const& right) const
	{
		return static_cast<Derived const&>(*this).eval(left, right);
	}

	auto linear (size_t index) const
	{
		return linear(index, std::is_fundamental<LeftSide>(), std::is_fundamental<RightSide>());
	}

	Array<dim_type, 1> shape () const
	{
		return shape(std::is_fundamental<LeftSide>());
	}

	Array<dim_type, 1> lbound () const
	{
		Array<dim_type, 1> lbounds(numDims());
		lbounds = 1;
		return lbounds;
	}

	auto zb(dim_type m) const
	{
		return zb(m, std::is_fundamental<LeftSide>(), std::is_fundamental<RightSide>());
	}

	auto zb(dim_type m, dim_type n) const
	{
		return zb(m, n, std::is_fundamental<LeftSide>(), std::is_fundamental<RightSide>());
	}

	auto zb(dim_type m, dim_type n, dim_type o) const
	{
		return zb(m, n, o, std::is_fundamental<LeftSide>(), std::is_fundamental<RightSide>());
	}

	auto zb(dim_type m, dim_type n, dim_type o, dim_type p) const
	{
		return zb(m, n, o, p, std::is_fundamental<LeftSide>(), std::is_fundamental<RightSide>());
	}

	constexpr bool isArrayView() const
	{
		return isArrayView(std::is_fundamental<LeftSide>(), std::is_fundamental<RightSide>());
	}

	operator Derived& ()
	{
		return static_cast<Derived&>(*this);
	}
	operator Derived const& () const
	{
		return static_cast<const Derived&>(*this);
	}
private:
	auto linear (size_t index, std::false_type, std::true_type) const
	{
		return eval(first.linear(index), second);
	}

	auto linear (size_t index, std::true_type, std::false_type) const
	{
		return eval(first, second.linear(index));
	}

	auto linear (size_t index, std::false_type, std::false_type) const
	{
		return eval(first.linear(index), second.linear(index));
	}

	auto zb(dim_type m, std::false_type, std::true_type) const
	{
		return eval(first.zb(m), second);
	}

	auto zb(dim_type m, std::true_type, std::false_type) const
	{
		return eval(first, second.zb(m));
	}

	auto zb(dim_type m, std::false_type, std::false_type) const
	{
		return eval(first.zb(m), second.zb(m));
	}

	auto zb(dim_type m, dim_type n, std::false_type, std::true_type) const
	{
		return eval(first.zb(m,n), second);
	}

	auto zb(dim_type m, dim_type n, std::true_type, std::false_type) const
	{
		return eval(first, second.zb(m,n));
	}

	auto zb(dim_type m, dim_type n, std::false_type, std::false_type) const
	{
		return eval(first.zb(m,n), second.zb(m,n));
	}

	auto zb(dim_type m, dim_type n, dim_type o, std::false_type, std::true_type) const
	{
		return eval(first.zb(m,n,o), second);
	}

	auto zb(dim_type m, dim_type n, dim_type o, std::true_type, std::false_type) const
	{
		return eval(first, second.zb(m,n,o));
	}

	auto zb(dim_type m, dim_type n, dim_type o, std::false_type, std::false_type) const
	{
		return eval(first.zb(m,n,o), second.zb(m,n,o));
	}

	auto zb(dim_type m, dim_type n, dim_type o, dim_type p, std::false_type, std::true_type) const
	{
		return eval(first.zb(m,n,o,p), second);
	}

	auto zb(dim_type m, dim_type n, dim_type o, dim_type p, std::true_type, std::false_type) const
	{
		return eval(first, second.zb(m,n,o,p));
	}

	auto zb(dim_type m, dim_type n, dim_type o, dim_type p, std::false_type, std::false_type) const
	{
		return eval(first.zb(m,n,o,p), second.zb(m,n,o,p));
	}

	constexpr bool isArrayView(const std::false_type, const std::true_type) const
	{
		return first.isArrayView();
	}

	constexpr bool isArrayView(const std::true_type, const std::false_type) const
	{
		return second.isArrayView();
	}

	constexpr bool isArrayView(const std::false_type, const std::false_type) const
	{
		return first.isArrayView() || second.isArrayView();
	}

	size_t size (std::false_type) const
	{
		return first.size();
	}
	size_t size (std::true_type) const
	{
		return second.size();
	}
	size_t size (int dimNumber, std::false_type) const
	{
		return first.size(dimNumber);
	}
	size_t size (int dimNumber, std::true_type) const
	{
		return second.size(dimNumber);
	}
	int numDims (std::false_type) const
	{
		return first.numDims();
	}
	int numDims (std::true_type) const
	{
		return second.numDims();
	}
	Array<dim_type, 1> shape (std::false_type) const
	{
		return first.shape();
	}
	Array<dim_type, 1> shape (std::true_type) const
	{
		return second.shape();
	}
};
}

#endif /* FTN_BINARYOPERATORBASE_H_ */
