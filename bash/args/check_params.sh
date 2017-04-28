#!/bin/bash

# 実行時に指定された引数の数、つまり変数 $# の値が 3 でなければエラー終了。
if [ $# -ne 3 ]; then
  echo "指定された引数は$#個です。" 1>&2
  echo "実行するには3個の引数が必要です。" 1>&2
  exit 1
fi

# show all arguments"
echo "ALL ARG: $@"
# show all arguments from 2nd arg."
echo "2nd and follwer: ${@:2}"
echo ${@:2}
# show all arguments from 3rd arg."
echo "${@:3}"
# 4th arg is nothing."
echo ${@:4}
echo "4th is empty: ${@:4}"


# ヒアドキュメントでメッセージを表示する。
cat <<__EOT__
指定された引数は、
  $1
  $2
  $3
の$#個です。
__EOT__

exit 0
