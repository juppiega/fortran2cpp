
#ifndef FTN_ARRAY_H_
#define FTN_ARRAY_H_
#include "ftn_ArrayBase.h"

namespace ftn
{
template<class Scalar>
class Array: public ArrayBase<Array<Scalar>, Scalar>
{
private:
	bool isAllocated;
	std::vector<dim_type> beginIndices;
	std::vector<dim_type> endIndices;
	friend class MDArrayRCP<Scalar> ;
	MDArrayRCP<Scalar> mdArray;

	dim_type findInitializationValues (dim_type initVal);
	dim_type findInitializationValues (span initVal);

	void indexOutOfBounds (dim_type index, int dimNumber) const;
	void linearIndexOutOfBounds (dim_type index) const;

public:

	template<class Derived>
	Array (OperatorBase<Derived, Scalar> const& array);

	template<class Derived>
	Array<Scalar>& operator= (OperatorBase<Derived, Scalar> const& array);

	Array (dim_type initVal);
	Array (span initVal);

	Scalar operator() (dim_type index) const;
	Scalar& operator() (dim_type index);

	Scalar linear (dim_type index) const;
	Scalar& linear (dim_type index);

	int numDims () const;

	Array<dim_type> shape () const;

	size_t size () const;
	size_t size (size_t dimNumber) const;

	Array& operator= (const Scalar& x);

	std::string toString () const;
};
}

#endif /* FTN_ARRAY_H_ */
