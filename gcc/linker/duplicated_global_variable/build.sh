gcc -c foo.c # foo() => bar2()
gcc -c bar.c # bar(), foo()
gcc -c bar2.c # bar(), bar2(), foo2()
gcc -c main.c # main() => foo() & bar2()

ar rcs libfoo.a foo.o # libfoo.a: [foo()]
ar rcs libbar.a bar.o bar2.o # libbar.a: [bar(), foo()], [bar(), bar2(), foo2()]
ar rcs libbar2.a bar2.o # libbar2.a: [bar(), bar2(), foo2()]

# OK
gcc main.o -L. -lfoo -lbar -lbar2
echo OK

# NG: 
# > ./libbar.a(bar.o):bar.c:(.text+0x0): multiple definition of `bar'
# > ./libbar.a(bar2.o):bar2.c:(.text+0x0): first defined here
gcc main.o -L. -lbar -lbar2 -lfoo 
echo NG

# NG2:
# > bar2.o:bar2.c:(.text+0x0): multiple definition of `bar'
# > bar.o:bar.c:(.text+0x0): first defined here
# > foo.o:foo.c:(.text+0x0): multiple definition of `foo'
# > bar.o:bar.c:(.text+0x24): first defined here
gcc *.o
echo NG2
