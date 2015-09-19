
#ifndef FTN_ARRAYBASE_H_
#define FTN_ARRAYBASE_H_
#include "ftn_typedefs.h"

namespace ftn
{

template<class Scalar>
class Array;

template<class Derived, class Scalar>
class ArrayBase
{
public:
	size_t size () const
	{
		return static_cast<Derived const&>(*this).size();
	}
	size_t size (size_t dimNumber) const
	{
		return static_cast<Derived const&>(*this).size(dimNumber);
	}

	dim_type lbound (dim_type dimNumber) const
	{
		return static_cast<Derived const&>(*this).lbound(dimNumber);
	}

	Scalar operator() (dim_type index) const
	{
		return static_cast<Derived const&>(*this)(index);
	}
	Scalar& operator() (dim_type index)
	{
		return static_cast<Derived&>(*this)(index);
	}

	Scalar linear (dim_type index) const
	{
		return static_cast<Derived const&>(*this).linear(index);
	}
	Scalar& linear (dim_type index)
	{
		return static_cast<Derived&>(*this).linear(index);
	}
	Array<dim_type> shape () const;
	Array<dim_type> lbound () const;

	template<class Derived2, class Scalar2>
	bool sameShapeAndContents(ArrayBase<Derived2, Scalar2> const& array) const
	{
		return static_cast<Derived const&>(*this).sameShapeAndContents(array);
	}

	template<class Derived2, class Scalar2>
	bool sameShape(ArrayBase<Derived2, Scalar2> const& array) const
	{
		return static_cast<Derived const&>(*this).sameShape(array);
	}

	template<class Derived2, class Scalar2>
	bool sameContents(ArrayBase<Derived2, Scalar2> const& array) const
	{
		return static_cast<Derived const&>(*this).sameContents(array);
	}

	int numDims () const
	{
		return static_cast<Derived const&>(*this).numDims();
	}
	std::string toString () const
	{
		return static_cast<Derived const&>(*this).toString();
	}

	operator Derived& ()
	{
		return static_cast<Derived&>(*this);
	}
	operator Derived const& () const
	{
		return static_cast<const Derived&>(*this);
	}

	template<class T1, class T2>
	friend std::ostream& operator<< (std::ostream & os, const ArrayBase<T1, T2>& arr);
};

template<class Derived, class Scalar>
std::ostream& operator<< (std::ostream & os, const ArrayBase<Derived, Scalar>& arr)
{
	os << arr.toString();
	return os;
}

void checkNonNegativeConstructLength(dim_type length)
{
	if (length < 0)
	{
		std::ostringstream strStream;
		strStream << "The length of an array cannot be negative! Received " << length;
		throw std::domain_error(strStream.str());
	}
}

}

#endif /* FTN_ARRAYBASE_H_ */
