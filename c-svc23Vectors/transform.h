#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "types.h"

void addVectorToTimeSeriesObservation(TimeSeriesObservation *tso, int newVector[ACCELEROMETOR_VECTOR_DIM]);
void transform(TimeSeriesObservation o, SampledObservation *out);
void extractXYZ(TimeSeriesObservation tso, double x[TIME_SERIES_VECTORS_AMOUNT], double y[TIME_SERIES_VECTORS_AMOUNT], double z[TIME_SERIES_VECTORS_AMOUNT]);
#endif /* END OF TRANSFORM_H */
