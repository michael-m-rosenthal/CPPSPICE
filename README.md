## CPPSPICE

This is just a sample template that might be used to define a C++ library for the JPL SPICE project.

The goal is to create an intuitive object oriented C++ library that will be easier to use than the c code that was ported from Fortran 77 using `f2c`.

## Preliminaries

I am doing this using Ubuntu which is not officiall support by NAIF.
I think all you need is c shell, gcc, and g++ installed on your system.

## Build Instructions

First add some directories with the following command:

```
mkdir bin
mkdir build
mkdir lib
mkdir exe
```



Go to the `cpsice` directory and run the `makeall.csh` command as usual.
Please note that you may need to use the command `chmod +x makeall.csh`

After you run the `makeall.csh` command move to the `src_cpp` directory.

There is a `mkcppprodct.csh` that will build a c program that came from one other SPICE turorials on the NAIF website.

I made a C++ class that does the same thing.

The header file is `.h`.
Some people use `.hpp` to distinguish between C++ and C headers.
At one point I did so as well, and I do not remember why I stopped favoring that convention.
There is probably a good reason, but I might consider reinstating using `.hpp` c++ code for this project to distinguish between the two.

Anyway, you will find Doxygen markup for all the variables in the header so that people do not need to look at tutorials, websites, or pdf documents.
I try to make the header contain the documentation for the code so that this is the only documentation people need.
I like to follow it up with example code usage too.

There were quite a few variables I had no idea about how to describe.
I did my best to describe the ones that made sense to me, and I put todo placeholders for the rest.

The `demo_class.cpp` file is where I define all the class methods.
I do not use any Doxygen in the `.cpp` files except for the at the header of the file.
