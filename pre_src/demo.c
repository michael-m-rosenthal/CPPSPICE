#include <stdio.h>
#include "SpiceUsr.h"

int main (){
  #define FILESZ 256
  #define WORDSZ 41
  #define ROOM 10

  SpiceBoolean found;
  SpiceChar iframe[WORDSZ];
  SpiceChar instnm[WORDSZ];
  SpiceChar satnm [WORDSZ];
  SpiceChar fixref[WORDSZ];
  SpiceChar scnm [WORDSZ];
  SpiceChar setupf[FILESZ];
  SpiceChar shape [WORDSZ];
  SpiceChar time [WORDSZ];

  SpiceDouble alt;
  SpiceDouble bundry[ROOM][3];
  SpiceDouble emissn;
  SpiceDouble et;
  SpiceDouble f;
  SpiceDouble insite[3];
  SpiceDouble srfvec[3];
  SpiceDouble pclat;
  SpiceDouble pclon;
  SpiceDouble pdlat;
  SpiceDouble pdlon;
  SpiceDouble phase;
  SpiceDouble point [3];
  SpiceDouble r;
  SpiceDouble radii [3];
  SpiceDouble re;
  SpiceDouble rp;
  SpiceDouble solar;
  SpiceDouble trgepc;

  SpiceInt i;
  SpiceInt instid;
  SpiceInt n;

  /* Prompt for the user-supplied inputs for our program */
  prompt_c ( "Enter setup file name > ", FILESZ, setupf );
  furnsh_c ( setupf );
  prompt_c ( "Enter satellite name > ", WORDSZ, satnm );
  prompt_c ( "Enter satellite frame > ", WORDSZ, fixref );
  prompt_c ( "Enter spacecraft name > ", WORDSZ, scnm );
  prompt_c ( "Enter instrument name > ", WORDSZ, instnm );
  prompt_c ( "Enter time > ", WORDSZ, time );

  /* Get the epoch corresponding to the input time: */
  str2et_c ( time, &et );
  /* Get the radii of the satellite. */
  bodvrd_c ( satnm, "RADII", 3, &i, radii );
  /* Get the instrument boresight and frame name. */
  bodn2c_c ( instnm, &instid, &found );
  if ( !found )
  {
      setmsg_c ( "Instrument name # could not be "
      "translated to an ID code." );
      errch_c ( "#", instnm );
      sigerr_c ( "NAMENOTFOUND" );
  }
  getfov_c ( instid, ROOM, WORDSZ, WORDSZ,
            shape, iframe, insite, &n, bundry );
  /* Compute the boresight ray intersection with the surface of the
    target body. */
  sincpt_c ( "Ellipsoid", satnm, et, fixref, "CN+S", scnm,
  iframe, insite, point, &trgepc, srfvec, &found );
  /* If an intercept is found, compute planetocentric and planetodetic
  latitude and longitude of the point. */
  if ( found )
  {
    reclat_c ( point, &r, &pclon, &pclat );
    /* Let re, rp, and f be the satellite's longer equatorial
    radius, polar radius, and flattening factor. */
    re = radii[0];
    rp = radii[2];
    f = ( re - rp ) / re;
    recgeo_c ( point, re, f, &pdlon, &pdlat, &alt );
    /* Compute illumination angles at the surface point. */
    ilumin_c ( "Ellipsoid", satnm, et, fixref, "CN+S", scnm, point,
    &trgepc, srfvec, &phase, &solar, &emissn );
    /* Display results. Convert angles to degrees for output. */
    printf (  "\n"
              "Intercept planetocentric longitude (deg): %11.6f\n"
              "Intercept planetocentric latitude (deg): %11.6f\n"
              "Intercept planetodetic longitude (deg): %11.6f\n"
              "Intercept planetodetic latitude (deg): %11.6f\n"
              "Range from spacecraft to intercept point (km): %11.6f\n"
              "Intercept phase angle (deg): %11.6f\n"
              "Intercept solar incidence angle (deg): %11.6f\n"
              "Intercept emission angle (deg): %11.6f\n",
              dpr_c() * pclon,
              dpr_c() * pclat,
              dpr_c() * pdlon,
              dpr_c() * pdlat,
              vnorm_c( srfvec ),
              dpr_c() * phase,
              dpr_c() * solar,
              dpr_c() * emissn
          );
  } else {
    printf ( "No intercept point found at %s\n", time );
  }
  return(0);
}