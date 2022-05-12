/**

example taken from https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/info/mostused.html

The following example determines time intervals in December, 2001
when the Sun is occulted by the Moon (solar eclipses) as seen from
the center of the Earth, with both Sun and Moon modeled as
ellipsoids
*/

#include "Occultations.hpp"
#include <string>


int main (){

  SPICEDOUBLE_CELL      ( cnfine, 200 );
  SPICEDOUBLE_CELL      ( dvswin, 200 );
  SPICEDOUBLE_CELL      ( result, 200 );
  // input data files needed for calculating occultations
  std::string FilenameLSK = "data/naif0012.tls";
  std::string FilenameSPK = "data/de430.bsp";
  std::string FilenamePCK = "data/pck00010.tpc";
  spice::Occultations occultations(FilenameLSK,FilenameSPK,FilenamePCK);

  // input time window contraints
  std::string startDateTimel="2002 DEC 04";
  std::string endDateTime="2002 DEC 05";
  occultations.SetTimeWindow(startDateTimel,endDateTime);

  // Set search parameters. Select a 3-minute step.
  double TimeStepSize=180.0;
  occultations.SetTimeStepSize(TimeStepSize);

  //
  occultations.ComputeOccultations();
  occultations.PrintTimes();
}
