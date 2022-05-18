# An Documented Example Using cspice with C++

The objective of the code in this repository is to write a C++ program that determines times of solar occultations (the moon blocks the sun as seen from earth) in the period 2030 JAN 01 to 2040 JAN 01.
It Uses NAIF's C++11 "Coding Style and Standards" document (attached) and examples of NAIF's existing CSPICE routines as guides.

## Simplifying Assumption

Since I do not know where on Earth the observer is, I am going to assume that the observer is located at the center of the Earth and that the Earth somehow does not obstruct the observer from viewing the event for the occultation calculation.

## Approach

I will link the static libraries that cspice compiles and call them within c++ code.
In particular, I anticipate that I will use the `SPICE Geometry Finder (GF) Subsystem` [found here](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/Tutorials/pdf/individual_docs/29_geometry_finder.pdf).
To test my code, I will try it on a period of time in the past where I can look up historic solar occultations.

I am going to accomplish this task sequentially in the following steps:

1) Read the coding style standard found in the `SPICE2_Coding_Style_and_Standards_2022-02-17.md` file
1) Write a simple c program with hard coded inputs that uses the `SPICE Geometry Finder (GF) Subsystem`
1) Write a C++ class that handles the memory management

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
I do not track changes to these files with git because it makes the repository big when you track things like that.
It is better just to archive the binaries using an artifact registry or a just collection of compressed files.

You may also wish to install a nice text editor like `atom`, but that is optional.
I hear good things about `sublime` and `vscode` too.
Personally, I like the idea of using `vim`, `grep`, and `sed`.
On Ubuntu, you can install `atom` using snap with the following command.

```
sudo snap install atom --classic
```

I have a few scripts that will download `cspice` and some of the kernels needed for the program.
These scripts requires `wget`.
If you want to use my scripts, you will need to have `wget` installed.
If you do not already have `wget`, you can install it with the following line of code.

```
sudo apt-get install wget
```

