#!/bin/bash

src=$1
dst="${src/.cpp/.out}"

g++ -I$UNIX_PRO_PATH -L$UNIX_PRO_PATH -lcomm  $src -o $dst
echo "gen $dst"
