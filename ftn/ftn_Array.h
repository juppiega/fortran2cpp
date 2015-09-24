#ifndef FTN_ARRAY_H_
#define FTN_ARRAY_H_
#include "ftn_ArrayNonConstBase.h"
#include "ftn_Span.h"

namespace ftn
{

template<class Scalar>
class ArrayView;

template<class Scalar>
class Array: public ArrayNonConstBase<Array<Scalar>, Scalar>
{
private:
	bool isAllocated;
	std::vector<dim_type> beginIndices;
	MDArrayRCP<Scalar> mdArray;

	dim_type findInitializationValues (dim_type initVal);
	dim_type findInitializationValues (span initVal);

	void indexOutOfBounds (dim_type index, int dimNumber) const;
	void linearIndexOutOfBounds (dim_type index) const;

public:

	template<class T1, class... OtherTypes>
	explicit Array (T1 m, OtherTypes... otherInitVals);

	template<class Derived, class Scalar2>
	Array (ArrayBase<Derived, Scalar2> const& array);

	Array (Array<Scalar>& array);

	Array (Array<Scalar>&& other) noexcept;

	Array<Scalar>& operator= (Array<Scalar>&& other) noexcept;

	template<class Derived, class Scalar2>
	Array<Scalar>& operator= (ArrayBase<Derived, Scalar2> const& array);

	Array<Scalar>& operator= (Array<Scalar>& array);

	Scalar operator() (dim_type index) const;
	Scalar& operator() (dim_type index);

	ArrayView<Scalar> operator() (span indexSpan) const;
	ArrayView<Scalar> operator() (span indexSpan);

	Scalar linear (dim_type index) const;
	Scalar& linear (dim_type index);

	int numDims () const;

	Array<dim_type> shape () const;

	Array<dim_type> lbound () const;
	dim_type lbound (dim_type dimNumber) const;

	Array<dim_type> ubound () const;
	dim_type ubound (dim_type dimNumber) const;

	size_t size () const;
	size_t size (size_t dimNumber) const;

	template<class Derived, class Scalar2>
	void reshape (ArrayBase<Derived, Scalar2> const& newDims); // Lisaa Ftn ja Operator Baseen

	Array<Scalar>& operator= (const Scalar& x);

	std::string toString () const;
};
}

#endif /* FTN_ARRAY_H_ */
