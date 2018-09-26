#!/bin/tcsh
#
# http://www.not-enough.org/abe/manual/unix2-ad99/csh-if.html
# http://echoes.jp/saito/csh.html


set x = 1

# Is environment variable defined?
if ( $?x ) then
	echo "env x defined"
else
	echo "env x not defined"
endif

if ( $?y ) then
	echo "env y defined"
else
	echo "env y not defined"
endif
# setenv / unset
setenv y 1
unset x
if ( $?x ) then
	echo "env x defined"
else
	echo "env x not defined"
endif

if ( $?y ) then
	echo "env y defined"
else
	echo "env y not defined"
endif


set x = 1
# string & number is not distinguished
if ( $x == 1 ) then
    echo "x is 1"
else
	echo "x is not 1"
endif

if ( $x == "1" ) then
    echo 'x is "1"'
else
    echo 'x is not "1"'
endif


