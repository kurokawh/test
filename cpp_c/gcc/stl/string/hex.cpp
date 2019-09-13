#include <iostream>
#include <sstream> // hex
#include <string>


int main(int argc, char** argv)
{
/*
	int num = 30;
	std::stringstream ss = std::hex << num;
	std::cout << ss.str() << std::endl;
*/
    std::stringstream ss;
 
    int decimal = 2018;
 
    ss << "10進数：" << decimal << "\n";
    ss << "16進数：0x" << std::hex << decimal;
 
    std::cout << ss.str() << "\n";

	return 0;
}
