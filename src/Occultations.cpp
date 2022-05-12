/**
// SPICE2 Version 0.0.0, 10-May-2022 (MMR)
*/

#include "Occultations.hpp"
#include <iostream>
#include <cassert>
#include <string>

spice::Occultations::Occultations(std::string filenameLSK, std::string filenameSPK,
  std::string filenamePCK )
{
  // load the leap second kernel
  std::cout << "Loading Kernel " << filenameLSK << std::endl;
  furnsh_c( filenameLSK.c_str() );
  std::cout << "Loading Kernel " << filenameSPK << std::endl;
  // load the ephemeris data
  furnsh_c( filenameSPK.c_str() );
  // load the planetary constants data
  std::cout << "Loading Kernel " << filenamePCK << std::endl;
  furnsh_c( filenamePCK.c_str() );
  // set the default TimeStepSize to 3 minute intervals
  SetTimeStepSize( 180.0);
  m_timeBin=3153600000.0; // about one hundred years years
  // Set the default time string format
  m_timeFormat="MON DD,YYYY  HR:MN:SC.####  ::UTC";
  // initialize the last result for keeping track of split eclipses
  m_lastResult=-1.0e100;
  //
  m_occultationType="ANY";
  m_front="MOON";
  m_back="SUN";
  m_observer="EARTH";
}

spice::Occultations::~Occultations(){
  /*
  Clear the KEEPER subsystem: unload all kernels, clear the kernel
  pool, and re-initialize the subsystem. Existing watches on kernel
  variables are retained.*/
  kclear_c();
}

void spice::Occultations::SetTimeWindow( std::string startDateTimel, std::string endDateTime )
{
  // convert the start time to ephemeris time value
  str2et_c ( startDateTimel.c_str(), &m_epemerisTimeSearchWindowStart );
  // convert the end time to ephemeris time value
  str2et_c ( endDateTime.c_str(), &m_desiredEpemerisTimeSearchWindowEnd );
  // check to see if we need to bin up the time interval
  SpiceDouble timeLength=m_desiredEpemerisTimeSearchWindowEnd-m_epemerisTimeSearchWindowStart;
  if (timeLength>m_timeBin)
  {
    // need to break up the search into smaller time bins
    m_epemerisTimeSearchWindowEnd=m_epemerisTimeSearchWindowStart+m_timeBin;
  }
  else
  {
    // we do not need to bin up the time interval
    m_epemerisTimeSearchWindowEnd=m_desiredEpemerisTimeSearchWindowEnd;
  }
}


void spice::Occultations::ClearResults(){
  m_resultStartTimeInterval.clear();
  m_resultEndTimeInterval.clear();
}

