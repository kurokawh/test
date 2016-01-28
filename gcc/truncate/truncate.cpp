#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char** argv)
{
	if (argc <3) {
		printf("\n");
		printf("arguments are missing.\n");
		printf("\n");
		printf("> %s FILE-NAME FILE-SIZE\n", argv[0]);
		printf("\n");
		return -1;
	}
	int ret = 0;

	//fpos_t offset = atoll(argv[2]);
	off_t offset = atoll(argv[2]);
	if (offset < 1) {
		printf("invalid offset: %d\n", offset);
		return -1;
	}

	FILE* fp = fopen(argv[1], "a");
	if (fp == NULL) {
		printf("open file failed: %s\n", argv[1]);
		return -1;
	}
	fclose(fp);

	ret = truncate(argv[1], offset - 1);
	if (ret) {
		printf("truncate failed: %s\n", argv[1]);
		return -1;
	}

	fp = fopen(argv[1], "a");
	if (fp == NULL) {
		printf("open file failed: %s\n", argv[1]);
		return -1;
	}

/*
	ret = fseek(fp, offset, SEEK_SET);
	//int ret = fsetpos(fp, &offset);
	if (ret) {
		printf("faled to seek. offset: %lld, ret: %d\n", offset, ret);
		return ret;
	}
*/
	size_t s = fwrite("a", 1, 1, fp);
	if (s != 1) {
		printf("faled write\n");
		return -1;
	}

	fclose(fp);
	printf("SUCCESS!!!\n");
	return 0;
}

