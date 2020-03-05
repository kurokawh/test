#include <stdlib.h>
#include <string>

struct OrgData
{
	int ival;
	char sval[20];
	OrgData* ptr;
	int ival2;
};

struct Holder
{
	union
	{
		OrgData od;
		struct
		{
			int alias_ival;
			char alias_sval[20];
			OrgData* alias_ptr;
			int alias_ival2;
		};
	};
};


void test(Holder* h)
{
	printf("alias_ival: %d\n", h->alias_ival);
	printf("alias_ival2: %d\n", h->alias_ival2);
}

int main(int argc, char** argv)
{
	printf("sizeof(OrgData): %d, sizeof(Holder): %d\n", sizeof(OrgData), sizeof(Holder));
	OrgData od = {1, "aaa", nullptr, 222};
//	test(od); // ERROR


	Holder h;
	h.od = od;
	test(&h);
	return 0;
}
