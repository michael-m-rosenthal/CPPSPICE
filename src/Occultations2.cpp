/**
// SPICE2 Version 0.0.0, 10-May-2022 (MMR)
*/

#include "Occultations2.hpp"

#include <iostream>
#include <iomanip>      // std::setprecision
#include <cmath>
#include <algorithm>

#include "SpiceUsr.h"
#include "lowLevel.hpp"

spice::Occultations2::Occultations2( std::string filenameLSK , std::string filenameSPK , std::string filenamePCK )
{
  // load the leap second kernel
  LoadKernel( filenameLSK );
  // load the ephemeris data
  LoadKernel( filenameSPK );
  // load the planetary constants data
  LoadKernel( filenamePCK );
  //
  m_frame="J2000";
  SetObserver("Earth");
  SetFront("MOON");
  SetBack("SUN");
  m_stepSizeET=180.0;
  m_halfFrontRevolution = 26.0*24.0*60.0*60.0/2.0; // slightly less than half the time it takes the front to revolve around the earth.
  // Set the default time string format
  m_timeFormat="MON DD,YYYY  HR:MN:SC.####  ::UTC";
  // truncated cone parameters
  m_radiusA=m_observerRadius+m_frontRadius/2.0;
  m_radiusB=m_backRadius+m_frontRadius/2.0;
  m_currentNormal.resize(3);
}


spice::Occultations2::~Occultations2(){
  /*
  Clear the KEEPER subsystem: unload all kernels, clear the kernel
  pool, and re-initialize the subsystem. Existing watches on kernel
  variables are retained.*/
  kclear_c();
}


void spice::Occultations2::LoadKernel( std::string filename )
{
  std::cout << "Loading Kernel " << filename << std::endl;
  furnsh_c( filename.c_str() );
}

void spice::Occultations2::SetObserver(std::string object){
  std::vector<double> values(3);
  SpiceInt dim;
  bodvrd_c ( object.c_str(), "RADII", 3, &dim, &values[0] );
  m_observer=object;
  m_observerRadius = *std::max_element(values.begin(),values.end());
}

void spice::Occultations2::SetFront(std::string object){
  std::vector<double> values(3);
  SpiceInt dim;
  bodvrd_c ( object.c_str(), "RADII", 3, &dim, &values[0] );
  m_front=object;
  m_frontRadius = *std::max_element(values.begin(),values.end());
}

void spice::Occultations2::SetBack(std::string object){
  std::vector<double> values(3);
  SpiceInt dim;
  bodvrd_c ( object.c_str(), "RADII", 3, &dim, &values[0] );
  m_back=object;
  m_backRadius = *std::max_element(values.begin(),values.end());
}

void spice::Occultations2::SetstepSizeET( double stepSizeET )
{
  m_stepSizeET = stepSizeET;
}

void spice::Occultations2::SetFrame( std::string frame )
{
  m_frame = frame;
}

void spice::Occultations2::SetTimeWindow( std::string startDateTime, std::string endDateTime )
{
  // convert the start time to ephemeris time value
  str2et_c ( startDateTime.c_str(), & m_startET);
  // convert the end time to ephemeris time value
  str2et_c ( endDateTime.c_str(), & m_endET );
}

void spice::Occultations2::GetState( std::string target, std::string observer, std::vector<double> &position, std::vector<double> &velocity ){
  std::string aberrationCorrection="NONE";
  SpiceDouble lightTime;
  SpiceDouble state [6];
  spkezr_c ( target.c_str(),    m_currentET,     m_frame.c_str(),
            aberrationCorrection.c_str(), observer.c_str(),
            state, &lightTime );
  position.resize(3);
  for (int ii = 0; ii < 3; ii++)
  {
    position[ii] = state[ii];
  }
  velocity.resize(3);
  for (int ii = 0; ii < 3; ii++)
  {
    velocity[ii] = state[ii+3];
  }
}



double spice::Occultations2::CurrentFrontDotBack()
{
  GetState( m_front.c_str(), m_observer.c_str(), m_toFront, m_frontVelocity);
  GetState( m_back.c_str(), m_observer.c_str(), m_toBack, m_backVelocity );
  return dotProduct(m_toBack,m_toFront);
}

void spice::Occultations2::RunSearch()
{
  m_currentET = m_startET;
  int countConsecutiveNegativeDots = 0;
  int countConsecutiveWithinCone = 0;
  while ( m_currentET < m_endET ) {
    if ( CurrentFrontDotBack()> 0 ){
      // the front is in front of the plane where it may pass in front of the observer.
      // now we need to make some additional computations.

      countConsecutiveNegativeDots = 0;
      // compute the unit normal
      std::vector<double> normal = m_toBack;
      double distance = normalize( normal );
      double dot = dotProduct( normal , m_toFront );
      double coneRadius=linearInterp(0.0, distance, m_radiusA, m_radiusB, dot);
      // project the front location to the nearest point on the line connecting observer and back
      double planeDistance = frobenius3(  m_toFront[0] - dot*normal[0], m_toFront[1] - dot*normal[1] , m_toFront[2] - dot*normal[2] );
      if ( planeDistance < coneRadius ){

        // the front object is obstructing the view.
        if ( countConsecutiveWithinCone  > 1 ){
            resultET[ resultET.size() - 1 ] = m_currentET;
        } else {
          resultET.push_back(m_currentET);
        }
        countConsecutiveWithinCone  ++;
      }
      else
      {
        countConsecutiveWithinCone  = 0;
      }
    } else {
      if (countConsecutiveNegativeDots == 0){
        // make one big leap in time equal to about half a month
        m_currentET += m_halfFrontRevolution;
      }
      countConsecutiveNegativeDots ++;
    }
    // check if the front
    m_currentET += m_stepSizeET;
  }
}

void spice::Occultations2::PrintResults()
{
  for ( int ii = 0; ii < resultET.size(); ii ++){
    SpiceChar dateUTC [50];
    timout_c ( resultET[ii],  m_timeFormat.c_str(), 50, dateUTC);
    std::cout << dateUTC;
    if ( (ii % 2) == 0){
      std::cout << " ";
    } else {
      std::cout << std::endl;
    }

  }

}
