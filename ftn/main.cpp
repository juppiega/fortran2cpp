
#define FTN_DEBUG
#include <stdlib.h>
#include <stdio.h>
#include <typeinfo>
#include <cmath>
#include "ftn.h"

namespace N
{
	namespace detail
	{
		double d;
	}
	void printSth(){std::cout<<"foo\n";}
};

struct S
{
	double d;
};

using namespace ftn;
//using namespace std;

int main()
{
	Array<double> a(2);
	a = 2.0;

	Array<double> c = a+a;

	std::cout << c(2) << std::endl;
	std::cout << c << std::endl;


	return 0;
}




