
#ifndef FTN_ARRAYIMPLEMENTATIONS_H_
#define FTN_ARRAYIMPLEMENTATIONS_H_
#include "ftn_Array.h"

namespace ftn
{
template<class Scalar>
Array<Scalar>::Array (dim_type initVal)
{
	beginIndices.reserve(1);
	endIndices.reserve(1);
	dim_type initLength = findInitializationValues(initVal);

	if (initLength == 0)
	{
		isAllocated = false;
	}
	else
	{
		isAllocated = true;
	}

	mdArray = MDArrayRCP<Scalar>(tuple(initLength)); // Alustaa alkiot!
}

template<class Scalar>
Array<Scalar>::Array (span initVal)
{
	beginIndices.reserve(1);
	endIndices.reserve(1);
	dim_type initLength = findInitializationValues(initVal);

	if (initLength == 0)
	{
		isAllocated = false;
	}
	else
	{
		isAllocated = true;
	}

	mdArray = MDArrayRCP<Scalar>(tuple(initLength)); // Alustaa alkiot!
}

template<class Scalar>
template<class Derived>
Array<Scalar>::Array (OperatorBase<Derived, Scalar> const& array)
{
	isAllocated = true;
	int nDims = array.numDims();
	beginIndices.assign(nDims, 1);
	endIndices.reserve(nDims);

	for (int i = 0; i < nDims; i++)
	{
		endIndices[i] = array.size(i + 1);
	}

	dim_type length = array.size();
	mdArray = MDArrayRCP<Scalar>(tuple(length)); // Alustaa alkiot!
	for (int i = 0; i < length; i++)
	{
		mdArray(i) = array.linear(i + 1);
	}
}

template<class Scalar>
template<class Derived>
Array<Scalar>& Array<Scalar>::operator= (OperatorBase<Derived, Scalar> const& array)
{
	if (this == &array)
		return *this;

	isAllocated = true;
	int nDims = array.numDims();
	beginIndices.assign(nDims, 1);
	endIndices.reserve(nDims);

	for (int i = 0; i < nDims; i++)
	{
		endIndices[i] = array.size(i + 1);
	}

	dim_type length = array.size();
	mdArray = MDArrayRCP<Scalar>(tuple(length)); // Alustaa alkiot!
	for (int i = 0; i < length; i++)
	{
		mdArray(i) = array.linear(i + 1);
	}

	return *this;
}

template<class Scalar>
int Array<Scalar>::numDims () const
{
	return beginIndices.size();
}

template<class Scalar>
Array<dim_type> Array<Scalar>::shape () const
{
	int n = numDims();
	Array<dim_type> shape(n);

	for (int i = 0; i < n; i++)
	{
		shape(i + 1) = endIndices[i] - beginIndices[i] + 1;
	}

	return shape;
}

template<class Scalar>
std::string Array<Scalar>::toString () const
{
	return mdArray.toString();
}

template<class Scalar>
dim_type Array<Scalar>::findInitializationValues (dim_type initVal)
{
	beginIndices.push_back(1);
	if (initVal == Dynamic)
	{
		endIndices.push_back(Dynamic);
		return 0;
	}
	else
	{
		endIndices.push_back(initVal);
		return initVal;
	}
}

template<class Scalar>
dim_type Array<Scalar>::findInitializationValues (span initVal)
{
	if (initVal.stop() == Dynamic)
	{
		endIndices.push_back(Dynamic);
		if (initVal.start() != Dynamic)
			beginIndices.push_back(initVal.start());
		else
			beginIndices.push_back(1);
		return 0;
	}
	else
	{
		dim_type length;
		if (initVal.start() != Dynamic)
		{
			beginIndices.push_back(initVal.start());
			length = initVal.stop() - initVal.start() + 1;
			endIndices.push_back(initVal.start() + length - 1);
		}
		else
		{
			beginIndices.push_back(1);
			length = initVal.stop();
			endIndices.push_back(length);
		}
		return length;
	}
}

template<class Scalar>
void Array<Scalar>::indexOutOfBounds (dim_type index, int dimNumber) const
{
	if (index < beginIndices[dimNumber] || index > endIndices[dimNumber])
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << beginIndices[dimNumber] << ", " << endIndices[dimNumber] << "]!";
		throw std::out_of_range(strStream.str());
	}
}

template<class Scalar>
void Array<Scalar>::linearIndexOutOfBounds (dim_type index) const
{
	if (index < 1 || index > mdArray.size())
	{
		std::ostringstream strStream;
		strStream << "Index " << index << " out of range [" << 1 << ", " << mdArray.size() << "]!";
		throw std::out_of_range(strStream.str());
	}
}

template<class Scalar>
Scalar Array<Scalar>::operator() (dim_type index) const
{
#ifdef FTN_DEBUG
	indexOutOfBounds(index, 0);
#endif
	return mdArray(index - beginIndices[0]);
}

template<class Scalar>
Scalar& Array<Scalar>::operator() (dim_type index)
{
#ifdef FTN_DEBUG
	indexOutOfBounds(index, 0);
#endif
	return mdArray(index - beginIndices[0]);
}

template<class Scalar>
Scalar Array<Scalar>::linear (dim_type index) const
{
#ifdef FTN_DEBUG
	linearIndexOutOfBounds(index);
#endif
	return mdArray.arrayRCP()[index - 1];
}

template<class Scalar>
Scalar& Array<Scalar>::linear (dim_type index)
{
#ifdef FTN_DEBUG
	linearIndexOutOfBounds(index);
#endif
	return mdArray.arrayRCP()[index - 1];
}

template<class Scalar>
size_t Array<Scalar>::size () const
{
	return mdArray.size();
}

template<class Scalar>
size_t Array<Scalar>::size (size_t dimNumber) const
{
#ifdef FTN_DEBUG
	if (dimNumber < 1 || dimNumber > numDims())
	{
		std::ostringstream strStream;
		strStream << "Argument dim = " << dimNumber << " out of range [" << 1 << ", " << numDims() << "]!";
		throw std::invalid_argument(strStream.str());
	}
#endif
	//std::cout << endIndices[0] << std::endl;
	//std::cout << beginIndices[0] << std::endl;
	dim_type a = endIndices[dimNumber - 1];
	dim_type b = beginIndices[dimNumber - 1];
	//return endIndices[dimNumber - 1] - beginIndices[dimNumber - 1] + 1;
	return a - b + 1;
}

template<class Scalar>
Array<Scalar>& Array<Scalar>::operator= (const Scalar& x)
{
	mdArray.assign(x);
	return *this;
}
}

#endif /* FTN_ARRAYIMPLEMENTATIONS_H_ */
