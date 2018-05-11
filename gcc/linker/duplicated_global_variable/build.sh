gcc -c main.c # main() => foo() & bar2()
gcc -c foo.c # foo() => bar2()
gcc -c bar.c # bar(), foo()
gcc -c bar2.c # bar(), bar2(), foo2()

ar rcs libfoo.a foo.o # libfoo.a: [foo()]
ar rcs libbar.a bar.o bar2.o # libbar.a: [bar(), foo()], [bar(), bar2(), foo2()]
ar rcs libbar2.a bar2.o # libbar2.a: [bar(), bar2(), foo2()]

# OK: foo() in libbar.a is not linked because foo() has been already provided by libfoo.a().
gcc main.o -L. -lfoo -lbar -lbar2
echo OK

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
