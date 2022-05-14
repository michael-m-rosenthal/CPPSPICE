#include "lowLevel.hpp"
#include <vector>
#include <cassert>
#include <cmath>

double dotProduct(std::vector<double> & vector1, std::vector<double> & vector2 )
{
  assert(( vector1.size() == vector2.size() ) && "Dimension must match");
  double dotProduct=0;
  for ( int ii = 0; ii < vector1.size(); ii++ )
  {
    dotProduct += vector1[ii]*vector2[ii];
  }
  return dotProduct;
}

double normalize( std::vector<double> & vector1 )
{
  double dot= dotProduct( vector1, vector1 );
  double length= std::sqrt(dot);
  for ( int ii = 0; ii < vector1.size(); ii++ )
  {
    vector1[ii] /= length;
  }
  return length;
}

void crossProduct3(std::vector<double> & vector1, std::vector<double> & vector2, std::vector<double>  & vector3 ){
  vector3[0] = vector1[1] * vector3[2] - vector1[2] * vector3[1];
  vector3[1] = vector1[2] * vector3[0] - vector1[0] * vector3[2];
  vector3[2] = vector1[0] * vector3[1] - vector1[1] * vector3[0];
}

double frobenius3( double x, double y, double z ){
  return std::sqrt( x * x + y * y + z * z );
}

double linearInterp(double x1, double x2, double y1, double y2, double xnew){
  return (y2-y1)*(xnew-x1)/(x2-x1)+y1;
}
