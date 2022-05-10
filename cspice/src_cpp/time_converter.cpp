/**
* @file time_converter.cpp
* @brief Converting between UTC and Ephemeris Time (LSK)
*
* Michael M. Rosenthal
*/

#include <stdio.h>
#include "SpiceUsr.h"
#include <vector>
#include <string>




void Time_Converter::load_leap_second_kernel(std::string lsk_file){
  furnsh_c  ( lsk_file.c_str() );
}
void Time_Converter::set_utc(std::string utc_input){
  str2et_c  ( utc_input.c_str(), &et );
}

void Time_Converter::set_et(SpiceDouble et_input){
  et = et_input;
  timout_c ( et, "YYYY-DOYTHR:MN:SC.### ::RND", utc.size(), &utc[0] );
}
