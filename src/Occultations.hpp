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
      // Primary inputs
      SpiceDouble m_epemerisTimeSearchWindowStart;/**< \brief current start time window in et */
      SpiceDouble m_epemerisTimeSearchWindowEnd; /**< \brief current end time window in et */
      SpiceDouble m_desiredEpemerisTimeSearchWindowEnd; /**< \brief goal end time window in et */
      // configuration inputs
      SpiceDouble m_timeBin;  /**< \brief how are you going to break up the total interval? */
      std::string m_timeFormat;  /**< \brief a string that tells cspice how to translate ET to a date string */
      std::string m_occultationType; /**< \brief occtyp input for gfoclt_c */
      std::string m_front; /**< \brief front input for gfoclt_c */
      std::string m_back; /**< \brief back input for gfoclt_c */
      std::string m_observer; /**< \brief obsrvr input for gfoclt_c */
      SpiceDouble m_timeStepSize;
      /**< \brief step input for gfoclt_c
      *
      * Seconds binning up the occultation search.
      */
      // main output
      std::vector<SpiceDouble> m_resultStartTimeInterval; /**< \brief Stored ET Start times for occultation events*/
      std::vector<SpiceDouble> m_resultEndTimeInterval;/**< \brief Stored ET end times for occultation events*/
      // Static Memory Parameters
      const int m_NUMBER_OF_DATE_CHARACTERS=51;
      // Auxilary Parameters
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
      * \brief I think that the only thing that needs specified to clear is the cspice kernel pool
      */
      ~Occultations();
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

      /**
      * \brief This will clear the m_resultStartTimeInterval and m_resultEndTimeInterval
      */
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

      /**
      * \brief Prints out a list of time intervals results in UTC time
      *
      */
      void PrintTimes();

      /**
      * \brief load additional kernels
      */
      void LoadKernel(std::string filename);

      /**
      * \brief set the observer
      */
      void SetObserver(std::string observer);
  };
}
#endif  // OCCULTATIONS_H_
