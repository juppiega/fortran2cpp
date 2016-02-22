#ifndef FTN_SPAN_H_
#define FTN_SPAN_H_

#include "ftn_typedefs.h"

namespace ftn
{

class span // TODO: Kirjoita templatet!
{
private:
	dim_type _begin;
	dim_type _end;
	dim_type _stride;
public:
	span() :
			_begin(Dynamic), _end(Dynamic), _stride(1)
	{
	}
	explicit span(dim_type length) :
			_begin(Dynamic), _end(length), _stride(1)
	{
	}
	span(dim_type beginIndex, dim_type endIndex) :
			_begin(beginIndex), _end(endIndex), _stride(1)
	{
	}
	span(dim_type beginIndex, dim_type endIndex, dim_type stride) :
			_begin(beginIndex), _end(endIndex), _stride(stride)
	{
	}

	void setStart (dim_type ind)
	{
		_begin = ind;
	}

	void setStop (dim_type ind)
	{
		_end = ind;
	}

	void setStride (dim_type st)
	{
		_stride = st;
	}

	dim_type start() const
	{
		return _begin;
	}

	dim_type stop() const
	{
		return _end;
	}

	dim_type stride() const
	{
		return _stride;
	}
};
// Class span

}

#endif /* FTN_SPAN_H_ */
