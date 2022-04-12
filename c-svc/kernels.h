#ifndef KERNELS_H
#define KERNELS_H

#include "math.h"
#include "types.h"

#define EULER 2.71828
#define GAMMA 24.5

double radialKernel(AggregatedObservation x, AggregatedObservation y);
double linearKernel(AggregatedObservation x, AggregatedObservation y);

#endif /* END OF KERNELS_H */
