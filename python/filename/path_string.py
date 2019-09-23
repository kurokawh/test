#! /usr/bin/env python

import os

# NOTE: user windows-native python.exe not cygwin version
path = r"C:\Program Files (x86)\Microsoft Visual Studio\Installer\vs_installer.exe"

bn = os.path.basename(path)
dn = os.path.dirname(path)
(file, ext) = os.path.splitext(path)

print("basename: " + bn)
print("dirname: " + dn)
print("splittext file: " + file)
print("splittext ext: " + ext)
