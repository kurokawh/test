#!/bin/tcsh
#
# http://www.not-enough.org/abe/manual/unix2-ad99/csh-if.html
# http://echoes.jp/saito/csh.html


set x = 1

### Is environment variable defined? ###
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
# if NOT
if ( ! $?x ) then
	echo 'if ( ! $?x ) true: not defined'
else
	echo 'if ( ! $?x ) false: defined'
endif
if ( ! $?y ) then
	echo 'if ( ! $?y ) true: not defined'
else
	echo 'if ( ! $?y ) false: defined'
endif



set x = 1
### string & number is not distinguished ###
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



if ( $x < 10 ) then
    echo "x(1) is smaller than 10"
else
	echo "x is bigger than 10"
endif

if ( $x < 0 ) then
    echo "x is smaller than 0"
else
	echo "x is bigger than 0"
endif
