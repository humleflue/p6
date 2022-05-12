#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "types.h"

void addVectorToTimeSeriesObservation(TimeSeriesObservation *tso, int newVector[ACCELEROMETOR_VECTOR_DIM]);
void transform(TimeSeriesObservation o, SampledObservation *out);

#endif /* END OF TRANSFORM_H */
