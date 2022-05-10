#!/bin/csh


# download the compressed tar from the NAIF site
wget https://naif.jpl.nasa.gov/pub/naif/toolkit//C/PC_Linux_GCC_64bit/packages/cspice.tar.Z .

# download the scritp that the NAIF site provides to unzip it
wget https://naif.jpl.nasa.gov/pub/naif/toolkit//C/PC_Linux_GCC_64bit/packages/importCSpice.csh .

# add execute permission for the decompression script
chmod +x ./importCSpice.csh

# run the decompression script
./importCSpice.csh
