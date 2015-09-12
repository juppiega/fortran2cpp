
#ifndef FTN_SPAN_H_
#define FTN_SPAN_H_

#include <Domi_Slice.hpp>
#include "ftn_typedefs.h"

namespace ftn
{
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
}

#endif /* FTN_SPAN_H_ */
