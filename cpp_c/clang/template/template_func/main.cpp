#include <vector>
#include <iostream>
#include <string>


enum ValueType {
	ValueType_None = 0,
	ValueType_Int,
	ValueType_Float,
	ValueType_Text,
	ValueType_Blob,
	ValueType_Null,
};
struct Value
{
	ValueType	type;
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
enum Result {
	SUCCESS = 0,
	E_TPYE_MISMATCH = -1,
	E_INVALID_VALUE,
};

class Field {
protected:
	std::string m_name;
	ValueType m_type;
public:
	Field(const std::string name, const ValueType type) : 
		m_name(name),
		m_type(type) {};
	virtual ~Field() {}
	const std::string& GetName() const {return m_name;} 
	const ValueType GetType() const {return m_type;}
};

template <class T>
class TypedField : public Field {
public:
	TypedField(const std::string name, const ValueType type) : 
		Field(name, type) {};
	virtual ~TypedField() {}
	const T GetValue(const Value& val) const {
		if (m_type != val.type) {
			return E_TPYE_MISMATCH;
		}
		switch (val.type) {
		case ValueType_Int:
			return static_cast<T>(val.v_int);
		case ValueType_Float:
			return static_cast<T>(val.v_float);
		case ValueType_Text:
			return static_cast<T>(val.v_text);
		case ValueType_Blob:
			return static_cast<T>(val.v_blob);
		case ValueType_None: // through
		case ValueType_Null: // through
		default:
			// err
			break;
		}
		return E_INVALID_VALUE;
	}
};

Field F1("aaa", ValueType_Int);
TypedField<int> CF1("ccc", ValueType_Int);

const Value vals[] = {
	{ValueType_Int, "name-int", sizeof(int64_t), 123},
	{ValueType_Text, "name-text", 3, (int64_t)"xyg"},
	{ValueType_Float, "name-float", sizeof(float), 0.1},
};
 
int main(int argc, char** argv)
{
	std::cout << "name: " << F1.GetName() << std::endl;
	std::cout << "int: " << CF1.GetValue(vals[0]) << std::endl;
	
	return 0;
}
