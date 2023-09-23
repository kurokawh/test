#!/bin/bash
#
# https://linuxhint.com/check-exit-status-using-if-statement-bash/
# https://saturncloud.io/blog/how-to-check-if-a-program-exists-from-a-bash-script/

#ls /false-directory
if [ $? -eq 0 ]
then
    echo "execution suncessfull"
else
    echo "execution failed"
fi


which $1 > /dev/null 2>&1
if [ $? -eq 0 ]
then
    echo "command exists"
else
    echo "command does not exist"
fi
