#!/bin/tcsh
#
# https://learnxinyminutes.com/docs/tcsh/

# --- Variables ---------------------------------------------------------------
# The shell maintains a list of variables, each of which has as value a list of
# zero or more words. The values of shell variables can be displayed and
# changed with the `set' and `unset' commands.
# The system maintains its own list of ``environment'' variables.
# These can be displayed and changed with `printenv', `setenv' and `unsetenv'.
# The syntax of setenv is similar to POSIX sh.

# Assign a value or nothing will create a variable
# Assign nothing
set var
# Assign a numeric value
# the '@' denotes the expression is arithmetic; it works similar to 'set' but
# the right value can be a numeric expression.
@ var = 1 + 2
# Assign a string value
set var = "Hello, I am the contents of 'var' variable"
# Assign the output of a program
set var = `ls`

# Remove a variable
unset var
# Prints 1 (true) if the variable `var' exists otherwise prints 0 (false)
echo $?var
# Print all variables and their values
##### set

set var = "sample string"
# Prints the contents of 'var'
echo $var;
echo "$var";
# Prints the string `$var'
echo \$var
echo '$var'
# braces can be used to separate variable from the rest when its needed
set num = 12; echo "There ${num}th element"

# Prints the number of characters of the value: 6
set var = '123456'; echo $%var

### LISTs
# Assign a list of values
set var = ( one two three four five )
# Print all the elements: one two three four five
echo $var
echo $var[*]
# Print the count of elements: 5
echo $#var
# Print indexed element; prints the second element: two
echo $var[2]
# Print range of elements; prints 2nd up to 3rd: two, three
echo $var[2-3]
# Prints all elements starting from the 3rd: three four five
echo $var[3-]
# Prints print all up to 3rd element: one two three
echo $var[-3]

### Special Variables
# $argv         list of command-line arguments
# $argv[0]      this file-name (the file of the script file)
# $# $0, $n, $* are the same as $#argv, $argv[0], $argv[n], $argv[*]
# $status, $?   the exit code of the last command that executed
# $_            the previous command line
# $!            the PID of the last background process started by this shell
# $$            script's PID

# $path, $PATH  the list of directories that will search for executable to run
# $home, $HOME  user's home directory, also the `~' can be used instead
# $uid          user's login ID
# $user         user's login name
# $gid          the user's group ID
# $group        the user's group-name
# $cwd, $PWD    the Current/Print Working Directory
# $owd          the previous working directory
# $tcsh         tcsh version
# $tty          the current tty; ttyN for linux console, pts/N for terminal
#               emulators under X
# $term         the terminal type
# $verbose      if set, causes the words of each command to be printed.
#               can be set by the `-v' command line option too.
# $loginsh      if set, it is a login shell

# TIP: $?0 is always false in interactive shells
# TIP: $?prompt is always false in non-interactive shells
# TIP: if `$?tcsh' is unset; you run the original `csh' or something else;
#      try `echo $shell'
# TIP: $verbose this is useful to debugging scripts
# NOTE: $PWD and $PATH are synchronised with $cwd and $pwd automatically.

# --- Variable modifiers ------------------------------------------------------
# Syntax: ${var}:m[:mN]
# Where <m> is:
# h : the directory  t : the filenane  r : remove extension   e : the extension
# u : uppercase the first lowercase letter
# l : lowercase the first uppercase letter
# p : print but do not execute it (hist)
# q : quote the substituted words, preventing further substitutions
# x : like q, but break into words at white spaces
# g : apply the following modifier once to each word
# a  : apply the following modifier as many times as possible to single word
# s/l/r/ : search for `l' and replace with `r', not regex; the `&' in the r is
# replaced by l
# & : Repeat the previous substitution
