template<typename T>
class MyTemplate
{
  class Inner {};
  Inner met();
};

template<typename T>
MyTemplate<T>::Inner  MyTemplate<T>::met()
{ }
