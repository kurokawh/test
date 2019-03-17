// map::find
#include <iostream>
#include <map>

int main ()
{
/*
  std::map<char,int> mymap;
  mymap['a']=50;
  mymap['b']=100;
  mymap['c']=150;
  mymap['d']=200;
*/
  std::map<char,int> mymap = {
    {'a', 50},
    {'b', 100},
    {'c', 150},
    {'d', 200},
  };
  std::map<char,int>::iterator it;

  it = mymap.find('b');
  if (it != mymap.end())
    mymap.erase (it);

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';

  return 0;
}

