#!/bin/bash

src=$1
dst="${src/.cpp/.out}"

flag=$2

g++ -I$UNIX_PRO_PATH -L$UNIX_PRO_PATH -lcomm $flag $src -o $dst
echo "gen $dst"
