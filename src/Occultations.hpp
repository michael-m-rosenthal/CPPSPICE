/**
// SPICE2 Version 0.0.0, 10-May-2022 (MMR)
*/

#ifndef OCCULTATIONS_H_
#define OCCULTATIONS_H_

#include "SpiceUsr.h"
#include <vector>
#include <string>


namespace spice
{
  /**
  * \brief A c++ class for computing times of solar occultations (the moon blocks the sun as seen from earth)
  */
  class Occultations
  {
    private:
      SpiceDouble m_timeStepSize;/**< \brief seconds binning up the occultation search */
      SpiceDouble m_epemerisTimeSearchWindowStart;
      SpiceDouble m_epemerisTimeSearchWindowEnd;
      SpiceDouble m_desiredEpemerisTimeSearchWindowEnd;
      SpiceDouble m_timeBin;

      std::string m_timeFormat;
      std::string m_occultationType;
      std::string m_front;
      std::string m_back;
      std::string m_observer;
      // main output
      std::vector<SpiceDouble> m_resultStartTimeInterval;
      std::vector<SpiceDouble> m_resultEndTimeInterval;

      //
      const int m_NUMBER_OF_DATE_CHARACTERS=51;

      //
      SpiceDouble m_lastResult;/**< \brief keep track of this so I can tell if I break in the middle of a solar eclipse */
    public:
      /**
      * \brief initialize the occultation calculation class
      *
      * You need to include paths to files that have the relevent the leap seconds data, empheris data, and planetary constants.
      */
      Occultations(
              std::string filenameLSK,  /**< \brief file path for the leap second kernel*/
              std::string filenameSPK,  /**< \brief file path for the planetary ephemeris data kernel*/
              std::string filenamePCK   /**< \brief file path for the planetary constant data kernel*/
            );
      /**
      * \brief initialize the occultation calculation class
      *
      */
      void SetTimeWindow(std::string startDateTimel,std::string endDateTime);

      /**
      * \brief setter method for specifying the time set bin interval
      *
      */
      void SetTimeStepSize(
        double timeStepSize /**< \brief search bin width in seconds*/
      ){
        m_timeStepSize=timeStepSize;
      }

      void ClearResults();

      /**
      * \brief Computes the next block of Occultation in the binned time interval
      *
      * The total time interval is broken up into smaller bins to get around the static memory issue that cspice has.
      * This function will return a 1 if there is another time block to compute and a 0 if there are no more time blocks.
      */
      int ComputeNextOccultation();

      /**
      * \brief Computes all Occultation time periods in the desired range
      *
      */
      void ComputeOccultations();

      void PrintTimes();
  };
}
#endif  // OCCULTATIONS_H_
