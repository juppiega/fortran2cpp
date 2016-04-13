#ifndef FTN_ARRAYBASE_H_
#define FTN_ARRAYBASE_H_
#include "ftn_typedefs.h"

namespace ftn
{

template<class Scalar, int nDims, bool isAllocatable = false>
class Array;

template<class Derived, class Scalar>
class ArrayBase
{
public:
	// Recognition of weather the type is member of the FTN library is based on containing this rather random typedef.
	// It's virtually impossible that a user-defined class would contain such a type.
	typedef ArrayBase<Derived, Scalar> PossibleBaseInFtn_WithRandomSequence_5CqH36Rz9c9ELo79Mi257usV;

	size_t size() const
	{
		return static_cast<Derived const&>(*this).size();
	}
	size_t size(int dimNumber) const
	{
		return static_cast<Derived const&>(*this).size(dimNumber);
	}

	dim_type lbound(dim_type dimNumber) const
	{
		return static_cast<Derived const&>(*this).lbound(dimNumber);
	}

	auto zb(dim_type m) const
	{
		return static_cast<Derived const&>(*this).zb(m);
	}
	auto zb(dim_type m, dim_type n) const
	{
		return static_cast<Derived const&>(*this).zb(m, n);
	}
	auto zb(dim_type m, dim_type n, dim_type o) const
	{
		return static_cast<Derived const&>(*this).zb(m, n, o);
	}
	auto zb(dim_type m, dim_type n, dim_type o, dim_type p) const
	{
		return static_cast<Derived const&>(*this).zb(m, n, o, p);
	}

	auto linear(size_t index) const
	{
		return static_cast<Derived const&>(*this).linear(index);
	}
	Scalar& linear(size_t index)
	{
		return static_cast<Derived&>(*this).linear(index);
	}
	Array<dim_type, 1> shape() const;
	Array<dim_type, 1> lbound() const;

	int numDims() const
	{
		return static_cast<Derived const&>(*this).numDims();
	}
	std::string toString() const
	{
		return static_cast<Derived const&>(*this).toString();
	}

	operator Derived&()
	{
		return static_cast<Derived&>(*this);
	}
	operator Derived const&() const
	{
		return static_cast<const Derived&>(*this);
	}

	operator Scalar() const;

	constexpr bool isArrayView() const
	{
		return static_cast<Derived const&>(*this).isArrayView();
	}

	template<class T1, class T2>
	friend std::ostream& operator<<(std::ostream & os,
			const ArrayBase<T1, T2>& arr);
};

template<class Derived, class Scalar>
std::ostream& operator<<(std::ostream & os,
		const ArrayBase<Derived, Scalar>& arr)
{
	os << arr.toString();
	return os;
}

void checkNonNegativeConstructLength(dim_type length)
{
	if (length < 0)
	{
		std::ostringstream strStream;
		strStream << "The length of an array cannot be negative! Received "
				<< length;
		throw std::domain_error(strStream.str());
	}
}

//template<class Derived, class Scalar>
//ArrayBase<Derived, Scalar>::operator Scalar() const
//{
//#ifdef FTN_DEBUG
//	if (size() != 1)
//	{
//		std::ostringstream strStream;
//		strStream << "Trying to convert an array of size " << size() << " into scalar!";
//		throw std::domain_error(strStream.str());
//	}
//#endif
//	return linear(0);
//}

}

#endif /* FTN_ARRAYBASE_H_ */
