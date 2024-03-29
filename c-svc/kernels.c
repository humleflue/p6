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

    roundedExponent = roundDouble((GAMMA * -1) * sumOfVectorsSquared);

    return power(EULER, roundedExponent);
}

int linearKernel(SampledObservation x, SampledObservation y) {
    return dotProduct3dVectors(x.observation, y.observation);
}

SampledObservation sampledObservationConstructor(const double vector[SAMPLED_OBSERVATION_DIM]) {
    int i;
    SampledObservation result;

    for(i = 0; i < SAMPLED_OBSERVATION_DIM; i++) {
        result.observation[i] = (int)vector[i];
    }

    return result;
}
