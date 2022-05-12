#! /bin/bash

mkdir data
cd data
wget https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/stations/earthstns_itrf93_201023.bsp
wget https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/stations/earthstns_itrf93_201023.cmt
cd ..
