// https://stackoverflow.com/questions/19845478/is-it-possible-to-declare-a-friend-function-as-static

//#define COMPILE_OK
#ifdef COMPILE_OK
class A;
static void IncrementValue(A & a);
#endif // COMPILE_OK

class A
{
public:
   A() {/* empty */}

private:
   friend void IncrementValue(A &);
   int value;
};

static void IncrementValue(A & a)
{
   a.value++;
}   

int main(int, char **)
{
   A a;
   IncrementValue(a);
   return 0;
}
