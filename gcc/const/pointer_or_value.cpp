
typedef char* PSTR;
int strlen_pstr(const PSTR str)
{
    int i;
//    for(i = 0; *str; str++) // error: increment of read-only parameter 'str'
//        i++;
    return i;
}

typedef const char* PCSTR;
int strlen_pcstr(PCSTR str)
{
    int i;
    for(i = 0; *str; str++)
        i++;
    return i;
}


int strlen_c1(const char* str) // same as ???
{
    int i;
    for(i = 0; *str; str++)
        i++;
    return i;
}
int strlen_c2(char const* str) // same as PCSTR
{
    int i;
    for(i = 0; *str; str++)
        i++;
    return i;
}
int strlen_c3(char* const str) // same as PSTR
{
    int i;
//    for(i = 0; *str; str++) // error: increment of read-only parameter 'str'
//        i++;
    return i;
}



const char* C1 = "c1";
char const* C2 = "c2";
char* const C3 = "c3"; // warning: deprecated conversion from string constant to 'char*' [-Wwrite-strings]
int main(int argc, char** argv)
{
	strlen_pstr("aaa"); // warning: deprecated conversion from string constant to 'PSTR {aka char*}' [-Wwrite-strings]
//	strlen_pstr(C1); // error: invalid conversion from 'const char*' to 'PSTR {aka char*}' [-fpermissive]
//	strlen_pstr(C2); // error: invalid conversion from 'const char*' to 'PSTR {aka char*}' [-fpermissive]
	strlen_pstr(C3);

	
	strlen_pcstr("aaa");
	strlen_pcstr(C1);
	strlen_pcstr(C2);
	strlen_pcstr(C3);

	strlen_c1("aaa");
	strlen_c1(C1);
	strlen_c1(C2);
	strlen_c1(C3);
	strlen_c2("aaa");
	strlen_c2(C1);
	strlen_c2(C2);
	strlen_c2(C3);
	strlen_c3("aaa"); // warning: deprecated conversion from string constant to 'char*' [-Wwrite-strings]
//	strlen_c3(C1);    // error: invalid conversion from 'const char*' to 'char*' [-fpermissive]
//	strlen_c3(C2);    // error: invalid conversion from 'const char*' to 'char*' [-fpermissive]
	strlen_c3(C3);
	
	return 0;
}
