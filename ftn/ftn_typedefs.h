
#ifndef FTN_TYPEDEFS_H_
#define FTN_TYPEDEFS_H_

#include <Domi_MDVector.hpp>
#include <Domi_MDArrayView.hpp>
#include <Domi_MDArrayRCP.hpp>
#include <Tpetra_DefaultPlatform.hpp>
#include <Teuchos_RCP.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <sstream>
#include <limits>

// Namespace of the Fortran emulator - ftn
namespace ftn
{
using Domi::MDComm;
using Domi::MDMap;
using Domi::MDVector;
using Domi::MDArrayView;
using Domi::MDArrayRCP;
using Teuchos::Comm;
using Teuchos::SerialComm;
using Teuchos::RCP;
using Teuchos::rcp;
using Teuchos::tuple;
typedef Domi::dim_type dim_type; // Define dim_type as a shorthand for Domi::dim_type
const dim_type Dynamic = std::numeric_limits<dim_type>::min(); // Create new keyword "Dynamic" for array operation emulation.

}


#endif /* FTN_TYPEDEFS_H_ */
