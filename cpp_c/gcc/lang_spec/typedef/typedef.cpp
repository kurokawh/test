#include <stdio.h>

namespace original {
	enum OrgEnum {
		ENUM_A,
		ENUM_B,
		ENUM_C,
	};

	void test(OrgEnum e)
	{
		return;
	}
}


namespace mine {

	// re-define Enum for my namespace
	typedef original::OrgEnum MyEnum;

	void test(MyEnum e)
	{
		return;
	}

};

int main(int argc, char** argv)
{
	original::OrgEnum oe = original::ENUM_A;
	oe = original::OrgEnum::ENUM_A;
	mine::MyEnum me = oe; // OK

	original::test(oe);
	original::test(me);


	me = original::ENUM_A; // XXX: "original" should not be used.
	me = mine::MyEnum::ENUM_A; // OK!!!
	mine::test(oe);
	mine::test(me);

	printf("OK!\n");
	return 0;
}
