#include <iostream>
#include <stdio.h>

#include <stdint.h> // INT MIN/MAX
#include <ieeefp.h> // DBL/FLT 

#include <math.h>   // log(), exp()

int main(int argc, char** argv)
{
	std::cout << "INT64_MAX: "  << INT64_MAX  << std::endl;
	std::cout << "INT64_MIN: "  << INT64_MIN  << std::endl;
	std::cout << "UINT64_MAX: " << UINT64_MAX << std::endl;
/*
	std::cout << "FLT_MAX: "  << FLT_MAX  << std::endl;
	std::cout << "FLT_MIN: "  << FLT_MIN  << std::endl;
	std::cout << "DBL_MAX: "  << DBL_MAX  << std::endl;
	std::cout << "DBL_MIN: "  << DBL_MIN  << std::endl;
*/
	uint64_t i64max = UINT64_MAX;
	uint64_t i64max_1 = UINT64_MAX -1;
	uint64_t i64max_2 = UINT64_MAX -2;

	double d = i64max;
	double d_1 = i64max_1;
	double d_2 = i64max_2;

	uint64_t r = d;
	uint64_t r_1 = d_1;
	uint64_t r_2 = d_2;

	std::cout << "UINT64_MAX: " << i64max << ", double: " << d << ", ret: " << r <<std::endl;
	std::cout << "UINT64_MAX-1: " << i64max_1 << ", double: " << d_1 << ", ret: " << r_1 <<std::endl;
	std::cout << "UINT64_MAX-2: " << i64max_2 << ", double: " << d_2 << ", ret: " << r_2 <<std::endl;

	return 0;
}



