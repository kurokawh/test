#include <iostream>
#include <string>

void concatenating_strings()
{
  std::string firstlevel ("com");
  std::string secondlevel ("cplusplus");
  std::string scheme ("http://");
  std::string hostname;
  std::string url;

  hostname = "www." + secondlevel + '.' + firstlevel;
  url = scheme + hostname;

  std::cout << url << '\n';

}

void op_lt()
{
  std::string a ("a");
  std::string b ("b");
  if (a < b) {
	  std::cout << "a<b" << std::endl;
  } else {
	  std::cout << "a>=b" << std::endl;
  }
}

int main(int argc, char** argv)
{
	concatenating_strings();
	op_lt();
	return 0;
}
