#include <stdlib.h>
#include <iostream>

template <typename X>
void check_intermediate_value(X min, X max)
{
	int i = 0;
	while (min < max) {
		std::cout << "\tmin: " << min << ", max: " << max << std::endl;
		max = ((max - min) / 2) + min;
		i++;
	}
	std::cout << "i: " << i << std::endl;
	std::cout << "(min,max) = (" << min << "," << max << ")" << std::endl;
}

int main(int argc, char** argv)
{
	if (argc != 3) {
		std::cout << "specify min, max val" << std::endl;
		return -1;
	}
	int min = atoi(argv[1]);
	int max = atoi(argv[2]);
	std::cout << "(min,max) = (" << min << "," << max << ")" << std::endl;

	std::cout << "int" << std::endl;
	check_intermediate_value<int>(min, max);
	std::cout << "double" << std::endl;
	check_intermediate_value<double>(min, max);
	std::cout << "float" << std::endl;
	check_intermediate_value<float>(min, max);
	return 0;
}
