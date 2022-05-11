/**
// SPICE2 Version 0.0.0, 10-May-2022 (MMR)
*/

#ifndef OCCULTATIONS_H_
#define OCCULTATIONS_H_

#include <stdio.h>
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
    public:
      void Occultations();
      void ~Occultations();
  };
}
#endif  // OCCULTATIONS_H_
