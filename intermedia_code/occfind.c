/**

example taken from https://naif.jpl.nasa.gov/pub/naif/toolkit_docs/C/info/mostused.html

The following example determines time intervals in December, 2001
when the Sun is occulted by the Moon (solar eclipses) as seen from
the center of the Earth, with both Sun and Moon modeled as
ellipsoids
*/

#include <stdio.h>
#include "SpiceUsr.h"

int main (){
  #define MAXWIN          200
  #define TIMLEN          51
  /*
  Format string for time output:
  */
  #define TDBFMT          "YYYY MON DD HR:MN:SC.### TDB ::TDB"
  SPICEDOUBLE_CELL      ( cnfine, MAXWIN );
  SPICEDOUBLE_CELL      ( result, MAXWIN );
  SPICEDOUBLE_CELL      ( dvswin, MAXWIN );
  SPICEDOUBLE_CELL        ( evswin, MAXWIN );
  SpiceDouble             et0;
  SpiceDouble             et1;
  SpiceDouble             step;
  SpiceChar             * target;
  SpiceChar               timstr  [ TIMLEN ];
  SpiceDouble             intbeg;
  SpiceDouble             intend;
  SpiceChar               begstr [ TIMLEN ];
  SpiceChar               endstr [ TIMLEN ];
  SpiceDouble             dintbg;
  SpiceDouble             dinten;
  SpiceInt i;
  SpiceDouble start;
  SpiceDouble finish;

  /*
     Load kernels.
  */
  furnsh_c( "data/naif0012.tls"  );
  furnsh_c( "data/de430.bsp"     );
  furnsh_c( "data/pck00010.tpc"  );
  /*
     Store the time bounds in the confinement window.
  */
  str2et_c ( "2001 DEC 01", &et0 );
  str2et_c ( "2002 JAN 01", &et1 );

  wninsd_c ( et0, et1, &cnfine );

  /*
     Set search parameters. Select a 3-minute step.
  */
  step = 180.0;

  /*
     Perform search.
  */
  gfoclt_c ( "ANY",
             "MOON",    "ELLIPSOID",  "IAU_MOON",
             "SUN",     "ELLIPSOID",  "IAU_SUN",
             "LT",      "EARTH",      step,
             &cnfine,   &result                 );
   // Place the difference of two double precision windows into a third window.
   wndifd_c ( &cnfine, &result , &dvswin );
   SpiceInt winsiz;
   /*
     The function wncard_c returns the number of intervals
     in a SPICE window.
   */
   winsiz = wncard_c( &result  );
   if ( winsiz == 0 )
            {
               printf ( "No events were found.\n" );
            }
            else
            {
              printf ( "Events were found.\n" );
              printf ( "\nTimes of occultation of Sun by Moon:\n\n" );

                       for ( i = 0;  i < wncard_c( &result );  i++ )
                       {
                          /*
                          Fetch the start and stop times of the Ith
                          interval from the window `result'.
                          */
                          wnfetd_c ( &result, i, &start, &finish );

                          timout_c ( start,  TDBFMT, TIMLEN, begstr );// you need to be careful here about the time... I think it is wrong
                          timout_c ( finish, TDBFMT, TIMLEN, endstr );

                          printf ( "   %s   %s\n", begstr, endstr );
                       }
            }

}
