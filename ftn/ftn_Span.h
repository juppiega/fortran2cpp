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
	span(dim_type length) :
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

	dim_type start()
	{
		return _begin;
	}

	dim_type stop()
	{
		return _end;
	}

	dim_type stride()
	{
		return _stride;
	}
};
// Class span

}

#endif /* FTN_SPAN_H_ */
