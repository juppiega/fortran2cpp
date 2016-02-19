#include <iostream>
#define FTN_DEBUG
#include "ftn.h"

int main()
{
	ftn::Array<double> a(ftn::span(0,2),2);
	a = 2;
	std::cout << a(2,2) << std::endl;

	return 0;
}
