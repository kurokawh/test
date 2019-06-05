#include <iostream>
#include <map>

int main ()
{
	std::map<int, char> m;
	m[3] = 'C';
	m[7] = 'G';
	m[8] = 'H';
	m[4] = 'D';
	m[5] = 'E';
	m[1] = 'A';
	m[2] = 'B';
	m[6] = 'F';

	for( auto i = m.begin(); i != m.end() ; ++i ) {
		std::cout << i->first << " " << i->second << "\n";
	}

	return 0;
}
