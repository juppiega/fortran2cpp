
#ifndef FTN_TRAITS_H_
#define FTN_TRAITS_H_

#include "ftn_typedefs.h"

// TODO: Anna tunnustus Armadillolle.
namespace ftn
{

template<typename T>
struct isFtnType
{
	typedef char yes[1];
	typedef char no[2];

	template<typename X> static yes& check(typename X::PossibleBaseInFtn_WithRandomSequence_5CqH36Rz9c9ELo79Mi257usV*);
	template<typename > static no& check(...);

	static const bool value = (sizeof(check<T>(0)) == sizeof(yes));
};

}

#endif /* FTN_TRAITS_H_ */
