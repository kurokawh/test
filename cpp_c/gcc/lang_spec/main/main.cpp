// main spec test
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

//	int ret = main(argc - 1, argv);
	int ret = fp2(argc - 1, argv); // recursive call to main
	if (ret < 0) {
		printf(" main: ret: %d\n", ret);
		return ret;
	}
	printf("exit main\n");
    return 0;
}
