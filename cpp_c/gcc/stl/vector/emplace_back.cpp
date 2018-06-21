#include <vector>
#include <iostream>


void test(std::vector<int> arg)
{
    std::cout << "element num: " << arg.size() << '\n';

    std::cout << "All numbers:";
    for (auto i : arg) {
        std::cout << ' ' << i;
    }
    std::cout << '\n';

	return;
} 
int main(int argc, char** argv)
{
    std::vector<int> numbers {2, 4, 6, 8};
	test(numbers);
    std::cout << "Second element: " << numbers[1] << '\n';

	test(std::vector<int>{1,2});
 

	std::vector<int> x;
	x.emplace_back(1);
	test(x);
	
	return 0;
}
