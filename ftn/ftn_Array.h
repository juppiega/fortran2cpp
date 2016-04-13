#ifndef FTN_ARRAY_H_
#define FTN_ARRAY_H_
#include "ftn_ArrayNonConstBase.h"
#include "ftn_Span.h"
#include "ftn_traits.h"

namespace ftn
{
// TODO:
// - Vector subscript (Ei logicalia).
// - Implementoi logical array -funktiot.
// - Implementoi transformational -funktiot (sum, transpose...).
// - Implementoi bitwise -funktiot.
// - Fixed size Array (nykyiseen Array-classiin).
// - Implementoi Fortranin character array- tyyppi.

template<class RefType, int nDims, class Scalar>
class ArrayView;

template<class Scalar, int nDims, bool isAllocatable> // The last one is optional. Specification in ftn_ArrayBase.h
class Array: public ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>
{
private:
	bool _isAllocated;
	int _dimCounter;
	std::array<dim_type, nDims> _beginIndices;
	std::array<size_t, nDims> _strides;
	std::array<dim_type, nDims> _dimLengths;
	Scalar* _mdArray;
	size_t _numel;

	dim_type findInitializationValues(dim_type initVal);
	dim_type findInitializationValues(span initVal);

public:
	using ArrayNonConstBase<Array<Scalar, nDims, isAllocatable>, Scalar>::operator(); // MUISTA LISATA UUSIIN CONTAINEREIHIN!!!!

	template<class T1, class ... OtherTypes>
	explicit Array(T1 m, OtherTypes ... otherInitVals);

	template<class Derived, class Scalar2>
	Array(ArrayBase<Derived, Scalar2> const& array);

	Array(Array<Scalar, nDims, isAllocatable>& array);

	Array(Array<Scalar, nDims, isAllocatable> && other) noexcept;

	Array<Scalar, nDims, isAllocatable>& operator=(Array<Scalar, nDims, isAllocatable> && other) noexcept;

	template<class Derived, class Scalar2>
	inline Array<Scalar, nDims, isAllocatable>& operator=(ArrayBase<Derived, Scalar2> const& array);

	Array<Scalar, nDims, isAllocatable>& operator=(Array<Scalar, nDims, isAllocatable>& array);

	Scalar zb(dim_type m) const;
	Scalar zb(dim_type m, dim_type n) const;
	Scalar zb(dim_type m, dim_type n, dim_type o) const;
	Scalar zb(dim_type m, dim_type n, dim_type o, dim_type p) const;

	Scalar& zb(dim_type m);
	Scalar& zb(dim_type m, dim_type n);
	Scalar& zb(dim_type m, dim_type n, dim_type o);
	Scalar& zb(dim_type m, dim_type n, dim_type o, dim_type p);

	Scalar operator()(dim_type m) const;
	Scalar operator()(dim_type m, dim_type n) const;
	Scalar operator()(dim_type m, dim_type n, dim_type o) const;
	Scalar operator()(dim_type m, dim_type n, dim_type o, dim_type p) const;

	Scalar& operator()(dim_type m);
	Scalar& operator()(dim_type m, dim_type n);
	Scalar& operator()(dim_type m, dim_type n, dim_type o);
	Scalar& operator()(dim_type m, dim_type n, dim_type o, dim_type p);

	Scalar linear(size_t index) const;
	Scalar& linear(size_t index);

	Array<dim_type, 1> shape() const;

	Array<dim_type, 1> lbound() const;
	dim_type lbound(dim_type dimNumber) const;

	Array<dim_type, 1> ubound() const;
	dim_type ubound(dim_type dimNumber) const;

	size_t linearStride (dim_type dimNumber) const;

	size_t size() const;
	size_t size(int dimNumber) const;

	template<class OtherDimType, long unsigned int T>
	size_t sub2ind (std::array<OtherDimType, T>& ind);

	int numDims () const;

	template<class Derived, class Scalar2>
	void reshape(ArrayBase<Derived, Scalar2> const& newDims); // Lisaa Ftn ja Operator Baseen

	template<class Scalar2>
	typename std::enable_if<!isFtnType<Scalar2>::value, Array<Scalar, nDims, isAllocatable> >::type& operator=(const Scalar2& x);

	constexpr bool isArrayView() const
	{
		return false;
	}

	~Array();

	std::string toString() const;
};
}

#endif /* FTN_ARRAY_H_ */
