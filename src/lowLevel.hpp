
#ifndef LOWLEVEL_H_
#define LOWLEVEL_H_

#include <vector>



double dotProduct(std::vector<double> & vector1, std::vector<double> & vector2 );


/**
* \brief make the vector of unit length
*/
double normalize( std::vector<double> & vector1 );

/**
* \brief compute the cross product of the first two vectors and output to the third.
*/
void crossProduct3(std::vector<double> & vector1, std::vector<double> & vector2, std::vector<double> & vector3 );

double frobenius3( double x, double y, double z );

double linearInterp( double x1, double x2, double y1, double y2, double xnew );

#endif  // LOWLEVEL_H_
