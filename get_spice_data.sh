#! /bin/bash

mkdir data
cd data
wget https://naif.jpl.nasa.gov/pub/naif/generic_kernels/lsk/naif0012.tls
wget https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/planets/de430.bsp
wget https://naif.jpl.nasa.gov/pub/naif/generic_kernels/pck/pck00010.tpc
cd ..
