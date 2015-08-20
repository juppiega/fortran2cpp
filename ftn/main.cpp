#include <stdlib.h>
#include <stdio.h>
#include "ftn.h"

int main()
{
	ftn::numArray<double> a(ftn::span(2,5));
	a.putScalar(1.0);

	a(5) = 2;

	std::cout << a(5) << std::endl;

	return 0;
}




