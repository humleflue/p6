#ifndef KERNELS_H
#define KERNELS_H

#include "math.h"
#include "types.h"

#define EULER 2.71828
#define GAMMA 24.5

double radialKernel(SampledObservation x, SampledObservation y);
double linearKernel(SampledObservation x, SampledObservation y);

#endif /* END OF KERNELS_H */
