#include <iostream>
//#include <cstdint>
#include <stdint.h> // INT MIN/MAX
#include <ieeefp.h> // DBL/FLT 

#include <math.h>   // log(), exp()

int main(int argc, char** argv)
{
	std::cout << "INT64_MAX: "  << INT64_MAX  << std::endl;
	std::cout << "INT64_MIN: "  << INT64_MIN  << std::endl;
	std::cout << "UINT64_MAX: " << UINT64_MAX << std::endl;

	std::cout << "FLT_MAX: "  << FLT_MAX  << std::endl;
	std::cout << "FLT_MIN: "  << FLT_MIN  << std::endl;
	std::cout << "DBL_MAX: "  << DBL_MAX  << std::endl;
	std::cout << "DBL_MIN: "  << DBL_MIN  << std::endl;

	double dbl = 0;
	dbl = DBL_MAX;
	std::cout << "DBL_MAX: "  << dbl  << std::endl;
	dbl = DBL_MAX * 10;
	std::cout << "DBL_MAX * 10: "  << dbl  << std::endl;
	dbl = DBL_MAX + 1;
	std::cout << "DBL_MAX + 1: "  << dbl  << std::endl;

	// http://nonbiri-tereka.hatenablog.com/entry/2014/09/24/095945
	dbl = log(0);
	std::cout << "log(0): "  << dbl  << std::endl;
	std::cout << "log(0)/log(0): "  << dbl/dbl  << std::endl;
	dbl = exp(750);
	std::cout << "exp(750): "  << dbl  << std::endl;
	std::cout << "exp(750)/exp(750): "  << dbl/dbl  << std::endl;
//	dbl = 0/0; // core dump (0 div error)
//	std::cout << "0/0: "  << dbl  << std::endl;

	return 0;
}



