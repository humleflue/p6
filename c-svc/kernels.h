#ifndef KERNELS_H
#define KERNELS_H

#include "math.h"
#include "types.h"
#include "matrixmath.h"

#define GAMMA 24.5

double radialKernel(SampledObservation x, SampledObservation y);
double linearKernel(SampledObservation x, SampledObservation y);

#endif /* END OF KERNELS_H */
