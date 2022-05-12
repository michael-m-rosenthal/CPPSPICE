#! /bin/bash

build_dir="./build"
bin_dir="./bin"
local_lib_dir="./cspice/lib"
local_include_dir="./cspice/include"
src_dir="./src"


#gcc pre_src/occfind.c -I$local_include_dir $local_lib_dir/cspice.a   -lm -o $bin_dir/occfind_c

g++ $src_dir/Occultations.cpp -I$local_include_dir -c -O2 -std=c++11 -o $build_dir/Occultations.o
g++ $src_dir/occfind.cpp $build_dir/Occultations.o -I$local_include_dir -B static $local_lib_dir/cspice.a -O2 -std=c++11 -o $bin_dir/occfind
