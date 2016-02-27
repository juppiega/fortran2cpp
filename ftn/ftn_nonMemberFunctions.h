/*
 * ftn_nonMemberFunctions.h
 *
 *  Created on: Sep 20, 2015
 *      Author: juho
 */

#ifndef FTN_NONMEMBERFUNCTIONS_H_
#define FTN_NONMEMBERFUNCTIONS_H_
#include "ftn_ArrayBase.h"
#include <cmath>
#include <ctime>
#include <boost/math/special_functions/bessel.hpp>

namespace ftn
{

template<class Derived, class Scalar, class OtherDerived, class OtherScalar>
bool sameContents(ArrayBase<Derived, Scalar> const& array1,
		ArrayBase<OtherDerived, OtherScalar> const& array2)
{
	size_t n = array1.size();
	if (n == array2.size())
	{
		for (size_t i = 0; i < n; i++)
		{
			if (array1.linear(i) != array2.linear(i))
				return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<class Derived, class Scalar, class OtherDerived, class OtherScalar>
bool sameShape(ArrayBase<Derived, Scalar> const& array1,
		ArrayBase<OtherDerived, OtherScalar> const& array2)
{
	return sameContents(array1.shape(), array2.shape());
}

template<class Derived, class Scalar, class OtherDerived, class OtherScalar>
bool sameShapeAndContents(ArrayBase<Derived, Scalar> const& array1,
		ArrayBase<OtherDerived, OtherScalar> const& array2)
{
	return array1.sameShape(array2) && array1.sameContents(array2);
}

template<size_t N>
std::array<size_t, N> computeArrayStrides(std::array<dim_type, N>& dimLengths)
{
	std::array<size_t, N> strides;
	strides[0] = 1;
	size_t dimProd = 1;
	for (int i = 1; i < (int) N; i++)
	{
		dimProd *= dimLengths[i - 1];
		strides[i] = dimProd;
	}
	return strides;
}

template<class Derived, class Scalar>
void printMat(ArrayNonConstBase<Derived, Scalar> const& array)
{
	for (int i = array.lbound(1); i <= array.ubound(1); i++)
	{
		for (int j = array.lbound(2); j <= array.ubound(2); j++)
			std::cout << array(i, j) << "  ";
		std::cout << std::endl;
	}
}

template<class Derived, class Scalar>
void printCube(ArrayNonConstBase<Derived, Scalar> const& array)
{
	for (int k = array.lbound(3); k <= array.ubound(3); k++)
	{
		std::cout << "(:,:," << k << ") = " << std::endl;
		for (int i = array.lbound(1); i <= array.ubound(1); i++)
		{
			for (int j = array.lbound(2); j <= array.ubound(2); j++)
				std::cout << array(i, j, k) << "  ";
			std::cout << std::endl;
		}
	}
}

double cpu_time()
{
	return ((double)std::clock()) / CLOCKS_PER_SEC;
}

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
// Bessel J_N1 to J_N2 (transformational function)
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
template<class T1, class T2, class T3>
Array<T3, 1> bessel_jn(T1 n1, T2 n2, T3 x)
{
	Array<T3, 1> result(n2 - n1 + 1);
	for (size_t i = 0, n = n1; n <= n2; n++, i++)
	{
		result.linear(i) = boost::math::cyl_bessel_j(n, x);
	}
	return result;
}
// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

}

#endif /* FTN_NONMEMBERFUNCTIONS_H_ */
