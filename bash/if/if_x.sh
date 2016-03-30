#!/bin/bash

# 'if [ x"$1" != x ]' means check if "$1" is nil.
#   (same as 'if [ -z "$1" ]' )
# http://www.unix.com/shell-programming-and-scripting/194691-if-x-1-x-what-does.html


whoseargs="client"
while [ x"$1" != x ]; do
    case "$1" in
    # '' required to prevent cpp from treating "/*" as a C comment.
    /''*|\./''*)
 if [ "$whoseargs" = "client" ]; then
     if [ x"$client" = x ] && [ x"$clientargs" = x ]; then
  client="$1"
     else
  clientargs="$clientargs $1"
     fi
 else
     if [ x"$server" = x ] && [ x"$serverargs" = x ]; then
  server="$1"
     else
  serverargs="$serverargs $1"
     fi
 fi
 ;;
    --)
 whoseargs="server"
 ;;
    *)
 if [ "$whoseargs" = "client" ]; then
     clientargs="$clientargs $1"
 else
     # display must be the FIRST server argument
     if [ x"$serverargs" = x ] && \
   expr "$1" : ':[0-9][0-9]*$' > /dev/null 2>&1; then
  display="$1"
     elif [ "$1" = "-listen" ]; then
  listenarg=""
     else
  serverargs="$serverargs $1"
     fi
 fi
 ;;
    esac
    shift
done

echo "clientargs: $clientargs"
echo "serverargs: $serverargs"
