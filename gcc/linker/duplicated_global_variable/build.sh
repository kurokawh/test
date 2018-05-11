gcc -c main.c # main() => foo() & bar2() & val
gcc -c foo.c # foo() => bar2()
gcc -c bar.c # bar(), foo()
gcc -c bar_val.c # bar(), foo(), val
gcc -c bar2.c # bar(), bar2(), foo2(), val
gcc -c foo_cpp.cpp # foo(), A

ar rcs libfoo.a foo.o # libfoo.a: [foo()]
ar rcs libbar.a bar.o bar2.o # libbar.a: [bar(), foo()], [bar(), bar2(), foo2(), val]
ar rcs libbar2.a bar2.o # libbar2.a: [bar(), bar2(), foo2(), val]
ar rcs libbar_val.a bar_val.o # libbar.a: [bar(), foo(), val]
ar rcs libfoo_cpp.a foo_cpp.o # libbar.a: [foo(), A]

# OK: foo() in libbar.a is not linked because foo() has been already provided by libfoo.a.
gcc main.o -L. -lfoo -lbar -lbar2
echo OK

# OK: val in libbar_val.a is not linked because val has been already provided by libbar2.a.
gcc main.o -L. -lfoo -lbar -lbar2 -lbar_val
echo OK2

# NOTE: global constructor does not run if object file is not stored.
gcc main.o -L. -lfoo -lfoo_cpp -lbar -lbar2
echo OK3-1 #A is NOT constructed because foo_cpp.o is not stored.
gcc main.o -L. -lfoo_cpp -lfoo -lbar -lbar2
echo OK3-2 #A is constructed

# NG: error because bar() in libbar.a and libbar2.a (loaded for bar2()).
# > ./libbar.a(bar.o):bar.c:(.text+0x0): multiple definition of `bar'
# > ./libbar.a(bar2.o):bar2.c:(.text+0x0): first defined here
gcc main.o -L. -lbar -lbar2 -lfoo 
echo NG

# NG2: error because all object files are to be linked executable.
# > bar2.o:bar2.c:(.text+0x0): multiple definition of `bar'
# > bar.o:bar.c:(.text+0x0): first defined here
# > foo.o:foo.c:(.text+0x0): multiple definition of `foo'
# > bar.o:bar.c:(.text+0x24): first defined here
gcc *.o
echo NG2
