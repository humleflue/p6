#include "kernels.h"

double radialKernel(SampledObservation x, SampledObservation y) {
    double sumOfVectorsSquared = 0,
           vectorEntryDiffSquared;
    int    i,
           roundedExponent;

    for(i = 0; i < SAMPLED_OBSERVATION_DIM; i++) {
        vectorEntryDiffSquared = power(x.observation[i] - y.observation[i], 2);
        sumOfVectorsSquared += vectorEntryDiffSquared;
    }

    roundedExponent = round((GAMMA * -1) * sumOfVectorsSquared);

    return power(EULER, roundedExponent);
}

/* TODO: Implement the Linear Kernel */
double linearKernel(SampledObservation x, SampledObservation y) {
    return 0.0 + x.observation[0] + y.observation[0];
}
