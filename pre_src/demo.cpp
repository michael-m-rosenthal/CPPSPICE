#include <stdio.h>
#include "SpiceUsr.h"
#include "demo_class.h"
int main (){
  const int FILESZ = 256;
  const int WORDSZ = 41;
  const int ROOM = 10;
  // initialize the demo class
  demo_class demo(FILESZ, WORDSZ,ROOM);
  // prompt the user for inputs
  demo.prompt();
  // process the request
  demo.process_request();
  return(0);
}