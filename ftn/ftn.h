#ifndef FTN_H_
#define FTN_H_

#include <Domi_MDVector.hpp>
#include <Domi_Slice.hpp>
#include <Domi_MDArrayView.hpp>
#include <Tpetra_DefaultPlatform.hpp>
#include <Teuchos_RCP.hpp>
#include <iostream>
#include <array>
#include <type_traits> // std::is_same

// Namespace of the Fortran emulator - ftn
namespace ftn
{
using Domi::MDComm;
using Domi::MDMap;
using Domi::MDVector;
using Domi::MDArrayView;
using Teuchos::Comm;
using Teuchos::SerialComm;
using Teuchos::RCP;
using Teuchos::rcp;
using Teuchos::tuple;
typedef Domi::dim_type dim_type; // Define dim_type as a shorthand for Domi::dim_type
static const dim_type Dynamic = Domi::Slice::Default; // Create new keyword "Dynamic" for array operation emulation.

/* Class span
 * Inherits: Domi::Slice
 *
 * Fortran-like emulator of Domi::Slice better suited for variable lower bounds and slicing.
 */
class span: public Domi::Slice
{
public:
	span () :
			Domi::Slice(Dynamic, Dynamic)
	{
	}
	span (dim_type length) :
			Domi::Slice(Dynamic, length)
	{
	}
	span (dim_type beginIndex, dim_type endIndex) :
			Domi::Slice(beginIndex, endIndex)
	{
	}
	span (dim_type beginIndex, dim_type endIndex, dim_type stride) :
			Domi::Slice(beginIndex, endIndex, stride)
	{
	}
};
// Class span

/* Class numArray
 * Inherits: Domi::MDVector
 *
 * Fortran-like emulator of Domi::MDVector with overloaded (parallel) operators (+,-,*,/), variable
 * lower bounds and (parallel) elemental intrinsic functions.
 */
template<class Scalar, class Node = Tpetra::Details::DefaultTypes::node_type>
class numArray: public MDVector<Scalar, Node>
{
private:
	bool isAllocated = false;
	std::array<dim_type, 7> offsets = { { 1, 1, 1, 1, 1, 1, 1 } };

	dim_type findInitializationValues (dim_type initVal, int dimNumber);
	dim_type findInitializationValues (span initVal, int dimNumber);

	template<class T>
	MDVector<Scalar, Node> init1d (T initVal);

public:

	template<class T>
	numArray (T initVal) :
			Domi::MDVector<Scalar, Node>(init1d(initVal))
	{

	}

	Scalar operator() (dim_type index) const;
};
// Class numArray

/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 * IMPLEMENTATIONS: Class ftn::numArray
 * &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
 */

template<class Scalar, class Node>
dim_type numArray<Scalar, Node>::findInitializationValues (dim_type initVal, int dimNumber)
{
	offsets[dimNumber] = 1;
	if (initVal == Dynamic)
		return 0;
	else
		return initVal;
}

template<class Scalar, class Node>
dim_type numArray<Scalar, Node>::findInitializationValues (span initVal, int dimNumber)
{
	if (initVal.stop() == Dynamic)
	{
		if (initVal.start() != Dynamic)
			offsets[dimNumber] = initVal.start();
		else
			offsets[dimNumber] = 1;
		return 0;
	}
	else
	{
		dim_type length;
		if (initVal.start() != Dynamic)
		{
			offsets[0] = initVal.start();
			length = initVal.stop() - initVal.start() + 1;
		}
		else
		{
			offsets[dimNumber] = 1;
			length = initVal.stop();
		}
		return length;
	}
}

template<class Scalar, class Node>
template<class T>
MDVector<Scalar, Node> numArray<Scalar, Node>::init1d (T initVal)
{
	RCP<const Comm<int> > serialComm(new SerialComm<int>());
	RCP<const MDComm> comm(new MDComm(serialComm, tuple(1), tuple(0)));

	dim_type initLength = findInitializationValues(initVal, 0);

	RCP<const MDMap<Node> > mdmap(new MDMap<Node>(comm, Teuchos::tuple(initLength), Teuchos::tuple(0), Teuchos::tuple(0)));
	MDVector<Scalar, Node> result(mdmap, false);
	return result;
}

template<class Scalar, class Node>
Scalar numArray<Scalar, Node>::operator() (dim_type index) const
{
	return MDVector<Scalar, Node>::getData(true)(index - offsets[0]);
}

} // namespace ftn

#endif /* FTN_H_ */
