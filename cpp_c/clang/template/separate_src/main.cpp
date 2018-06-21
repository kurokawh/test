#include <vector>
#include <iostream>

#include "template.h"

using namespace test;
 
int main(int argc, char** argv)
{
	Container c;
	int64_t retid = c.GetId(0);

	std::cout << "id: " << retid << std::endl;
	
	return 0;
}
