#! /bin/csh

set build_dir    = "../build"
set bin_dir    = "../bin"
set local_lib_dir    = "../lib"
set local_include_dir    = "../include"

gcc demo.c -I$local_include_dir $local_lib_dir/cspice.a   -lm -o $bin_dir/demo_c
g++ demo_class.cpp -I$local_include_dir -c -O2 -std=c++11 -o $build_dir/demo_class.o
g++ demo.cpp $build_dir/demo_class.o -I$local_include_dir -B static $local_lib_dir/cspice.a -O2 -std=c++11 -o $bin_dir/demo_cpp