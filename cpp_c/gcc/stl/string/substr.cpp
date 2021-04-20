#include <iostream>
#include <sstream> // hex
#include <string>


int main(int argc, char** argv)
{
 

	std::string str = "0123";

    std::cout << "str.size(): " << str.size() << "\n";

    std::cout << "str.substr(2): " << str.substr(2) << "\n";
    std::cout << "str.substr(3): " << str.substr(3) << "\n";
    std::cout << "str.substr(4): " << str.substr(4) << "\n";

// exception!
//    std::cout << "str.substr(5): " << str.substr(5) << "\n";

	return 0;
}
