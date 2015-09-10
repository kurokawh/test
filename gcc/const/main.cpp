#include <stdlib.h>

class Test
{
public:
	void normal() {}
};
class ConstTest
{
public:
//	ConstTest() : m_val(0), m_const_int(1) {}
	ConstTest() : m_obj(this) {}
	void constFunc(int val) const;
	void normalFunc(int val);
private:
	mutable int m_val;
//	const int m_const_int; // must be initialized 
	mutable ConstTest* m_obj;
	mutable Test m_test;
};

void ConstTest::constFunc(int val) const
{
	m_val = val;
//	normalFunc(val); // error: passing 'const ConstTest' as 'this' argument of 'void ConstTest::normalFunc(int)' discards qualifiers
//	m_obj = this; //  error: invalid conversion from 'const ConstTest* const' to 'ConstTest*' 
	m_obj->normalFunc(val);
	this->constFunc(val);

	m_test.normal();
	return;
}

void ConstTest::normalFunc(int val)
{
	m_val = val;
	return;
}


void test(const ConstTest& obj)
{
//	obj.normalFunc(1);
	obj.constFunc(10);
}
int main(int argc, char** argv)
{
	ConstTest obj;
	obj.normalFunc(1);
	test(obj);
	return 0;
}
