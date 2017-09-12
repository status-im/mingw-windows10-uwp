#!/bin/sh

gcc -dumpspecs | sed -e 's/-lmingwex/-lwinstorecompat -lmingwex -lwinstorecompat -lole32 -lruntimeobject/' -e "s/-lmsvcrt/-lmsvcr120_app/" >./specfile
gcc -specs=./specfile -shared -o PureMinGWDLL.dll MinGWDLL.c pureDLL.c -Wl,--dynamicbase
./appcontainer.pl PureMinGWDLL.dll