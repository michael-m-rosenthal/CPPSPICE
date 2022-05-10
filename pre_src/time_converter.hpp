/**
* @file time_converter.hpp
* @brief Converting between UTC and Ephemeris Time (LSK)
*
* Michael M. Rosenthal
*/

#ifndef TIME_CONVERTER_H_
#define TIME_CONVERTER_H_

#include <stdio.h>
#include "SpiceUsr.h"
#include <vector>
#include <string>



class Time_Converter{
  private:
    SpiceDouble   et;
    std::vector<SpiceChar> utc;
  public:
    Time_Converter(){
      utc.resize(32);
    };
    ~Time_Converter(){
      utc.clear();
    };
    /**
         \brief load LSK file
    */
    void load_leap_second_kernel(std::string lsk_file);
    /**
         \brief convert UTC to ET
    */
    void set_utc(std::string utc_input);
    /**
         \brief convert UTC to ET
    */
    void set_et(SpiceDouble et_input);
}
