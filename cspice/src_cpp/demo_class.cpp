#include "demo_class.h"
#include <stdio.h>
#include "SpiceUsr.h"

demo_class::demo_class(int max_file_string_size_0, int max_word_size_0, int room_0){
  // set dimension parameters
  max_file_string_size=max_file_string_size_0;
  max_word_size=max_word_size_0;
  room=room_0;
  // initialized inputs
  setupf.resize(max_file_string_size);
  satnm.resize(max_word_size);
  fixref.resize(max_word_size);
  scnm.resize(max_word_size);
  instnm.resize(max_word_size);
  time.resize(max_word_size);
};

demo_class::~demo_class(){
  setupf.clear();
  satnm.clear();
  fixref.clear();
  scnm.clear();
  instnm.clear();
  time.clear();
}

void demo_class::prompt(){
  prompt_c ( "Enter setup file name > ", max_file_string_size, &setupf[0] );
  furnsh_c ( &setupf[0] );
  prompt_c ( "Enter satellite name > ", max_word_size, &satnm[0] );
  prompt_c ( "Enter satellite frame > ", max_word_size, &fixref[0] );
  prompt_c ( "Enter spacecraft name > ", max_word_size, &scnm[0] );
  prompt_c ( "Enter instrument name > ", max_word_size, &instnm[0] );
  prompt_c ( "Enter time > ", max_word_size, &time[0] );
}

void demo_class::process_request(){
  SpiceBoolean found;
  SpiceChar iframe[max_word_size];
  SpiceChar shape [max_word_size];
  SpiceDouble alt;
  SpiceDouble bundry[room][3];
  SpiceDouble et;
  SpiceDouble f;
  SpiceDouble insite[3];
  SpiceDouble point [3];
  SpiceDouble r;
  SpiceDouble radii [3];
  SpiceDouble re;
  SpiceDouble rp;
  SpiceDouble trgepc;
  SpiceInt i;
  SpiceInt instid;
  SpiceInt n;
  /* Get the epoch corresponding to the input time: */
  str2et_c ( &time[0], &et );
  /* Get the radii of the satellite. */
  bodvrd_c ( &satnm[0], "RADII", 3, &i, radii );
  /* Get the instrument boresight and frame name. */

  bodn2c_c ( &instnm[0], &instid, &found );
  if ( !found )
  {
      setmsg_c ( "Instrument name # could not be "
      "translated to an ID code." );
      errch_c ( "#", &instnm[0] );
      sigerr_c ( "NAMENOTFOUND" );
  }
  getfov_c ( instid, room, max_word_size, max_word_size,
            shape, iframe, insite, &n, bundry );
  /* Compute the boresight ray intersection with the surface of the
    target body. */
  sincpt_c ( "Ellipsoid", &satnm[0], et, &fixref[0], "CN+S", &scnm[0],
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
    ilumin_c ( "Ellipsoid", &satnm[0], et, &fixref[0], "CN+S", &scnm[0], point,
    &trgepc, srfvec, &phase, &solar, &emissn );
    display_results();
  } else {
    printf ( "No intercept point found at %s\n", &time[0] );
  }
}

void demo_class::display_results(){
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
}

