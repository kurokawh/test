#include <fstream>
#include <iostream>
#include <string>
#include <string.h> // strerror()

int main(int argc, const char* argv[])
{
//    std::ifstream ifs("test.txt");
    std::ifstream ifs(argv[1]);
    std::string str;
    if (ifs.fail())
    {
		int err = errno;
        std::cerr << "error: " << err << std::endl;
        std::cerr << "strerror: " << strerror(err) << std::endl;
        return -1;
    }
    while (getline(ifs, str))
    {
        std::cout << "[" << str << "]" << std::endl;
    }
    return 0;
}

