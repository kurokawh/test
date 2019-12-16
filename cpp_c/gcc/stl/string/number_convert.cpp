#include <iostream>
#include <sstream> // hex
#include <string>


int main(int argc, char** argv)
{
 

	std::string str = "2018";

    int decimal = std::stoi(str);
    std::cout << "10進数：" << decimal << "\n";

	std::string not_num = "abcd";
    decimal = std::stoi(not_num);
    std::cout << "not_num：" << decimal << "\n";

	std::string empty = "";
    decimal = std::stoi(empty);
    std::cout << "empty：" << decimal << "\n";

    std::cout << "\n";

	return 0;
}
