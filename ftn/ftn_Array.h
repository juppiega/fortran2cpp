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
	bool _isAllocated;
	int _nDims;
	std::array<dim_type, maxDims> _beginIndices;
	std::array<size_t, maxDims> _strides;
	std::array<dim_type, maxDims> _dimLengths;
	std::vector<Scalar> _mdArray;

	dim_type findInitializationValues(dim_type initVal);
	dim_type findInitializationValues(span initVal);

public:
	//using ArrayNonConstBase<Array<Scalar>, Scalar>::operator();

	template<class T1, class ... OtherTypes>
	explicit Array(T1 m, OtherTypes ... otherInitVals);

	template<class Derived, class Scalar2>
	Array(ArrayBase<Derived, Scalar2> const& array);

	Array(Array<Scalar>& array);

	Array(Array<Scalar> && other) noexcept;

	Array<Scalar>& operator=(Array<Scalar> && other) noexcept;

	template<class Derived, class Scalar2>
	Array<Scalar>& operator=(ArrayBase<Derived, Scalar2> const& array);

	Array<Scalar>& operator=(Array<Scalar>& array);

	Scalar operator()(dim_type m) const;
	Scalar operator()(dim_type m, dim_type n) const;
	Scalar operator()(dim_type m, dim_type n, dim_type o) const;
	Scalar operator()(dim_type m, dim_type n, dim_type o, dim_type p) const;

	Scalar& operator()(dim_type m);
	Scalar& operator()(dim_type m, dim_type n);
	Scalar& operator()(dim_type m, dim_type n, dim_type o);
	Scalar& operator()(dim_type m, dim_type n, dim_type o, dim_type p);

	Scalar linear(dim_type index) const;
	Scalar& linear(dim_type index);

	Array<dim_type> shape() const;

	Array<dim_type> lbound() const;
	dim_type lbound(dim_type dimNumber) const;

	Array<dim_type> ubound() const;
	dim_type ubound(dim_type dimNumber) const;

	size_t size() const;
	size_t size(size_t dimNumber) const;

	int numDims () const;

	template<class Derived, class Scalar2>
	void reshape(ArrayBase<Derived, Scalar2> const& newDims); // Lisaa Ftn ja Operator Baseen

	Array<Scalar>& operator=(const Scalar& x);

	std::string toString() const;

	int dimNum()
	{
		static int timesCalled = 0;
		timesCalled++;
		return timesCalled-1;
	}
};
}

#endif /* FTN_ARRAY_H_ */
