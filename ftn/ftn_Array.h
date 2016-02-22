#ifndef FTN_ARRAY_H_
#define FTN_ARRAY_H_
#include "ftn_ArrayNonConstBase.h"
#include "ftn_Span.h"

namespace ftn
{
// TODO:
// - Lisää Arraylle optional template parameter, joka kertoo, onko Dynamic shape (defaulttina false).
// - Lisää template, joka kertoo, onko jokin luokka peritty ArrayBasesta.
// - Lisää constexpr-funktio jokaiselle luokalle, joka kertoo, onko kyseessä ArrayView (voi vaihdella ArrayRef:ssa, joten on oltava funktio jokaisessa tyypissä erikseen!).
// - Lisää Array:lle ja ArrayViewille 0-pohjaiset (m,n,o,...):t.
// - Lisää operaattoreille moniulotteiset 0-pohjaiset (m,n,o,...):t.
// - Array:ssa assignment lineaarinen, jos operaattori ei sisällä yhtään ArrayView:a. Muutoin käytä (m,n,o,...)
// - ArrayView:ssa assignment aina käyttäen (m,n,o,...):a.
// - Mieti, milloin assignmentissa tulee ottaa huomioon temporaryt.
template<class RefType, int nDims, class Scalar>
class ArrayView;

template<class Scalar>
class Array: public ArrayNonConstBase<Array<Scalar>, Scalar>
{
private:
	bool _isAllocated;
	int _nDims;
	int _dimCounter;
	std::array<dim_type, maxDims> _beginIndices;
	std::array<size_t, maxDims> _strides;
	std::array<dim_type, maxDims> _dimLengths;
	std::vector<Scalar> _mdArray;

	dim_type findInitializationValues(dim_type initVal);
	dim_type findInitializationValues(span initVal);

public:
	using ArrayNonConstBase<Array<Scalar>, Scalar>::operator(); // MUISTA LISATA UUSIIN CONTAINEREIHIN!!!!

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

	Array<dim_type> shape() const;

	Array<dim_type> lbound() const;
	dim_type lbound(dim_type dimNumber) const;

	Array<dim_type> ubound() const;
	dim_type ubound(dim_type dimNumber) const;

	size_t linearStride (dim_type dimNumber) const;

	size_t size() const;
	size_t size(size_t dimNumber) const;

	template<class OtherDimType, long unsigned int T>
	size_t sub2ind (std::array<OtherDimType, T>& ind);

	int numDims () const;

	template<class Derived, class Scalar2>
	void reshape(ArrayBase<Derived, Scalar2> const& newDims); // Lisaa Ftn ja Operator Baseen

	Array<Scalar>& operator=(const Scalar& x);

	std::string toString() const;
};
}

#endif /* FTN_ARRAY_H_ */
