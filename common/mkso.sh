#!/bin/bash


cd "$UNIX_PRO_PATH"
python gen_wrapper.py

target="libcomm.so"
g++  util.cpp wrapper.cpp  -fPIC -shared -o ${target}

echo "gen $target finish"

