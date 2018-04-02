#include <iostream>
#include <stdio.h>

#include <stdint.h> // INT MIN/MAX
#include <ieeefp.h> // DBL/FLT 

#include <math.h>   // log(), exp()

int main(int argc, char** argv)
{
	std::cout << "INT64: "  << sizeof(int64_t)  << std::endl;
	std::cout << "UINT64: " << sizeof(uint64_t) << std::endl;

	std::cout << "FLT: "  << sizeof(float)  << std::endl;
	std::cout << "DBL: "  << sizeof(double)  << std::endl;

	double dbl = 9.9;
	std::cout << "DBL: "  << dbl  << std::endl;
	std::cout << "DBL * 10: "  << dbl*10  << std::endl;
	std::cout << "DBL + 1: "  << dbl+1  << std::endl;
	printf("printf: DBL: %lf\n", dbl);
	printf("printf: DBL * 10: %lf\n", dbl * 10);
	printf("printf: DBL + 1: %lf\n", dbl + 1);


	float flt = 9.9;
	std::cout << "FLT: "  << flt  << std::endl;
	std::cout << "FLT * 10: "  << flt*10  << std::endl;
	std::cout << "FLT + 1: "  << flt+1  << std::endl;
	printf("printf: FLT: %f\n", flt);
	printf("printf: FLT * 10: %f\n", flt * 10);
	printf("printf: FLT + 1: %f\n", flt + 1);
	return 0;
}



