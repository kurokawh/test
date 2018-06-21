#include <vector>
#include <iostream>
#include <algorithm>


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
    std::vector<int> org = {2, 4, 6, 8};
    std::vector<int> numbers(org);
	test(numbers);

	std::vector<int>::iterator it_begin = numbers.begin();
	std::vector<int>::iterator it_end = numbers.end();
	it_begin++;
	it_end--;

	// begin is erased, end is not erased (one before end is erased).
	numbers.erase(it_begin, it_end);
	std::cout << "erased ===>\n";
	test(numbers);
	std::cout << "org ===>\n";
	test(org);
	
	return 0;
}
