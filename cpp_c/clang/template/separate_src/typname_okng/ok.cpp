template<typename T>
class MyTemplate
{
  class Inner {};
  Inner met();
};

template<typename T>
typename MyTemplate<T>::Inner  MyTemplate<T>::met()
{ }
