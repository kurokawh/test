@echo off

if "%1"=="" (
	echo "no argument"
	echo "need at least 1 arg."
	exit /b 0
)

if "%2"=="2" (
	echo "2nd option is 2!"
	shift /1
) else (
	echo "2nd option is not 2!"
)

if "%2" neq "x" (
	echo "2nd or 3rd option is not `x`!"
REM	shift /1
) else (
	echo "2nd or 3rd option is `x`!"
)



echo "check %2"
if exist %2 (
	echo "%2 exist!"
) else (
	echo "%2 is not file or directory."
)