Alternatively, you can just download the files from the [NAIF website](https://naif.jpl.nasa.gov/naif/).


## Download CSPICE from NAIF

I have already included `cspice` in this repository.
In retrospect, I probably should have git ignored this entire directory.
I made a script called `download_and_unzip_linux_64_cspice.sh` that will download and unzip CSPICE.
You can run the script with the following command.

```
chmod +x ./download_and_unzip_linux_64_cspice.sh
./download_and_unzip_linux_64_cspice.sh
```

You can also just download it from the NAIF site [here](https://naif.jpl.nasa.gov/naif/toolkit_C_PC_Linux_GCC_64bit.html)


### Build CSPICE

We will need to build the cspice static libraries before we can link them.
To do that you will need c-shell and the build essentials installed as I mentioned earlier.
If you have c-shell and gcc installed, then you should be able to the run the `./makall.csh` script from within the `cspice` directory after you give it execute permission.

If you open a terminal in the directory that this `README.md` file is located in, then you should be able to build cspice with the following command.

```
cd cspice
chmod +x makeall.csh
./makeall.csh
```

## Descriptions of cpp files I had before starting

Before I started this project, I had some c and c++ code that I wrote to help me understand the CSPICE toolkit.
I do not want to go into much detail about them because it is not really part of the assignment.
Rather than deleting them, I put it in the `pre_src` directory.
You can think of it as a scrap bin of code that I normally would not have included in the repository.
I have since added some other scrap c/c++ code here.

## Description of Data

To compute the occultation times, I will need to load an appropriate leap second kernel, an appropriate SPK to get the ephemeris state and positions of the planets, and a pck to get the planetary constants.
The generic kernels can be downloaded manually [here](https://naif.jpl.nasa.gov/naif/data_generic.html).

The following kernels are loaded in the `gfoclt_c` example found [here](https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/info/mostused.html#3)

```
furnsh_c( "naif0008.tls"  );
furnsh_c( "de421.bsp"     );
furnsh_c( "pck00008.tpc"  );
```

These do not appear to be the latest versions of the data kernels.

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

I made a script called `get_spice_data.sh` that will download the data and put it in a folder.
You can run it with the following command.

```
chmod +x get_spice_data.sh
./get_spice_data.sh
```

I also made a script to get the old spice data.
You can run it with the following command.

```
chmod +x get_spice_data.sh
./get_oldspice_data.sh
```

## Building the occfind program

I made a bash script called `build_cpp.sh` that will build `./bin/occfind` binary.
You can run from the same directory as this `README.md` file with the following command.

```
chmod +x build_cpp.sh
./build_cpp.sh
```

You should now have `./bin/occfind` compiled and ready to use.


## Description of occfind CLI

I made occfind into a command line interface with defaults that match the coding project inputs.
There is are detailed help description inside the program itself.
You can find that help description with the following command.

```
./bin/occfind --help
```

The default search path for the kernel files can be configured with environment variables.
This is to make it easy to install and update the program's data.
There are also various options to manually specify the kernel file locations, and to specify the search window.

The default settings are configured to run the describe programming task as if the input variables where hard coded.
So if you want times of solar occultations in the period 2030 JAN 01 to 2040 JAN 01, simply run the following command.

```
./bin/occfind
```

## Installing occfind command line interface locally without root by using environment variables

You can make the occfind command accessible upon startup by adding the following lines to your `~/.bashrc` file.

```
export SPICEDIR="/path/to/spice/directory"
export PATH="$SPICEDIR/bin:$PATH"
export OCCFIND_DATA_PATH="$SPICEDIR/data/"
export OCCFIND_LSK_BASENAME="naif0012.tls"
export OCCFIND_SPK_BASENAME="de430.bsp"
export OCCFIND_PCK_BASENAME="pck00010.tpc"
```

I have also made a script that you can call in the terminal to temporarily install it in the environment you are using.
All you need to do is run the following command.

```
source ./initialize_occfinder.sh
```

Replace `/path/to/spice/directory` with the absolute path to this directory.



## A Dockerfile for testing code

I have also included a Dockerfile that will create a testing environment that can be used for automated testing later.
Docker images like this are commonly used for CI/CD DEVOPS using Jenkins or Gitlab runners.

https://docs.docker.com/engine/install/ubuntu/

I like to keep my dockerfiles shallow (calling other scripts) so that the build scripts that I use to create the docker image are exactly available for someone who wants to build the environment on the host system.
Also, if the script needs to change, I find that I am far more likely to miss something if I need to change the scripts in multiple files.
This does have some drawbacks because if the build fails at a script, the entire script will need to be ran again.
I have found that the benefits outweigh the drawbacks on the projects that I have worked on.

My main reason for doing the dockerfile in this project is so that I can test the scripts and commands I have documented for setting up the dev environment using a system without the dev tools already installed.

The docker image can be built with the following command.

```
sudo docker build -t spice/occfind:latest .
```

Once the docker image has been built, an interactive terminal can be ran with the following command

```
sudo docker run -it --rm spice/occfind:latest bash
```

The actual cli command can also be ran with the following command.

```
sudo docker run -it --rm spice/occfind:latest ./bin/occfind
```

You can also pass in whatever optional arguments are supported by the CLI.

```
sudo docker run -it --rm spice/occfind:latest ./bin/occfind --help
```

## A quick test

Normally, I would have a set of test that I would run, but that is the part that takes to longest time.
I am going to settle with a less formal test for this project.

This project has brought back some great personal memories for me.

There was a total eclipse in North America on August 21, 2017.
My wife and I decided to settle for seeing a partial eclipse at home because we had a small child and the hotels were booked up everywhere.
We picked up a some special eye protection from the local library and made a viewer out of a cardboard box for our daughter to look through.
It was overcast in Panama City Beach, FL on that day.
My wife and I looked at the radar and noticed that we might be able to make it in time to a clear spot just north of I-10.
We buckled up our one year old daughter and drove north on highway 79 praying for a break in the clouds.
We pulled over to a gas station and viewed a partial eclipse from there.
I remember that the sun was high in the sky, so I imagine that the time was around noon.

A trucker noticed us looking at the eclipse and decided to pull over to see it.
He had a brown beer bottle that he was trying to view the eclipse from.
I explained to him that he needed special eye protection to view it and we shared our protective glasses with him so that he could see it without ruining his eyesight.
We also shared our cardboard viewer so that he could see it through the viewer as well.

Will my occfind program which leverages cspice's geometry finder be able to tell me the correct time?

To find out, type the following command:

```
./bin/occfind -b "2017 AUG 21" -e "2017 AUG 22"
```

```
The output is

Loading Kernel ./data/naif0012.tls
Loading Kernel ./data/de430.bsp
Loading Kernel ./data/pck00010.tpc
Searching for Occultations
Start Time (UTC):
	AUG 21,2017  00:00:00.0000
END Time (UTC):
	AUG 22,2017  00:00:00.0000

Results (UTC):
	AUG 21,2017  17:51:03.1466 - AUG 21,2017  19:00:00.4608
```

17:51:03.1466 UTC is 2017/08/22 01:50 PM, so that seems to be accurate with respect to what I recall.

## Result

```
Loading Kernel ./data/naif0012.tls
Loading Kernel ./data/de430.bsp
Loading Kernel ./data/pck00010.tpc
Searching for Occultations
Start Time (UTC):
	JAN 01,2030  00:00:00.0000
END Time (UTC):
	JAN 01,2040  00:00:00.0000

Results (UTC):
	JUN 01,2030  06:20:42.2582 - JUN 01,2030  06:35:24.6961
	NOV 25,2030  06:11:49.7772 - NOV 25,2030  07:29:05.1794
	MAY 21,2031  06:13:30.7355 - MAY 21,2031  08:16:20.8072
	NOV 14,2031  20:17:38.8633 - NOV 14,2031  21:55:02.5773
	MAR 20,2034  09:30:15.1732 - MAR 20,2034  11:04:55.8497
	SEP 12,2034  15:33:19.5171 - SEP 12,2034  17:03:18.9084
	MAR 09,2035  22:27:30.3650 - MAR 09,2035  23:41:56.6301
	SEP 02,2035  01:13:32.4942 - SEP 02,2035  02:37:43.2673
	JAN 05,2038  13:04:43.6032 - JAN 05,2038  14:27:21.6770
	JUL 02,2038  12:29:29.0582 - JUL 02,2038  14:34:00.7796
	DEC 26,2038  00:10:36.2953 - DEC 26,2038  01:47:25.7879
```

There is a list occultation listed [here](https://en.wikipedia.org/wiki/List_of_solar_eclipses_in_the_21st_century).

There are some times that are missing,

- May 9, 2032
- November 3, 2032
- March 30, 2033
- September 23, 2033
- February 27, 2036
- July 23, 2036
- August 21, 2036
- January 16, 2037
- July 13, 2037
- June 21, 2039
- December 15, 2039

But in the cases above no shadow would be cast where the Earth's center is.


## More Stuff

Assuming that the observer is in the center of the Earth was bothering me, so I made some changes to make it so that I could load ephemeris data for an earth station.
I figured out that to set DSS-14 as the observer, that I need to load
`data/earth_200101_990628_predict.bpc` and `earthstns_itrf93_201023.bsp`.

Then I made some additional options in the CLI so that I could pass that in.
The following command will compute occulations with DSS-14 as the observer.

```
./bin/occfind --set-observer "DSS-14" --extra-kernels data/earth_200101_990628_predict.bpc data/earthstns_itrf93_201023.bsp
```

The outputed result was

```
Loading Kernel ./data/naif0012.tls
Loading Kernel ./data/de430.bsp
Loading Kernel ./data/pck00010.tpc
Loading Kernel data/earth_200101_990628_predict.bpc
Loading Kernel data/earthstns_itrf93_201023.bsp
Observer: DSS-14
Searching for Occultations
Start Time (UTC):
	JAN 01,2030  00:00:00.0000
END Time (UTC):
	JAN 01,2040  00:00:00.0000

Results (UTC):
	JUN 01,2030  06:09:56.4747 - JUN 01,2030  07:35:20.2067
	NOV 14,2031  21:10:28.4327 - NOV 14,2031  22:08:50.5115
	MAR 30,2033  16:29:12.0038 - MAR 30,2033  18:25:07.6356
	MAR 20,2034  09:22:39.5816 - MAR 20,2034  10:23:50.7405
	SEP 02,2035  02:23:48.6839 - SEP 02,2035  03:28:11.4383
	JAN 05,2038  11:30:33.0279 - JAN 05,2038  13:18:38.7113
	JUN 21,2039  14:48:46.0807 - JUN 21,2039  16:41:56.0064
```

# occfind2

I made a second program (not a CLI) that computes solar occultation events.
It is called occfind2.
The main class is called Occultations2.
It uses the `spkezr_c` function from cspice.

The results from the program are listed below.

```
UN 01,2030  03:53:59.9990 JUN 01,2030  09:02:59.9990
NOV 25,2030  04:33:00.0009 NOV 25,2030  09:09:00.0009
MAY 21,2031  04:32:59.9987 MAY 21,2031  09:59:59.9987
NOV 14,2031  18:39:00.0011 NOV 14,2031  23:33:00.0011
MAY 09,2032  11:29:59.9985 MAY 09,2032  15:20:59.9985
NOV 03,2032  03:48:00.0013 NOV 03,2032  07:21:00.0013
MAR 30,2033  16:20:59.9982 MAR 30,2033  19:44:59.9982
SEP 23,2033  12:15:00.0015 SEP 23,2033  15:33:00.0015
MAR 20,2034  07:56:59.9983 MAR 20,2034  12:38:59.9983
SEP 12,2034  13:45:00.0014 SEP 12,2034  18:54:00.0014
MAR 09,2035  20:38:59.9984 MAR 10,2035  01:32:59.9984
SEP 01,2035  23:33:00.0013 SEP 02,2035  04:21:00.0013
FEB 27,2036  03:14:59.9985 FEB 27,2036  06:17:59.9985
AUG 21,2036  15:57:00.0011 AUG 21,2036  18:54:00.0011
JAN 16,2037  08:08:59.9995 JAN 16,2037  11:29:59.9995
JUL 13,2037  00:33:00.0001 JUL 13,2037  04:45:00.0001
JAN 05,2038  11:17:59.9998 JAN 05,2038  16:17:59.9998
JUL 02,2038  10:53:59.9998 JUL 02,2038  16:11:59.9998
DEC 25,2038  22:36:00.0001 DEC 26,2038  03:24:00.0001
JUN 21,2039  14:56:59.9995 JUN 21,2039  19:26:59.9995
DEC 15,2039  14:39:00.0004 DEC 15,2039  18:09:00.0004
```

It misses one small solar occultation event near the south pole on July 23, 2036.
I think it missing this one because I use hard coded planetary constants that I got off of the internet, which may not be particularly accurate.

An algorithm description can be found in `occfind2.pdf`.
