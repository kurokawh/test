// main spec test
// 
// spec says: https://en.cppreference.com/w/cpp/language/main_function
//   The main function has several special properties:
//   1) It cannot be used anywhere in the program
//     a) in particular, it cannot be called recursively
//     b) its address cannot be taken
//
// but g++ and clang allows these a) & b) behavior.

#include <stdio.h>
#include <functional>

int main(int argc, char** argv)
{
//	std::function<int(int,char**)> fp = main;
	int (*fp2)(int,char**);
	fp2 = main;

	printf("argc: %d\n", argc);
	if (argc < 0) {
		return -1;
	}

	int ret = main(argc - 1, argv);
//	int ret = fp2(argc - 1, argv); // recursive call to main
	if (ret < 0) {
		printf(" main: ret: %d\n", ret);
		return ret;
	}
	printf("exit main\n");
    return 0;
}
