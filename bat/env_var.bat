@echo off
REM https://maku77.github.io/windows/batch/check-env-var.html


if not defined D_OPT (
  echo "D_OPT is not defined. use default."
   set D_OPT="default"
) else (
  echo "D_OPT is defined"
)
echo "D_OPT: %D_OPT%"

REM ===

if defined HOME (
  echo "HOME is defined"
  echo %HOME%
)

if not defined HOME (
  echo "HOME is not defined"
  exit /b
)


