#include <list>
#include <iostream>
#include <algorithm>


void test(std::list<int> arg)
{
    std::cout << "All numbers:";
    for (auto i : arg) {
        std::cout << ' ' << i;
    }
    std::cout << '\n';
    std::cout << "element num: " << arg.size() << '\n';

	return;
} 
int main(int argc, char** argv)
{
    std::list<int> org = {2, 4, 6, 8};
    std::list<int> numbers(org);
	std::cout << "initial ===>\n";
	test(numbers);

	std::list<int>::iterator it_begin = numbers.begin();
	int head = *it_begin;
	std::cout << "pop: " << head << std::endl;

	// begin is erased, end is not erased (one before end is erased).
	numbers.erase(it_begin);
	std::cout << "erased ===>\n";
	test(numbers);
	
	return 0;
}
