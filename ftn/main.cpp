
#define FTN_DEBUG
#include <stdlib.h>
#include <stdio.h>
#include "ftn.h"

struct S
{
	double d;
};

int main()
{
	ftn::Array<double> a(2), b(2);
	a = 2.0; b = 2.0;

	//std::cout << a << std::endl;

	ftn::Array<double> c = a % (b - a - a);

	std::cout << c << std::endl;

	return 0;
}




