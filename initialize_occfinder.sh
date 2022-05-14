#! /bin/bash

export SPICEDIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
export PATH="$SPICEDIR/bin:$PATH"
export OCCFIND_DATA_PATH="$SPICEDIR/data/"
export OCCFIND_LSK_BASENAME="naif0012.tls"
export OCCFIND_SPK_BASENAME="de430.bsp"
export OCCFIND_PCK_BASENAME="pck00010.tpc"
