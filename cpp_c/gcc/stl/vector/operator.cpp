#include <vector>
#include <iostream>
 
int main(int argc, char** argv)
{
    std::vector<int> numbers {2, 4, 6, 8};
 
    std::cout << "Second element: " << numbers[1] << '\n';
    std::cout << "Second element: " << numbers.at(1) << '\n';

 
    numbers[0] = 5;
    std::cout << "All numbers:";
    for (auto i : numbers) {
        std::cout << ' ' << i;
    }
    std::cout << '\n';

    std::cout << "capacity: " << numbers.capacity() << '\n';
    std::cout << "size: " << numbers.size() << '\n';


// segmentation falt
//
//    std::cout << "100th element: " << numbers[100] << '\n';
//	numbers[100] = -1;
//    std::cout << "100th element: " << numbers[100] << '\n';
	
	return 0;
}
