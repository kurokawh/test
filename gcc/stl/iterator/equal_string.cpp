#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>

typedef std::vector<std::string>	IdList;


int main(int argc, char** argv)
{
	IdList list;
	list.push_back("1");
	list.push_back("2");
	list.push_back("3");

	IdList::iterator it = list.begin();
	it++;
	it++;

	IdList::iterator it2 = list.begin();
	it2++;
	it2++;

	IdList::reverse_iterator rit = list.rbegin();

	// show value
	printf("((it++)++)->c_str(): %s, rit->c_str(): %s\n", it->c_str(), rit->c_str());

	std::string s = list.at(list.size() - 1);
	std::string s2("3");

	// result of (==)
//	printf("((it++)++): %p, rit: %p, ==: %d\n", it, rit, it == rit); // compile error
	printf("*((it++)++): %p, *rit: %p, ==: %d\n", *it, *rit, *it == *rit); // TRUE
//	printf("*((it++)++): %p, &list.at(list.size() - 1): %p, ==: %d\n", *it, &(list.at(list.size() - 1)), *it == &(list.at(list.size() - 1)); // compile error
	printf("*((it++)++): %p, list.at(list.size() - 1): %p, ==: %d\n", *it, list.at(list.size() - 1), *it == list.at(list.size() - 1)); // TRUE
	printf("s: %p, list.at(list.size() - 1): %p, ==: %d\n", s, list.at(list.size() - 1), s == list.at(list.size() - 1)); // TRUE but '%p' is different.

	printf("it: %p, it2: %p, ==: %d\n", it, it2, it == it2); // TRUE
	printf("s: %p, s2: %p, ==: %d\n", s, s2, s == s2); // TRUE but '%p' is different.
	return 0;
}
