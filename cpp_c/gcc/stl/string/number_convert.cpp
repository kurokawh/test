#include <iostream>
#include <sstream> // hex
#include <string>


int main(int argc, char** argv)
{
 

	std::string str = "2018";

    int decimal = str = std::stoi(str);
    ss << "10進数：" << decimal << "\n";

	std::string not_num = "abcd";
    decimal = str = std::stoi(not_num);
    ss << "not_num：" << decimal << "\n";

	std::string empty = "";
    decimal = str = std::stoi(empty);
    ss << "empty：" << decimal << "\n";

    std::cout << ss.str() << "\n";

	return 0;
}