int spice::Occultations::ComputeNextOccultation(){
  const int MAXIMUM_WINDOWS=500;
  // create SPICE window to which the search is restricted.
  SPICEDOUBLE_CELL      ( cnfine, MAXIMUM_WINDOWS );
  SPICEDOUBLE_CELL      ( dvswin, MAXIMUM_WINDOWS );
  SPICEDOUBLE_CELL      ( result, MAXIMUM_WINDOWS );
  wninsd_c ( m_epemerisTimeSearchWindowStart, m_epemerisTimeSearchWindowEnd, &cnfine );

  // run the spice geometry finder
  gfoclt_c ( m_occultationType.c_str(),
             m_front.c_str(), "ELLIPSOID",  "IAU_MOON",
             m_back.c_str(),  "ELLIPSOID",  "IAU_SUN",
             "LT",
             m_observer.c_str(),
             m_timeStepSize,
             &cnfine,   &result                 );
  // Compute the difference between the original search window and the result window.
  // create a placeholder to store the difference

  //   wndifd_c places the difference of two double precision windows into a third window.
  wndifd_c ( &cnfine, &result , &dvswin );
  // Find out how many results we found
  /*
    The function wncard_c returns the number of intervals
    in a SPICE window.
  */
  SpiceInt resultsFound = wncard_c( &result  ); // how many results were found

  if ( resultsFound == 0 )
  {
    // No events were found
  }
  else
  {
    /*
    Because I bin up the time interval, I need to make sure it isn't binned in the middle of a lunar eclipse.
    To accomplish this I will compare the end of the previous interval to the start of this current interval
    */
    for ( SpiceInt ii = 0; ii < resultsFound ; ii++ )
    {
      SpiceDouble startET;
      SpiceDouble finishET;
      // retrieve the start and end ephemeris time
      wnfetd_c ( &result, ii, &startET, &finishET );
      if (std::abs(startET-m_lastResult)<86400.0)// same day
      {
        // In this case the start time for this result overlaps the time period for the previous result
        // This can happen if the break point occurs in the middle of an ecplise.
        // All we need to do is update the last interval
        m_resultEndTimeInterval[ m_resultEndTimeInterval.size()-1 ] = finishET;
      }
      else
      {
        m_resultStartTimeInterval.push_back( startET );
        m_resultEndTimeInterval.push_back( finishET );
        m_lastResult = finishET;
      }
    }

  }
  int completionStatus=0; // zero means the entire desired search window has been searched
  if (m_epemerisTimeSearchWindowEnd<m_desiredEpemerisTimeSearchWindowEnd)
  {
    // update to the next time block
    m_epemerisTimeSearchWindowStart=m_epemerisTimeSearchWindowEnd;
    m_epemerisTimeSearchWindowEnd=std::min(m_desiredEpemerisTimeSearchWindowEnd,m_epemerisTimeSearchWindowEnd+m_timeBin);
    completionStatus=1; // one means there is another block to search
  }
  // clear the results
  wndifd_c ( &cnfine, &cnfine,&result);
  wndifd_c ( &cnfine, &cnfine,&dvswin );
  wndifd_c ( &dvswin, &dvswin,&cnfine );
  // is there are way to clear out the data?
  // is there a need to clear out the data?
  // I can clear out the whole pool, but I don't want to do that.
  return completionStatus;
}



void spice::Occultations::ComputeOccultations(){
  do {
    // convert the ephemeris time to strings
    SpiceChar startUTC [m_NUMBER_OF_DATE_CHARACTERS];
    SpiceChar finishUTC [m_NUMBER_OF_DATE_CHARACTERS];
    timout_c ( m_epemerisTimeSearchWindowStart,  m_timeFormat.c_str(), m_NUMBER_OF_DATE_CHARACTERS, startUTC);
    timout_c ( m_epemerisTimeSearchWindowEnd, m_timeFormat.c_str(), m_NUMBER_OF_DATE_CHARACTERS, finishUTC);

    // print out search band
    std::cout << "Searching for Occultations" << std::endl;
    std::cout << "Start Time (UTC):\n\t" << startUTC << std::endl;
    std::cout << "END Time (UTC):\n\t" << finishUTC << std::endl<< std::endl;
  } while ( ComputeNextOccultation() ==1 );
}

void spice::Occultations::PrintTimes()
{

  std::cout << "Results (UTC):" << std::endl;

  assert( m_resultStartTimeInterval.size() ==   m_resultEndTimeInterval.size() && " The size of the two time result vectors must be equal.");
  for ( int ii = 0; ii < m_resultStartTimeInterval.size(); ii++)
  {
    // convert the ephemeris time to strings
    SpiceChar startUTC [m_NUMBER_OF_DATE_CHARACTERS];
    SpiceChar finishUTC [m_NUMBER_OF_DATE_CHARACTERS];
    timout_c ( m_resultStartTimeInterval[ii],  m_timeFormat.c_str(), m_NUMBER_OF_DATE_CHARACTERS, startUTC);
    timout_c ( m_resultEndTimeInterval[ii], m_timeFormat.c_str(), m_NUMBER_OF_DATE_CHARACTERS, finishUTC);

    // print out the event
    std::cout <<"\t"<< startUTC << " - " << finishUTC << std::endl;
  }


}
