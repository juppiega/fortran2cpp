#include <iostream>
//#define FTN_DEBUG
#include "ftn.h"

using namespace ftn;

//void testFunc (double* __restrict__ b, double* __restrict__ a)
//{
//	*b = *a + 1.0 + *a;
//}

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
	const dim_type N = 10000;
	Array<double, 2> a(N,N);
	Array<double, 2> b(N,N);

//	std::vector<double> a(N);
//	std::vector<double> b(N);

//	double* a = new double [N];
//	double* b = new double [N];
//
//	for (dim_type i = 0; i < N; i++)
//	{
//		a[i] = 0.001;
//	}

	a = 0.001;

	auto sl = a(span(Dynamic,Dynamic,2),span());

	double t1 = cpu_time();
	b = 2 * cosh(a) + 1.0;
//	for (dim_type i = 0; i < N; i++)
//		b[i] = 2 * a[i] + 1.0;
	//b = sl + 1.0 + sl;
//	for (dim_type j = 0; j < 5000; j++)
//		for (dim_type i = 0; i < 25000; i++)
//			testFunc(&b.zb(i, j), &a.zb(2*i,j));
			//b.zb(i, j) = a.zb(2*i,j) + 1.0 + a.zb(2*i,j);


	double t2 = cpu_time();
	std::cout << "Traverse Time (ms): " << (double) (t2 - t1) * 1000
			<< std::endl;
	std::cout << a(1,1) << std::endl;

	return 0;
}
