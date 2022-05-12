#! /bin/bash

mkdir oldspicedata
cd oldspicedata
wget https://naif.jpl.nasa.gov/pub/naif/generic_kernels/lsk/a_old_versions/naif0008.tls
wget https://naif.jpl.nasa.gov/pub/naif/generic_kernels/spk/planets/a_old_versions/de421.bsp
wget https://naif.jpl.nasa.gov/pub/naif/generic_kernels/pck/a_old_versions/pck00008.tpc
cd ..
