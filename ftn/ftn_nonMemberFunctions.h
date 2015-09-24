/*
 * ftn_nonMemberFunctions.h
 *
 *  Created on: Sep 20, 2015
 *      Author: juho
 */

#ifndef FTN_NONMEMBERFUNCTIONS_H_
#define FTN_NONMEMBERFUNCTIONS_H_
#include "ftn_ArrayBase.h"

namespace ftn
{

template<class Derived, class Scalar, class OtherDerived, class OtherScalar>
bool sameContents (ArrayBase<Derived, Scalar> const& array1, ArrayBase<OtherDerived, OtherScalar> const& array2)
{
	size_t n = array1.size();
	if (n == array2.size())
	{
		for (size_t i = 1; i <= n; i++)
		{
			if (array1.linear(i) != array2.linear(i)) return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<class Derived, class Scalar, class OtherDerived, class OtherScalar>
bool sameShape (ArrayBase<Derived, Scalar> const& array1, ArrayBase<OtherDerived, OtherScalar> const& array2)
{
	return sameContents(array1.shape(), array2.shape());
}

template<class Derived, class Scalar, class OtherDerived, class OtherScalar>
bool sameShapeAndContents (ArrayBase<Derived, Scalar> const& array1, ArrayBase<OtherDerived, OtherScalar> const& array2)
{
	return array1.sameShape(array2) && array1.sameContents(array2);
}

}


#endif /* FTN_NONMEMBERFUNCTIONS_H_ */
