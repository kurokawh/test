#include <iostream>
#include <string>
#include <array>

using namespace std;

struct address1 {
    int a;
};

struct address4 {
    unsigned int a1:8;
    unsigned int a2:8;
    unsigned int a3:8;
    unsigned int a4:8;
};
ostream& operator<<(ostream& stream, const address4& a) {
    return stream << a.a1 << "." << a.a2 << "." << a.a3 << "." << a.a4;
}

union X1 {
    address1 a;
    address4 b;
    int c;
};

union X2 {
    int a;
    address4 b;
    int c;
};

static constexpr int initial = 0x0100007f;
constexpr X1 x1_global {{initial}};
constexpr X2 x2_global {initial};
const X1 x1_global_nonexpr {{initial}};
const X2 x2_global_nonexpr {initial};

void test();
int main() {
    static constexpr X1 x1_static {{initial}};
    static constexpr X2 x2_static {initial};
    static const X1 x1_static_nonexpr {{initial}};
    static const X2 x2_static_nonexpr {initial};
    constexpr X1 x1_local {{initial}};
    constexpr X2 x2_local {initial};
    const X1 x1_local_nonexpr {{initial}};
    const X2 x2_local_nonexpr {initial};
#define TEST(v)     cout << __FILE__ "(" << __LINE__ << "): " #v ": " << v.b << endl;
    TEST(x1_global)
    TEST(x2_global)
    TEST(x1_global_nonexpr)
    TEST(x2_global_nonexpr)
    TEST(x1_static)
    TEST(x2_static)
    TEST(x1_static_nonexpr)
    TEST(x2_static_nonexpr)
    TEST(x1_local)
    TEST(x2_local)
    TEST(x1_local_nonexpr)
    TEST(x2_local_nonexpr)

	test();

	return 0;
}
enum Type
{
	Type_None = 0,
	Type_Int,
	Type_Float,
	Type_Text,
	Type_Blob,
	Type_Null,
};
struct FieldValue
{
	Type	type;
	const char* name;
	int32_t		size;
	union 
	{
		int64_t		v_int;
		double		v_float;
		const char* v_text;
		const void* v_blob;
	};
};

void test()
{
	const char cstr[] = "pointer to string";
//	FieldValue f = {Type_Text, "name", 3, {"123"}}; // NG
//	FieldValue f = {Type_Text, "name", 3, xxx}; // NG
	FieldValue f[] = {
		{Type_Int, "name-int", sizeof(int64_t), 123}, // OK???
		{Type_Text, "name", 3, (int64_t)"123"}, // OK???
		{Type_Text, "name2", sizeof(cstr) - 1, (int64_t)cstr} // OK???
	};

	for (int i = 0; i < sizeof(f)/sizeof(FieldValue); i++) {
		if (f[i].type == Type_Text) {
			printf("name: %s, text value: %s\n", f[i].name, f[i].v_text);
		}
		if (f[i].type == Type_Int) {
			printf("name: %s, int value: %ld\n", f[i].name, f[i].v_int);
		}
	}
}
