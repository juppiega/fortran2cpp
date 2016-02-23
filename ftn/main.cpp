#include <iostream>
#define FTN_DEBUG
#include "ftn.h"

using namespace ftn;


int main()
{
	constexpr bool b = isFtnType<Array<double> >::value;
	std::cout << b << std::endl;
//	double t1 = cpu_time();
//	Array<double> a(50000, 5000);
//	double t2 = cpu_time();
//	std::cout << "Alloc Time (ms): " << (double)(t2-t1)*1000 << std::endl;
//
//	a = 0.001;
//
//	double sum = 0.0;
//	t1 = cpu_time();
//	a(span(1,Dynamic,2), span(1,Dynamic,2)) =  sin(a(span(1,Dynamic,2), span(1,Dynamic,2))) + 4.0;
//	t2 = cpu_time();
//	std::cout << "Traverse Time (ms): " << (double)(t2-t1)*1000 << std::endl;
//	std::cout << a(1,1) << std::endl;

	return 0;
}
