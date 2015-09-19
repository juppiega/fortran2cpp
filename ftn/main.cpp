
#define FTN_DEBUG
#include <stdlib.h>
#include <stdio.h>
#include "ftn.h"

struct S
{
	double d;
};

using namespace ftn;

int main()
{

	Array<double> a(span(0,4)), c(span(-1,3));
	a = 2.0; c = 1.0;

	//std::cout << a << std::endl;

	c = a;

	std::cout << c << std::endl;
	std::cout << c.lbound() << std::endl;

	return 0;
}




