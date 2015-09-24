/*
 * ftn_ArrayViewImplementation.h
 *
 *  Created on: Sep 20, 2015
 *      Author: juho
 */

#ifndef FTN_ARRAYVIEWIMPLEMENTATION_H_
#define FTN_ARRAYVIEWIMPLEMENTATION_H_
#include "ftn_nonMemberFunctions.h"
#include "ftn_Array.h"
#include "ftn_ArrayView.h"

namespace ftn
{
template<class Scalar>
ArrayView<Scalar>::ArrayView (MDArrayView<Scalar>& arrayView) :
		mdArrayView(arrayView)
{
}

template<class Scalar>
ArrayView<Scalar>::ArrayView (ArrayView<Scalar> && other) :
		mdArrayView(other.getMdArrayView())
{
	std::cout << "Move constructor called!\n";
}

template<class Scalar>
template<class Derived, class Scalar2>
ArrayView<Scalar>& ArrayView<Scalar>::operator= (ArrayBase<Derived, Scalar2> const& array)
{
#ifdef FTN_DEBUG
	if (numDims() != array.numDims())
	{
		std::ostringstream strStream;
		strStream << "Trying to assign array of dimension: " << array.numDims() << " into array subobject of dimension: " << numDims();
		throw std::domain_error(strStream.str());
	}
#endif

	MDArrayView<Scalar> copyTo;
	if (sameShape(*this, array))
	{
		copyTo = mdArrayView; // No subobject creation required.
	}
	else // We need to create a subView of this, where to copy the elements of array.
	{
		MDArrayView<Scalar> shrinkedViewOfThis = mdArrayView;
		int n = array.numDims();
		for (int i = 1; i <= n; i++)
		{
#ifdef FTN_DEBUG
			if (array.size(i) > size(i))
			{
				std::ostringstream strStream;
				strStream << "Trying to assign array of shape: " << array.shape() << " into array subobject of shape: " << shape();
				throw std::domain_error(strStream.str());
			}
#endif
			shrinkedViewOfThis = shrinkedViewOfThis[span(0, array.size(i))];
		}
		copyTo = shrinkedViewOfThis;
	}

	dim_type length = array.size();
	for (int i = 0; i < length; i++)
	{
		copyTo.arrayView()[i] = array.linear(i + 1);
	}
	return *this;
}

template<class Scalar>
ArrayView<Scalar>& ArrayView<Scalar>::operator= (ArrayView<Scalar>& array)
{
	ArrayNonConstBase<ArrayView<Scalar>, Scalar>& arrayBaseInstance = array;
	this->operator=(arrayBaseInstance);
}

template<class Scalar>
int ArrayView<Scalar>::numDims () const
{
	return mdArrayView.numDims();
}

template<class Scalar>
size_t ArrayView<Scalar>::size () const
{
	MDArrayView<Scalar> nonConst(mdArrayView); // Fix bug in Domi::MDArrayView
	return nonConst.size();
}

template<class Scalar>
size_t ArrayView<Scalar>::size (size_t dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "Argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return mdArrayView.dimension(dimNumber - 1);
}

template<class Scalar>
Scalar ArrayView<Scalar>::linear (dim_type index) const
{
#ifdef FTN_DEBUG
	linearIndexOutOfBounds(index);
#endif
	return mdArrayView.arrayView()[index - 1];
}

template<class Scalar>
Scalar& ArrayView<Scalar>::linear (dim_type index)
{
#ifdef FTN_DEBUG
	linearIndexOutOfBounds(index);
#endif
	return mdArrayView.arrayView()[index - 1];
}

template<class Scalar>
dim_type ArrayView<Scalar>::lbound (dim_type dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "Argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return 1;
}

template<class Scalar>
Array<dim_type> ArrayView<Scalar>::shape () const
{
	int n = numDims();
	Array<dim_type> shape(n);

	for (int i = 0; i < n; i++)
	{
		shape(i + 1) = mdArrayView.dimension(i);
	}

	return shape;
}

template<class Scalar>
Array<dim_type> ArrayView<Scalar>::lbound () const
{
	int n = numDims();
	Array<dim_type> lbounds(n);
	lbounds = 1;
	return lbounds;
}

template<class Scalar>
ArrayView<Scalar>& ArrayView<Scalar>::operator= (const Scalar& x)
{
	mdArrayView.assign(x);
	return *this;
}

template<class Scalar>
std::string ArrayView<Scalar>::toString () const
{
	return mdArrayView.toString();
}

template<class Scalar>
void ArrayView<Scalar>::indexOutOfBounds (dim_type index, int dimNumber) const
{
	if (index < lbound(dimNumber) || index > ubound(dimNumber))
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << lbound(dimNumber) << ", " << ubound(dimNumber) << "]!";
		throw std::out_of_range(strStream.str());
	}
}

template<class Scalar>
void ArrayView<Scalar>::linearIndexOutOfBounds (dim_type index) const
{
	dim_type upperBound = size();
	if (index < 1 || index > upperBound)
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << 1 << ", " << upperBound << "]!";
		throw std::out_of_range(strStream.str());
	}
}

template<class Scalar>
dim_type ArrayView<Scalar>::ubound (dim_type dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "Argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	return lbound(dimNumber) + mdArrayView.dimension(dimNumber - 1) - 1;
}

template<class Scalar>
Array<dim_type> ArrayView<Scalar>::ubound () const
{
	int n = numDims();
	Array<dim_type> ubounds(n);

	for (int i = 1; i <= n; i++)
	{
		ubounds(i) = ubound(i);
	}

	return ubounds;
}

template<class Scalar>
ArrayView<Scalar> Array<Scalar>::operator() (span indexSpan) const
{
	std::cout << "At const" << std::endl;
	MDArrayView<Scalar> domiView = mdArray.mdArrayView();
	dim_type startInd = indexSpan.start();
	dim_type stopInd = indexSpan.stop();

	if (startInd == Dynamic)
	{
		startInd = lbound(1);
	}
	if (stopInd == Dynamic)
	{
		stopInd = ubound(1);
	}

#ifdef FTN_DEBUG
	indexOutOfBounds(startInd, 1);
	indexOutOfBounds(stopInd, 1);
#endif

	startInd -= lbound(1);
	stopInd -= lbound(1);

	domiView = domiView[span(startInd, stopInd + 1, indexSpan.step())];
	ArrayView<Scalar> result(domiView);

	return result;
}

template<class Scalar>
ArrayView<Scalar> Array<Scalar>::operator() (span indexSpan)
{
	MDArrayView<Scalar> domiView = mdArray.mdArrayView();
	dim_type startInd = indexSpan.start();
	dim_type stopInd = indexSpan.stop();

	if (startInd == Dynamic)
	{
		startInd = lbound(1);
	}
	if (stopInd == Dynamic)
	{
		stopInd = ubound(1);
	}

#ifdef FTN_DEBUG
	indexOutOfBounds(startInd, 1);
	indexOutOfBounds(stopInd, 1);
#endif

	startInd -= lbound(1);
	stopInd -= lbound(1);

	domiView = domiView[span(startInd, stopInd + 1, indexSpan.step())];
	ArrayView<Scalar> result = domiView;

	return result;
}

template<class Scalar>
MDArrayView<Scalar> ArrayView<Scalar>::getMdArrayView () const
{
	return mdArrayView;
}

}

#endif /* FTN_ARRAYVIEWIMPLEMENTATION_H_ */
