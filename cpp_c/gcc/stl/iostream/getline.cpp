#include <fstream>
#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
//    std::ifstream ifs("test.txt");
    std::ifstream ifs(argv[1]);
    std::string str;
    if (ifs.fail())
    {
        std::cerr << "失敗" << std::endl;
        return -1;
    }
    while (getline(ifs, str))
    {
        std::cout << "[" << str << "]" << std::endl;
    }
    return 0;
}

