#include <string.h>
 #include <stdio.h>
 #include "SpiceUsr.h"

    /*
    PROGRAM VISIBL

    Find and display the window of times when the MEX
    spacecraft is above a specified elevation limit in the
    topocentric reference frame of DSN station DSS-14
    and is not occulted by Mars.
    */

 int main()
 {
    /*
    Local constants
    */

    /*
    The  meta-kernel:
    */
    #define METAKR          "visibl.tm"

    /*
    Maximum number of intervals in any window:
    */
    #define MAXIVL          1000

    /*
    Maximum result window size:
    */
    #define MAXWIN          ( 2 * MAXIVL )

    /*
    Format string for time output:
    */
    #define TDBFMT          "YYYY MON DD HR:MN:SC.### TDB ::TDB"

    /*
    Time string length:
    */
    #define TIMLEN          29

    /*
    Local variables
    */

    /*
    Confinement window used to store interval to be searched:
    */
    SPICEDOUBLE_CELL        ( cnfine, MAXWIN );

    /*
    Windows to hold sets of times for which

       - target is occulted
       - target is above the elevation limit
       - target is visible

    Separate ccultation and visibility windows are used
    for ellipsoidal and DSK target shape models.
    */
    SPICEDOUBLE_CELL        ( docwin, MAXWIN );
    SPICEDOUBLE_CELL        ( eocwin, MAXWIN );
    SPICEDOUBLE_CELL        ( riswin, MAXWIN );
    SPICEDOUBLE_CELL        ( dvswin, MAXWIN );
    SPICEDOUBLE_CELL        ( evswin, MAXWIN );

    SpiceChar             * abcorr;
    SpiceChar             * back;
    SpiceChar             * bframe;
    SpiceChar             * bshape;
    SpiceChar             * coord;
    SpiceChar             * crdsys;
    SpiceChar             * fframe;
    SpiceChar             * front;
    SpiceChar             * fshape;
    SpiceChar             * obsfrm;
    SpiceChar             * occtyp;
    SpiceChar             * relate;
    SpiceChar             * srfpt;
    SpiceChar             * start;
    SpiceChar             * stop;
    SpiceChar             * target;
    SpiceChar               btmstr [ TIMLEN ];
    SpiceChar               etmstr [ TIMLEN ];

    SpiceDouble             adjust;
    SpiceDouble             dintbg;
    SpiceDouble             dinten;
    SpiceDouble             elvlim;
    SpiceDouble             etbeg;
    SpiceDouble             etend;
    SpiceDouble             intbeg;
    SpiceDouble             intend;
    SpiceDouble             revlim;

    /*
    stepsz is the step size, measured in seconds, used to search
    for times bracketing a state transition.
    */
    SpiceDouble             stepsz;

    SpiceInt                i;
    SpiceInt                winsiz;


    /*
    Load the meta-kernel.
    */
    furnsh_c ( METAKR );

    /*
    Assign the inputs for our search.

    Since we're interested in the apparent location of the
    target, we use light time and stellar aberration
    corrections. We use the "converged Newtonian" form
    of the light time correction because this choice may
    increase the accuracy of the occultation times we'll
    compute using gfoclt_c.
    */
    srfpt  = "DSS-14";
    obsfrm = "DSS-14_TOPO";
    target = "MEX";
    abcorr = "CN+S";
    start  = "2004 MAY 2 TDB";
    stop   = "2004 MAY 6 TDB";
    elvlim =  6.0;

    /*
    The elevation limit above has units of degrees; we convert
    this value to radians for computation using SPICE routines.
    We'll store the equivalent value in radians in REVLIM.
    */
    revlim = rpd_c() * elvlim;

    /*
    We model the target shape as a point.

    We model the target shape as a point. We either model the
    blocking body's shape as an ellipsoid, or we represent
    its shape using actual topographic data. No body-fixed
    reference frame is required for the target since its
    orientation is not used.
    */
    back   = target;
    bshape = "POINT";
    bframe = " ";
    front  = "MARS";
    fframe = "IAU_MARS";

    /*
    The occultation type should be set to "ANY" for a point
    target.
    */
    occtyp = "any";

    /*
    Since SPICE doesn't directly support the AZ/EL coordinate
    system, we use the equivalent constraint

       latitude > REVLIM

    in the latitudinal coordinate system, where the reference
    frame is topocentric and is centered at the viewing location.
    */
    crdsys = "LATITUDINAL";
    coord  = "LATITUDE";
    relate = ">";

    /*
    The adjustment value only applies to absolute extrema
    searches; simply give it an initial value of zero
    for this inequality search.
    */
    adjust = 0.0;

    /*
    STEPSZ is the step size, measured in seconds, used to search
    for times bracketing a state transition. Since we don't expect
    any events of interest to be shorter than five minutes, and
    since the separation between events is well over 5 minutes,
    we'll use this value as our step size. Units are seconds.
    */
    stepsz = 300.0;

    /*
    Display a banner for the output report:
    */
    printf ( "\n%s\n\n",
             "Inputs for target visibility search:" );

    printf ( "   Target                       = %s\n", target );
    printf ( "   Observation surface location = %s\n", srfpt  );
    printf ( "   Observer's reference frame   = %s\n", obsfrm );
    printf ( "   Blocking body                = %s\n", front  );
    printf ( "   Blocker's reference frame    = %s\n", fframe );
    printf ( "   Elevation limit (degrees)    = %f\n", elvlim );
    printf ( "   Aberration correction        = %s\n", abcorr );
    printf ( "   Step size (seconds)          = %f\n", stepsz );

    /*
    Convert the start and stop times to ET.
    */
    str2et_c ( start, &etbeg );
    str2et_c ( stop,  &etend );

    /*
    Display the search interval start and stop times
    using the format shown below.

       2004 MAY 06 20:15:00.000 (TDB)
    */
    timout_c ( etbeg, TDBFMT, TIMLEN, btmstr );
    printf ( "   Start time                   = %s\n", btmstr  );

    timout_c ( etend, TDBFMT, TIMLEN, etmstr );
    printf ( "   Stop time                    = %s\n", etmstr  );

    printf ( "\n" );

    /*
    Initialize the "confinement" window with the interval
    over which we'll conduct the search.
    */
    wninsd_c ( etbeg, etend, &cnfine );

    /*
    In the call below, the maximum number of window
    intervals gfposc_c can store internally is set to MAXIVL.

    Now search for the time period, within our confinement
    window, during which the apparent target has elevation
    at least equal to the elevation limit.
    */
    gfposc_c ( target, obsfrm, abcorr, srfpt,
               crdsys, coord,  relate, revlim,
               adjust, stepsz, MAXIVL, &cnfine, &riswin );

    /*
    Now find the times when the apparent target is above
    the elevation limit and is not occulted by the
    blocking body (Mars). We'll find the window of times when
    the target is above the elevation limit and *is* occulted,
    then subtract that window from the view period window
    riswin found above.

    For this occultation search, we can use riswin as
    the confinement window because we're not interested in
    occultations that occur when the target is below the
    elevation limit.

    Find occultations within the view period window.
    */
    printf ( " Searching using ellipsoid target shape model...\n" );

    fshape = "ELLIPSOID";

    gfoclt_c ( occtyp, front,  fshape,  fframe,
               back,   bshape, bframe,  abcorr,
               srfpt,  stepsz, &riswin, &eocwin );

    printf ( " Done.\n" );

    /*
    Subtract the occultation window from the view period
    window: this yields the time periods when the target
    is visible.
    */
    wndifd_c ( &riswin, &eocwin, &evswin );

    /*
    Repeat the search using low-resolution DSK data
    for the front body.
    */
    printf ( " Searching using DSK target shape model...\n" );

    fshape = "DSK/UNPRIORITIZED";

    gfoclt_c ( occtyp, front,  fshape,  fframe,
               back,   bshape, bframe,  abcorr,
               srfpt,  stepsz, &riswin, &docwin );

    printf ( " Done.\n" );

    wndifd_c ( &riswin, &docwin, &dvswin );


    /*
    The function wncard_c returns the number of intervals
    in a SPICE window.
    */
    winsiz = wncard_c( &evswin );

    if ( winsiz == 0 )
    {
       printf ( "No events were found.\n" );
    }
    else
    {
       /*
       Display the visibility time periods.
       */
       printf ( "\nVisibility start and stop times of "
                "%s as seen from %s\n"
                "using both ellipsoidal and DSK "
                "target shape models:"
                "\n\n",
                target, srfpt                       );

       for (  i = 0;   i < winsiz;   i++  )
       {
          /*
          Fetch the start and stop times of the Ith interval
          from the ellipsoid search result window evswin.
          */
          wnfetd_c ( &evswin, i, &intbeg, &intend );

          /*
          Convert the start and stop times to TDB calendar
          strings. Write the results.
          */
          timout_c ( intbeg, TDBFMT, TIMLEN, btmstr );
          timout_c ( intend, TDBFMT, TIMLEN, etmstr );

          printf ( " Ell: %s : %s\n", btmstr, etmstr );

          /*
          Fetch the start and stop times of the Ith interval
          from the DSK search result window dvswin.
          */
          wnfetd_c ( &dvswin, i, &dintbg, &dinten );

          /*
          Convert the start and stop times to TDB calendar
          strings. Write the results.
          */
          timout_c ( dintbg, TDBFMT, TIMLEN, btmstr );
          timout_c ( dinten, TDBFMT, TIMLEN, etmstr );

          printf ( " DSK: %s : %s\n", btmstr, etmstr );

          printf ( "\n" );
       }
    }

    return ( 0 );
 }
