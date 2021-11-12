#!/usr/bin/env python
# -*- coding: utf-8 -*-

string = input("文字列を入力してください:")
if string.isdecimal():
    print(string, "は数字です")
elif string.isalpha():
    print(string, "はアルファベットです")
else:
    print(string, "は数字でもアルファベットでもありません")
