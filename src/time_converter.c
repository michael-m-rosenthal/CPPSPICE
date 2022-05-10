#include <stdio.h>
#include "SpiceUsr.h"
int main (){
  SpiceChar utc[32];
  SpiceDouble et;
  furnsh_c  ( "data/naif0008.tls" );
  str2et_c  ( "2005 DEC 31 12:00", &et );
  timout_c ( et+spd_c(), "YYYY-DOYTHR:MN:SC.### ::RND", 32, utc );
  return(0);
}
