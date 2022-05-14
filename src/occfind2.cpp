/**

*/

#include "Occultations2.hpp"
#include <string>
#include <cstdlib>
#include <iostream>


int main(int argc, char *argv[]){
  std::string OCCFIND_DATA_PATH = "./data/"; // default
  if ( const char* env_p = std::getenv("OCCFIND_DATA_PATH") )
  {
    OCCFIND_DATA_PATH = env_p;
  }

  std::string OCCFIND_LSK_BASENAME;
  if ( const char* env_p = getenv ("OCCFIND_LSK_BASENAME") )
  {
    OCCFIND_LSK_BASENAME = env_p;
  }
  else
  {
    OCCFIND_LSK_BASENAME = "naif0012.tls"; // default
  }

  std::string OCCFIND_SPK_BASENAME;
  if ( const char* env_p = getenv ("OCCFIND_SPK_BASENAME") )
  {
    OCCFIND_SPK_BASENAME = env_p;
  }
  else
  {
    OCCFIND_SPK_BASENAME = "de430.bsp"; // default
  }

  std::string OCCFIND_PCK_BASENAME;
  if ( const char* env_p = getenv ("OCCFIND_PCK_BASENAME") )
  {
    OCCFIND_PCK_BASENAME = env_p;
  }
  else
  {
    OCCFIND_PCK_BASENAME = "pck00010.tpc"; // default
  }

  //////////////////////////////////////////////////////////////////////////////
  // set the default file paths using the configuration environment variables
  // By the way, if you want to use c++17, there are implementations to append file path safely
  std::string FilenameLSK = OCCFIND_DATA_PATH + OCCFIND_LSK_BASENAME;
  std::string FilenameSPK = OCCFIND_DATA_PATH + OCCFIND_SPK_BASENAME ;
  std::string FilenamePCK = OCCFIND_DATA_PATH + OCCFIND_PCK_BASENAME;

  std::string startDateTime="2030 JAN 01";
  std::string endDateTime="2040 JAN 01";

  spice::Occultations2 Occultations2( FilenameLSK , FilenameSPK , FilenamePCK );
  Occultations2.SetTimeWindow( startDateTime, endDateTime );

  Occultations2.RunSearch();
  Occultations2.PrintResults();
  return 0;
}
