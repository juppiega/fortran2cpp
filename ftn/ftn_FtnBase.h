
#ifndef FTN_FTNBASE_H_
#define FTN_FTNBASE_H_
#include "ftn_typedefs.h"

namespace ftn
{
template<class Derived, class Scalar>
class FtnBase
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

//	Array<dim_type> shape () const
//	{
//		return static_cast<Derived const&>(*this).shape();
//	}
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
	friend std::ostream& operator<< (std::ostream & os, const FtnBase<T1, T2>& arr);
};

template<class Derived, class Scalar>
std::ostream& operator<< (std::ostream & os, const FtnBase<Derived, Scalar>& arr)
{
	os << arr.toString();
	return os;
}

}

#endif /* FTN_FTNBASE_H_ */
