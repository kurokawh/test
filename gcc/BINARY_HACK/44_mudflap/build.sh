gcc -g -fmudflap -o testflap testflap.c -lmudflap
./testflap

# install libmudflap if following compile error occurs.
#
# cc1: fatal error: mf-runtime.h: No such file or directory
# compilation terminated.
#
# % sudo apt-get install libmudflap0 libmudflap0-dbg libmudflap0-4.6-dev
