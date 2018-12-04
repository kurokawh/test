#include <vector>
#include <iostream>
#include <string>
#include <assert.h>


enum ValueType {
	ValueType_None = 0,	//
	ValueType_Int,		// "INTEGER"
	ValueType_Float,	// "REAL"
	ValueType_Text,		// "TEXT"
	ValueType_Blob,		// "NONE"
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

	std::string GenerateCreateTableSQL() {
		static const char* SQL_COLUMN_TYPE[] = {
			NULL,
			"INTEGER",
			"REAL",
			"TEXT",
			"NONE",  
			NULL,
		};
		return m_name + " "	+ SQL_COLUMN_TYPE[m_type];
	}
};

template <class T>
class IntField : public Field {
public:
	IntField(const std::string name) : 
		Field(name, ValueType_Int) {};
	virtual ~IntField() {}
	const T GetValue(const Value& val) const {
		assert(m_type == val.type);
		return static_cast<T>(val.v_int);
	}
};
template <class T>
class FloatField : public Field {
public:
	FloatField(const std::string name) : 
		Field(name, ValueType_Float) {};
	virtual ~FloatField() {}
	const T GetValue(const Value& val) const {
		assert(m_type == val.type);
		return static_cast<T>(val.v_float);
	}
};
template <class T>
class TextField : public Field {
public:
	TextField(const std::string name) : 
		Field(name, ValueType_Text) {};
	virtual ~TextField() {}
	const T GetValue(const Value& val) const {
		assert(m_type == val.type);
		return static_cast<T>(val.v_text);
	}
};

Field F1("aaa", ValueType_Int);
IntField<int> IF("ii");
TextField<std::string> TF("ttt");
FloatField<double> FF("ffff");

Value vals[] = {
	{ValueType_Int, "name-int", sizeof(int64_t), 123},
	{ValueType_Text, "name-text", 3, (int64_t)"xyg"},
	{ValueType_Float, "name-float", sizeof(double), static_cast<double>(1.5)}, // XX: val is shown as 5.94064-324 not 1.5.
};
 
int main(int argc, char** argv)
{
	std::cout << "name: " << F1.GetName() << std::endl;
	std::cout << "int: " << IF.GetValue(vals[0]) << std::endl;
	std::cout << "text: " << TF.GetValue(vals[1]) << std::endl;
	std::cout << "float: " << FF.GetValue(vals[2]) << std::endl;
	std::cout << "1.5: " << (double)1.5 << std::endl;

	vals[2].v_float = 1.6; // set val is OK
	std::cout << "float1.6: " << FF.GetValue(vals[2]) << std::endl;


	std::cout << "SQL: CREATE TABLE tbl_xxx(" 
			  << IF.GenerateCreateTableSQL() << ", "
			  << TF.GenerateCreateTableSQL() << ", "
			  << FF.GenerateCreateTableSQL() << ");"
			  << std::endl;
	return 0;
}


// list of field declaration test.
Field* flds[] = {
	&IF,
	&TF,
	&FF,
};
Field* fldnews[] = {
	new IntField<int>("ii"),
	new TextField<std::string>("ttt"),
};
IntField<int> ifs[] = {IntField<int>("i1"), IntField<int>("i2")};
/* NG
Field& fldrefs[] = {
	IF,
	TF,
	FF,
};
Field& ng[] = {
	IntField<int>("ii"),
	TextField<std::string>("ttt"),
};
*/
