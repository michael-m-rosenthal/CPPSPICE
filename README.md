# An Documented Example Using cspice with C++

The objective of the code in this repository is to write a C++ program that determines times of solar occultations (the moon blocks the sun as seen from earth) in the period 2030 JAN 01 to 2040 JAN 01.
It Uses NAIF's C++11 "Coding Style and Standards" document (attached) and examples of NAIF's existing CSPICE routines as guides.

## Approach

I will link the static libraries that cspice compiles and call them within c++ code.
In particular, I anticipate that I will use the `SPICE Geometry Finder (GF) Subsystem` [found here](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/29_geometry_finder.pdf).
To test my code, I will try it on a period of time in the past where I can look up historic solar occultations.

I am going to accomplish this task sequentially in the following steps:

1) Read the coding style standard found in the `SPICE2_Coding_Style_and_Standards_2022-02-17.md` file
1) Write a simple c program with hard coded inputs that uses the `SPICE Geometry Finder (GF) Subsystem` [found here](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/29_geometry_finder.pdf)
1) Write a C++ program that deals the dynamic memory allocation
1) Write a C++ class that handles the memory management

Along the way I will explain the progression of the code into it final form.

## Preliminaries

I am doing this on Ubuntu (focal Fossa) which is not official support by NAIF.
I think that all you need is c shell, gcc, and g++ installed on your system.
I made a script `install_focal_preliminaries.sh` that will install the preliminaries files.
It must be ran either as root or with `sudo` privileges.
You can do so with the following command.

```
chmod +x install_focal_preliminaries.sh
sudo ./install_focal_preliminaries.sh
```


You will also need to create some directories to store compiled shared objects, static libraries, and compiled binaries. If you open a terminal in the directory that this `README.md` file is located in, then you should be able to create the directories with the following command.

```
mkdir bin
mkdir build
mkdir cspice/lib
mkdir cspice/exe
```

These directories do not get pushed to the repository because I git ignore them so that I do not accidentally tell git to keep track of changes made to compiled binaries.
The build directory will contain the shared objects that I create with my c++ code.
The bin directory will contain the API and other binaries compiled from my c++ code.
I do not track changes with these files with git because it makes the repository big when you track things like that, and it is better just to archive the binaries using an artifact repository or a collection of compressed files.

You may also wish to install a nice text editor like `atom`, but that is optional.
I heart good things about `sublime` and `vscode` too.
Personally, I like `vim` and `grep`.
You can install `atom` using snap with the following command.

```
sudo snap install atom --classic
```
### Build CSPICE

We will need to build the cspice static libraries from before we can link them.
To do that you will need c-shell and the build essentials installed as I mentioned earlier.
If you have c-shell and gcc installed, then you should be able to the run the `./makall.csh` script from within the `cspice` directory after you give it execute permission.

If you open a terminal in the directory that this `README.md` file is located in, then you should be able to build cspice with the following command.

```
cd cspice
chmod +x makeall.csh
./makeall.csh
```

### Build Dockerfile Testing Environment

I have also included make a Dockerfile that will create a testing environment that can be used for automated testing later.
I will not have time to go into much detail with that for this coding assignment, but I will mention that docker images like this a commonly used in CI/CD DEVOPS applications using Jenkins and Gitlab.

https://docs.docker.com/engine/install/ubuntu/

I like to keep my dockerfiles shallow (calling other scripts) so that the build scripts that I use to create the docker image are exactly available for someone who wants to build the environment on the host system.

## Build Instructions





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
