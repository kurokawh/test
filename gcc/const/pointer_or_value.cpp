
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



int main(int argc, char** argv)
{
	strlen_pstr("aaa"); // warning: deprecated conversion from string constant to 'PSTR {aka char*}' [-Wwrite-strings]
	strlen_pcstr("aaa");

	strlen_c1("aaa");   // warning: deprecated conversion from string constant to 'PSTR {aka char*}' [-Wwrite-strings]
	strlen_c2("aaa");
	strlen_c3("aaa");   // warning: deprecated conversion from string constant to 'char*' [-Wwrite-strings]
	
	return 0;
}
