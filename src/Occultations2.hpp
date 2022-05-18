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
      SpiceDouble m_startET; /* \brief the desired starting ET time for the search*/
      SpiceDouble m_endET; /* \brief the desired ending ET time for the search*/
      // SPICE variables
      std::string m_timeFormat;  /**< \brief a string that tells cspice how to translate ET to a date string */
      std::string m_occultationType; /**< \brief occtyp input for gfoclt_c */
      std::string m_front; /**< \brief front input for gfoclt_c */
      std::string m_back; /**< \brief back input for gfoclt_c */
      std::string m_observer; /**< \brief obsrvr input for gfoclt_c */
      std::string m_frame; /* \brief J2000 */
      // Auxilary variables
      SpiceDouble m_currentET; /* \brief the current time at which the algorithm is searching through */
      SpiceDouble m_stepSizeET; /* \brief the time stepsize used to search for events */
      std::vector<double> m_toFront;/* \brief vector pointing toward the back from the observer */
      std::vector<double> m_frontVelocity;/* \brief velocity of the back with respect to observer's center */
      std::vector<double> m_toBack;/* \brief vector pointing to the front from the center of the observer */
      std::vector<double> m_backVelocity;/* \brief velocity of the front with respect to the observer's center */
      std::vector<double> m_currentNormal;/* \brief unit direction toward the back */
      double m_halfFrontRevolution; /* \brief how much time can we safely fast-forward when the front is behind the observer with respec to the back?*/
      // planetary constant parameter
      double m_observerRadius; /* \brief the maximum radius of the observer */
      double m_frontRadius;/* \brief the maximum radius of the back*/
      double m_backRadius;/* \brief the maximum radius of the front */
      double m_radiusA;/* \brief the maximum radius of the observer plus front */
      double m_radiusB;/* \brief the maximum radius of the back plus front */
      // output
      std::vector<double> resultET; /* \brief result times
      *
      * should be even with adjacent times denoting start and end times.
      */
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
      void LoadKernel( std::string filename );
      /**
      * \brief set the cspice observer object (default for the class is EARTH)
      */
      void SetObserver( std::string object );
      /**
      * \brief set the cspice front object (default for the class is MOON)
      */
      void SetFront( std::string object );
      /**
      * \brief set the cspice back object (default for the class is SUN)
      */
      void SetBack( std::string object) ;
      /**
      * \brief set  stepsize used to search for events (default for the class is 180 seconds)
      */
      void SetstepSizeET( double stepSizeET );
      /**
      * \brief set the frame used by cspise (default for the class is J2000)
      */
      void SetFrame( std::string frame );
      /**
      * \brief set the start and end time for the search
      */
      void SetTimeWindow( std::string startDateTime, std::string endDateTime );
      /**
      * \brief A wrapper for getting the state of an object with respect to observer
      */
      void GetState( std::string target, std::string observer,  std::vector<double> &position, std::vector<double> &velocity  );
      /**
      * \brief Computes the dot product between the back and the front vectors.
      */
      double CurrentFrontDotBack();
      /**
      * \brief Runs the main search
      */
      void RunSearch();
      /**
      * \brief Print the current results to the screen
      */
      void PrintResults();
  };
}


#endif  // Occultations2_H_
