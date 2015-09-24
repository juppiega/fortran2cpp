
#define FTN_DEBUG
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>
#include "ftn.h"

struct S
{
	double d;
};

using namespace ftn;

int main()
{

	Array<double> a(span(-1,0), 2, 2);
	a = 2.0;

	std::cout << a << std::endl;

	return 0;
}




