#include <stdlib.h>

class Test
{
public:
	void normal() {}
};

class ConstTest;
typedef const ConstTest* Defined;

class ConstTest
{
public:
//	ConstTest() : m_val(0), m_const_int(1) {}
	ConstTest() : m_obj(this) {}
	void constFunc(int val) const;
	void normalFunc(int val);
private:
	mutable int m_val;
//	const int m_const_int; // error: uninitialized member 'ConstTest::m_const_int' with 'const' type 'const int' [-fpermissive]
	mutable ConstTest* m_obj;
	mutable const ConstTest* m_const_obj;
	const mutable ConstTest* cm_obj;
	const ConstTest* const_obj;
	
//	mutable ConstTest* const cmpc_obj; // error: uninitialized member 'ConstTest::cmc_obj' with 'const' type 'ConstTest* const' [-fpermissive]
	mutable ConstTest const * cmcp_obj;
	Defined def_obj;
	mutable Test m_test;
};

void ConstTest::constFunc(int val) const
{
	m_val = val;     // OK: because m_val is mutable.
	
//	m_obj = this; //  error: invalid conversion from 'const ConstTest* const' to 'ConstTest*' 
	m_const_obj = this; //  OK: because variable itself is not const (only pointer is const).
	cm_obj = this;
	cmcp_obj = this;
//	const_obj = this;   // error: assignment of member 'ConstTest::const_obj' in read-only object

	m_obj->normalFunc(val);

	// calling const func is OK.
	this->constFunc(val);
	m_obj->constFunc(val);
	m_const_obj->constFunc(val);
	cm_obj->constFunc(val);
	cmcp_obj->constFunc(val);
	const_obj->constFunc(val);
	def_obj->constFunc(val);
	// calling not const func is NG
//	normalFunc(val); // error: passing 'const ConstTest' as 'this' argument of 'void ConstTest::normalFunc(int)' discards qualifiers
	m_obj->normalFunc(val);
//	m_const_obj->normalFunc(val); // error: passing 'const ConstTest' as 'this' argument of 'void ConstTest::normalFunc(int)' discards qualifiers [-fpermissive]
//	const_obj->normalFunc(val);   // error: passing 'const ConstTest' as 'this' argument of 'void ConstTest::normalFunc(int)' discards qualifiers [-fpermissive]
//	def_obj->normalFunc(val);     // error: passing 'const ConstTest' as 'this' argument of 'void ConstTest::normalFunc(int)' discards qualifiers [-fpermissive]

	m_test.normal();
	return;
}

void ConstTest::normalFunc(int val)
{
	m_val = val;
	
	m_obj = this;
	m_const_obj = this;
	cm_obj = this;
	cmcp_obj = this;
	const_obj = this;
	
	return;
}


void test(const ConstTest& obj)
{
//	obj.normalFunc(1); // error: passing 'const ConstTest' as 'this' argument of 'void ConstTest::normalFunc(int)' discards qualifiers [-fpermissive]
	obj.constFunc(10);
}
int main(int argc, char** argv)
{
	ConstTest obj;
	obj.normalFunc(1);
	test(obj);
	return 0;
}
