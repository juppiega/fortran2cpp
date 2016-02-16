#ifndef FTN_BINARYOPERATORBASE_H_
#define FTN_BINARYOPERATORBASE_H_
#include "ftn_OperatorBase.h"
#include <type_traits>

/* TODO
 *
 */

namespace ftn
{

template<class Derived, class LeftSide, class RightSide, class Scalar>
class BinaryOperatorBase: public OperatorBase<BinaryOperatorBase<Derived, LeftSide, RightSide, Scalar>, Scalar>
{
	template<typename T> struct type { };
protected:
	LeftSide const& first;
	RightSide const& second;
public:
	BinaryOperatorBase (ArrayBase<LeftSide, Scalar> const& a, ArrayBase<RightSide, Scalar> const& b) :
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
	BinaryOperatorBase (LeftSide const& a, ArrayBase<RightSide, Scalar> const& b) :
			first(a), second(b){}
	BinaryOperatorBase (ArrayBase<LeftSide, Scalar> const& a, RightSide const& b) :
			first(a), second(b){}

	size_t size () const
	{
		return size(std::is_fundamental<LeftSide>());
	}
	size_t size (size_t dimNumber) const
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

	Scalar linear (dim_type index) const
	{
		return static_cast<Derived const&>(*this).linear(index);
	}

	Array<dim_type> shape () const
	{
		return shape(std::is_fundamental<LeftSide>());
	}

	Array<dim_type> lbound () const
	{
		Array<dim_type> lbounds(numDims());
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
private:
	size_t size (std::false_type) const
	{
		return first.size();
	}
	size_t size (std::true_type) const
	{
		return second.size();
	}
	size_t size (size_t dimNumber, std::false_type) const
	{
		return first.size();
	}
	size_t size (size_t dimNumber, std::true_type) const
	{
		return second.size();
	}
	int numDims (std::false_type) const
	{
		return first.numDims();
	}
	int numDims (std::true_type) const
	{
		return second.numDims();
	}
	Array<dim_type> shape (std::false_type) const
	{
		return first.shape();
	}
	Array<dim_type> shape (std::true_type) const
	{
		return second.shape();
	}
};
}

#endif /* FTN_BINARYOPERATORBASE_H_ */
