#ifndef KERNELS_H
#define KERNELS_H

#include "math.h"
#include "types.h"

#define GAMMA 24.5

double radialKernel(SampledObservation x, SampledObservation y);
int linearKernel(SampledObservation x, SampledObservation y);
SampledObservation sampledObservationConstructor(const double vector[SAMPLED_OBSERVATION_DIM]);

#endif /* END OF KERNELS_H */
