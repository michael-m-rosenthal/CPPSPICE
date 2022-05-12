/**

*/

#include "Occultations.hpp"
#include "occfindHelpPrint.hpp"
#include <string>
#include <cstdlib>



int main(int argc, char *argv[]){
  //////////////////////////////////////////////////////////////////////////////
  /* Get occfind configuration Environment Variables

  OCCFIND_DATA_PATH
  OCCFIND_LSK_BASENAME
  OCCFIND_SPK_BASENAME
  OCCFIND_PCK_BASENAME

  This will make it easier to make this an application that can be installed or configured on a unix-like system.
  All you would need to do is
  1) put the binaries in a common place (like /bin)
  2) put the data files in a common place (like /ect/spice)
  3) set the OCCFIND_DATA_PATH, OCCFIND_LSK_BASENAME, OCCFIND_SPK_BASENAME, and OCCFIND_PCK_BASENAME
  */
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

  // input default time window contraints
  std::string startDateTime="2030 JAN 01";
  std::string endDateTime="2040 JAN 01";

  // input default cspice search bin interval
  double timeStepSize=180.0; // 3 minutes

  //////////////////////////////////////////////////////////////////////////////
  // Read CLI arguments and modify default inputs
  for ( int ii = 0; ii < argc; ii++ )
  {
    std::string currentArgument = argv[ii];// convert to c++ string so that I can use c++ string comparison
    if ((currentArgument=="--help") | (currentArgument=="-h"))
    {
      spice::PrintHelp();
      return 0;
    }
    if ((currentArgument=="--lsk") | (currentArgument=="-l"))
    {
      ii +=1;
      FilenameLSK=argv[ii];
    }
    if ((currentArgument=="--spk") | (currentArgument=="-s"))
    {
      ii +=1;
      FilenameSPK=argv[ii];
    }
    if ((currentArgument=="--pck") | (currentArgument=="-p"))
    {
      ii +=1;
      FilenamePCK=argv[ii];
    }
    if ((currentArgument=="--begin") | (currentArgument=="-b"))
    {
      ii +=1;
      startDateTime=argv[ii];
    }
    if ((currentArgument=="--end") | (currentArgument=="-e"))
    {
      ii +=1;
      endDateTime=argv[ii];
    }
    if ((currentArgument=="--step"))
    {
      ii +=1;
      timeStepSize=std::atof(argv[ii]);
    }
  }

  //////////////////////////////////////////////////////////////////////////////
  // Initialize object and run the computation
  // load kernels
  spice::Occultations occultations(FilenameLSK,FilenameSPK,FilenamePCK);
  // set search window
  occultations.SetTimeWindow(startDateTime,endDateTime);
  // set the step size
  occultations.SetTimeStepSize(timeStepSize);
  // Run the Search
  occultations.ComputeOccultations();
  // Print the Results
  occultations.PrintTimes();
  return 0;
}
