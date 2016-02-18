
#ifndef FTN_TYPEDEFS_H_
#define FTN_TYPEDEFS_H_

#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <sstream>
#include <utility>
#include <limits>

// Namespace of the Fortran emulator - ftn
namespace ftn
{

typedef int dim_type;
const dim_type Dynamic = std::numeric_limits<dim_type>::min(); // Create new keyword "Dynamic" for array operation emulation.
const int maxDims = 8;

}


#endif /* FTN_TYPEDEFS_H_ */
