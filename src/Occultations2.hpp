/**
// SPICE2 Version 0.0.0, 10-May-2022 (MMR)
*/

#ifndef Occultations2_H_
#define Occultations2_H_

#include "SpiceUsr.h"
#include <vector>
#include <string>

namespace spice
{
  /**
  * \brief A c++ class for computing the position (and velocity) of planents
  */
  class Occultations2
  {
    private:
      SpiceDouble m_startET;
      SpiceDouble m_endET;
      //
      SpiceDouble m_currentET;
      SpiceDouble m_stepSizeET;
      //
      std::string m_timeFormat;  /**< \brief a string that tells cspice how to translate ET to a date string */
      std::string m_occultationType; /**< \brief occtyp input for gfoclt_c */
      std::string m_front; /**< \brief front input for gfoclt_c */
      std::string m_back; /**< \brief back input for gfoclt_c */
      std::string m_observer; /**< \brief obsrvr input for gfoclt_c */
      std::string m_frame;
      //


      std::vector<double> m_toFront;
      std::vector<double> m_frontVelocity;
      std::vector<double> m_toBack;
      std::vector<double> m_backVelocity;
      std::vector<double> m_currentNormal;
      std::vector<double> m_toObserver;
      std::vector<double> m_ObserverVelocity;
      double m_halfMoonRevolution;
      //
      double m_observerRadius;
      double m_frontRadius;
      double m_backRadius;
      double m_radiusA;
      double m_radiusB;
      //
      std::vector<double> resultET;
    public:
      /**
      * \brief initialize the occultation calculation class
      *
      * You need to include paths to files that have the relevent the leap seconds data, empheris data, and planetary constants.
      */
      Occultations2(
              std::string filenameLSK,  /**< \brief file path for the leap second kernel*/
              std::string filenameSPK,  /**< \brief file path for the planetary ephemeris data kernel*/
              std::string filenamePCK   /**< \brief file path for the planetary constant data kernel*/
            );
      /**
      * \brief I think that the only thing that needs specified to clear is the cspice kernel pool
      */
      ~Occultations2();
      /**
      * \brief load additional kernels
      */
      void LoadKernel(std::string filename);
      void SetTimeWindow( std::string startDateTime, std::string endDateTime );
      void GetState( std::string target, std::string observer,  std::vector<double> &position, std::vector<double> &velocity  );
      double CurrentFrontDotBack();
      void RunSearch();
      void PrintResults();
  };
}


#endif  // Occultations2_H_
