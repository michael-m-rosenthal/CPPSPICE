/**
// SPICE2 Version 0.0.0, 10-May-2022 (MMR)
*/

#ifndef OCCFINDHELPPRINT_H_
#define OCCFINDHELPPRINT_H_


#include <string>
#include <iostream>


namespace spice
{
  /**
  * \brief Put the CLI help out put here.
  */
  std::string lineBorder(80, '-');
  void PrintHelp(){
    // print title bar
    std::cout << lineBorder << std::endl;
    std::cout << "occfind2 CLI" << std::endl;
    std::cout << lineBorder << std::endl;
    // print brief description
    std::cout << "occfind2 locates solar occultations (the moon blocks the sun as seen from earth)." << std::endl<< std::endl;
    std::cout << std::endl;
    std::cout << lineBorder << std::endl;
    // describe how the function is called
    std::cout << "Usage:  occfind2 [OPTION]"<< std::endl;
    std::cout << lineBorder << std::endl;
    // describe options
    std::cout << "Options:  "<< std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "--help -h";
    std::cout << "\n\t\t";
    std::cout << "Print help for using the occfind2 CLI";
    std::cout   << std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "--lsk -l ";
    std::cout << "\n\t\t";
    std::cout << "Specify the path of the spice leap second kernel data file.";
    std::cout << "\n\n\t\t";
    std::cout << "[DEFAULT] $OCCFIND_DATA_PATH/data/naif0012.tls";
    std::cout   << std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "--spk -s ";
    std::cout << "\n\t\t";
    std::cout << "Specify the path of the spice planetary ephemeris data file.";
    std::cout << "\n\n\t\t";
    std::cout << "[DEFAULT] $OCCFIND_DATA_PATH/data/de430.bsp";
    std::cout   << std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "--pck -p ";
    std::cout << "\n\t\t";
    std::cout << "Specify the path of the spice planetary constants data file.";
    std::cout << "\n\n\t\t";
    std::cout << "[DEFAULT] $OCCFIND_DATA_PATH/data/pck00010.tpc";
    std::cout   << std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "--begin -b ";
    std::cout << "\n\t\t";
    std::cout << "Specify the starting date string for the search window";
    std::cout << "\n\n\t\t";
    std::cout << "[DEFAULT] \"2030 JAN 01\"";
    std::cout   << std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "--end -e ";
    std::cout << "\n\t\t";
    std::cout << "Specify the ending date string for the search window";
    std::cout << "\n\n\t\t";
    std::cout << "[DEFAULT] \"2040 JAN 01\"";
    std::cout   << std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "--step ";
    std::cout << "\n\t\t";
    std::cout << "Specify bin time step size (in seconds) for the spice search";
    std::cout << "\n\n\t\t";
    std::cout << "[DEFAULT] 180.0";
    std::cout   << std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "--set-observer ";
    std::cout << "\n\t\t";
    std::cout << "Choose another observer such as MARS or DSS-14";
    std::cout << "\n\n\t\t";
    std::cout << "[DEFAULT] EARTH";
    std::cout   << std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "--extra-kernels ";
    std::cout << "\n\t\t";
    std::cout << "Load extra kernels needed for the observer";
    std::cout << "\n\t\t";
    std::cout << "You can specify more than one file, but do not try to add any other argument after this or you will get and error.";
    std::cout << "After you use the --extra-kernels option, all other arguments must be paths to kernels";
    std::cout << "\n\n\t\t";
    std::cout << "[DEFAULT] ";
    std::cout   << std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << lineBorder << std::endl;
    std::cout << "Configuration Environment Variables:  "<< std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "OCCFIND_DATA_PATH  "<< std::endl;
    std::cout << "\n\t\t";
    std::cout << "The user can configure where occ will look for the spice data kernel files";
    std::cout << "\n\n\t\t";
    std::cout << "If OCCFIND_DATA_PATH is empty, then occfind2 assumes OCCFIND_DATA_PATH=./data/";
    std::cout << std::endl<< std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "OCCFIND_LSK_BASENAME"<< std::endl;
    std::cout << "\n\t\t";
    std::cout << "The user can configure the basename for the spice leap second kernel data";
    std::cout << "\n\n\t\t";
    std::cout << "[DEFAULT] naif0012.tls";
    std::cout << std::endl<< std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "OCCFIND_SPK_BASENAME"<< std::endl;
    std::cout << "\n\t\t";
    std::cout << "The user can configure the basename for the spice planetary ephemeris kernel data";
    std::cout << "\n\n\t\t";
    std::cout << "[DEFAULT] naif0012.tls";
    std::cout << std::endl<< std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\t";
    std::cout << "OCCFIND_PCK_BASENAME"<< std::endl;
    std::cout << "\n\t\t";
    std::cout << "The user can configure the basename for the spice planetary constant kernel data";
    std::cout << "\n\n\t\t";
    std::cout << "[DEFAULT] naif0012.tls";
    std::cout << std::endl<< std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << lineBorder << std::endl;
    std::cout << "Examples:  "<< std::endl;
    ////////////////////////////////////////////////////////////////////////////
      std::cout << "\n\n\tExample Usage: \n\t";
    std::cout << "occfind2  "<< std::endl;
    std::cout << "\n\t\t";
    std::cout << "First will load the following spice kernel files\n";
    std::cout << "\t\t\t./data/naif0012.tls\n";
    std::cout << "\t\t\t./data/de430.bsp\n";
    std::cout << "\t\t\t./data/pck00010.tpc\n";
    std::cout << "\n\t\t";
    std::cout << "Then it will find solar occultations between \"2030 JAN 01\" and \"2040 JAN 01\"\n";
    std::cout << std::endl;
    ////////////////////////////////////////////////////////////////////////////
      std::cout << "\n\n\tExample Usage: \n\t";
    std::cout << "occfind2 -b \"2017 AUG 21\" -e \"2017 AUG 22\" "<< std::endl;
    std::cout << "\n\t\t";
    std::cout << "This will find solar occultations between  \"2017 AUG 21\" and  \"2017 AUG 22\"";
    std::cout << std::endl;
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\n\n\tExample Usage: \n\t";
    std::cout << "occfind2  -l ~/oldspicedata/naif0008.tls -s ~/oldspicedata/de421.bsp -p ~/oldspicedata/pck00008.tpc"<< std::endl;
    std::cout << "\n\t\t";
    std::cout << "This will allow you to manually load alternative kernels";
    std::cout << std::endl;
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    std::cout << "\n\n\tExample Usage: \n\t";
    std::cout << "./bin/occfind2 --set-observer \"DSS-14\" --extra-kernels data/earth_200101_990628_predict.bpc data/earthstns_itrf93_201023.bsp "<< std::endl;
    std::cout << "\n\t\t";
    std::cout << "This will compute occultations with respect to Earth Station DSS-14";
    std::cout << std::endl;
    std::cout << lineBorder << std::endl;
  }
}
#endif  // OCCFINDHELPPRINT_H_
