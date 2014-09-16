#ifndef __TRANSFORM__
#define __TRANSFORM__
#include "glStuff.h"
class Transform {
      public:
         static double* rotate(double dx,double dy,double dz,double angle,double *coords);
//         static double* opMatrixd(double *matrix,double *vec);
};
#endif
