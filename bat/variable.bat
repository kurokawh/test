@echo off
REM set command result to varialbe.
REM http://mmasashi.hatenablog.com/entry/20100207/1265557400

for /f "usebackq tokens=*" %%i in (`cygpath -ua .`) do @set RESULT=%%i
echo %RESULT%
