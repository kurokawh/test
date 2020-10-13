REM infinit loop sample

echo off


set count=0

:start

REM https://jj-blues.com/cms/wantto-calculationinbatfile/
set /a count=%count%+1
echo %count%

sleep 5

goto :start
