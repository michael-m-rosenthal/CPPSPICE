# An Documented Example Using cspice with C++

The objective of the code in this repository is to write a C++ program that determines times of solar occultations (the moon blocks the sun as seen from earth) in the period 2030 JAN 01 to 2040 JAN 01.
It Uses NAIF's C++11 "Coding Style and Standards" document (attached) and examples of NAIF's existing CSPICE routines as guides.

## Approach

I will link the static libraries that cspice compiles and call them within c++ code.
In particular, I anticipate that I will use the `SPICE Geometry Finder (GF) Subsystem` [found here](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/29_geometry_finder.pdf).
To test my code, I will try it on a period of time in the past where I can look up historic solar occultations.

I am going to accomplish this task sequentially in the following steps:

1) Read the coding style standard found in the `SPICE2_Coding_Style_and_Standards_2022-02-17.md` file
1) Write a simple c program with hard coded inputs that uses the `SPICE Geometry Finder (GF) Subsystem`
1) Write a C++ program that deals the dynamic memory allocation
1) Write a C++ class that handles the memory management

Along the way I will explain the progression of the code into it final form.

## Preliminaries

I am doing this on Ubuntu (Focal Fossa) which is not official support by NAIF.
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
I do not track changes with these files with git because it makes the repository big when you track things like that, and it is better just to archive the binaries using an artifact registry or a just collection of compressed files.

You may also wish to install a nice text editor like `atom`, but that is optional.
I hear good things about `sublime` and `vscode` too.
Personally, I like `vim` and `grep`.
You can install `atom` using snap with the following command.

```
sudo snap install atom --classic
```


## Download CSPICE from NAIF

I have already included `cspice` in this repository
In retrospect, I probably should have git ignored this entire directory.
I made a script called `download_and_unzip_linux_64_cspice.sh` that will download and unzip CSPICE.
The script requires `wget`.
If you do not already have wget, you can install it with the following line of code with root or sudo privledges.

```
apt-get install wget
```

You can run the script with the following command.

```
chmod +x ./download_and_unzip_linux_64_cspice.sh
./download_and_unzip_linux_64_cspice.sh
```

You can also just install it from the NAIF site [here](https://naif.jpl.nasa.gov/naif/toolkit_C_PC_Linux_GCC_64bit.html)


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

## A Dockerfile for testing code

I have also included make a Dockerfile that will create a testing environment that can be used for automated testing later.
I will not have time to go into much detail with that for this coding assignment, but I will mention that docker images like this are commonly used for CI/CD DEVOPS using Jenkins or Gitlab runners.

https://docs.docker.com/engine/install/ubuntu/

I like to keep my dockerfiles shallow (calling other scripts) so that the build scripts that I use to create the docker image are exactly available for someone who wants to build the environment on the host system.
Also, if the script needs to change, I find that I am far more likely to miss something if I need to change the script in multiple places.
This does have a drawback because if the build fails at a script, the entire script will need to be ran again.
I have found that the benefits outweigh the drawbacks on the projects that I have worked on.

My main reason for doing the dockerfile is so that I can test the scripts and commands I have documented for setting up the dev environment using a system without the dev tools already installed.


### Descriptions of cpp files I had before starting

Before I started this project, I had some c and c++ code that I wrote to help me understand the CSPICE toolkit.
I do not want to go into much detail about them because I am going to do a much more thorough job explaining everything related to this coding project.
Rather than deleting them, I put it in the `pre_src` directory.
If you are interested, you can `cd` into the `pre_src`directory and build the shared object libraries and binaries using the `mkcppprodct.csh`.


### Description of Data


The following kernels are loaded in the `gfoclt_c` example found [here](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/info/mostused.html#3)
```
furnsh_c( "naif0008.tls"  );
furnsh_c( "de421.bsp"     );
furnsh_c( "pck00008.tpc"  );
```

I need a lsk, a spk and a pck to use `gfoclt_c`.

The generic kernels can be downloaded manually [here](https://naif.jpl.nasa.gov/naif/data_generic.html).

At the time I am writing this, the [aareadme.txt](https://naif.jpl.nasa.gov/pub/naif/generic_kernels/lsk/aareadme.txt) says that `naif0012.tls` is the latest leap second kernel.

In [aareadme_de430-de431.txt](https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/planets/aareadme_de430-de431.txt) it says,

```
For those whose need of a planet ephemeris can be satisfied by the DE430 time span, and for
those in need of the most accurate JPL-produced lunar ephemeris, DE430 is now considered
the official export ephemeris.

  de430.bsp
  Approximate file size:   120 Mbytes
  Approximate time span:   1550 Jan 01 to 2650 Jan 22
```

So I think I need to use `de430.bsp` instead of `de421.bsp`.
I do not think that I need `de431.bsp` because I am not doing calculations deep in the past or deep into the future.

I am pretty sure I do not need the binary planetary constants for this calculation.
I see `pck00008.tpc` listed in the old_version directory and it looks like `pck00010.tpc` is the latest version.
I am going to presume that I need `pck00010.tpc`.

I made a script called `get_data.sh` that will download the data and put it in a folder.
You can run it with the following command.

```
chmod +x get_data.sh
./get_data.sh
```
