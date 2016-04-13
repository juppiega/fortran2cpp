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

	int N = 300;
	int M = 300;
	Array<double, 2> a(N, M);
	Array<double, 2> b(N, M);
	Array<double, 2> c(N/2, M/2);
	a = 1E-6;
	b = 2E-6;
	c = 2.0;

	double t1 = cpu_time();
	//for (int k = 0; k < 100; k++)
	{
		for (size_t t = 0; t < 10000; t++)
		{
			c = c + a(span(1, N, 2), span(1, M, 2)) + b(span(1, N, 2), span(1, M, 2)) + a(span(1, N, 2), span(1, M, 2));
//			for (int j = 0; j < 2; j++)
//				for(int i = 0; i < 2; i++)
//					c.zb(i,j) = c.zb(i,j) + aSpan.zb(i,j) + bSpan.zb(i,j) + aSpan.zb(i,j);
		}
	}
	double t2 = cpu_time();
	//printMat(c);
	//std::cout << c(c.size(1), c.size(2)) << std::endl;
	std::cout << (t2 - t1) * 1000 << std::endl;
	//std::cout << aSpan.shape() << std::endl;

//	c = gamma(c);
//	printCube(c);
//	std::cout << asInt(4.2) << std::endl;

//	const dim_type N = 5000;
//
//	double t1 = cpu_time();
//
//	Array<double, 2> a(N,N);
//	Array<double, 2> b(N,N);
//
//	double t2 = cpu_time();
//	std::cout << "Alloc Time (ms): " << (double) (t2 - t1) * 1000
//			<< std::endl;
////	std::vector<double> a(N);
////	std::vector<double> b(N);
//
////	double* a = new double [N];
////	double* b = new double [N];
////
////	for (dim_type i = 0; i < N; i++)
////	{
////		a[i] = 0.001;
////	}
//
//	a = 0.001;
//
//	auto sl = a(span(Dynamic,Dynamic,2),span());
//
//	t1 = cpu_time();
//	b = 2 * cos(a) + 1.0;
////	for (dim_type i = 0; i < N; i++)
////		b[i] = 2 * a[i] + 1.0;
//	//b = sl + 1.0 + sl;
////	for (dim_type j = 0; j < 5000; j++)
////		for (dim_type i = 0; i < 25000; i++)
////			testFunc(&b.zb(i, j), &a.zb(2*i,j));
//			//b.zb(i, j) = a.zb(2*i,j) + 1.0 + a.zb(2*i,j);

//	t2 = cpu_time();
//	std::cout << "Traverse Time (ms): " << (double) (t2 - t1) * 1000
//			<< std::endl;
//	std::cout << a(1,1) << std::endl;

	return 0;
}
