#!/bin/bash

file=$0
dir=`pwd`

# test.txtはファイルかどうかをチェック
if [ -f $file ]; then
    echo "$file is a file."
else
    echo "$file is NOT a file."
fi

# testdirはファイルかどうかをチェック
if [ -f $dir ]; then
    echo "$dir is a file."
else
    echo "$dir is NOT a file."
fi

# test.txtはディレクトリかどうかをチェック
if [ -d $file ]; then
    echo "$file is a directory."
else
    echo "$file is NOT directory."
fi

# testdirはディレクトリかどうかをチェック
if [ -d $dir ]; then
    echo "$dir is a directory."
else
    echo "$dir is NOT a directory."
fi

# check existance
if [ -e $file ]; then
    echo "$file exists."
else
    echo "$file does not exists."
fi
if [ -e $dir ]; then
    echo "$dir exists."
else
    echo "$dir does not exists."
fi
# check if NOT exist
if [ ! -e $dir ]; then
    echo "$dir does NOT exists."
else
    echo "$dir exists."
fi
if [ ! -e $file ]; then
    echo "$file does NOT exists."
else
    echo "$file exists."
fi
if [ ! -e xxx ]; then
    echo "xxx does NOT exists."
else
    echo "xxx exists."
fi
