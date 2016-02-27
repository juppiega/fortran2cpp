#include <iostream>
#define FTN_DEBUG
#include "ftn.h"

using namespace ftn;

int main()
{

//	Array<double, 3> a(2, 1, 2);
//	Array<double, 3> b(2, 1, 2);
//	Array<double, 3> c(2, 1, 2);
//	a = 2;
//	b = 3;
//	c = 2.0 * b(span(), span(), span());
//	printCube(c);
//	//std::cout << (a + b * c).isArrayView() << std::endl;

	Array<double, 2> a(50000, 5000);
	Array<double, 2> b(25000, 5000);

	a = 0.001;

	auto sl = a(span(Dynamic,Dynamic,2),span());

	double t1 = cpu_time();
	b = 2.0 * sl + (sl / 4.0) + 1.0 - sl * sl;
	double t2 = cpu_time();
	std::cout << "Traverse Time (ms): " << (double) (t2 - t1) * 1000
			<< std::endl;
	std::cout << a(1, 1) << std::endl;

	return 0;
}
