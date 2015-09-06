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
	ftn::Array<double> a(5), b(5);
	a = 1.0; b = 2.0;

	//std::cout << a << std::endl;

	ftn::Array<double> c = a + b;

	std::cout << c << std::endl;

	return 0;
}




