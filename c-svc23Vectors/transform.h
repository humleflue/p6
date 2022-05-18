#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "types.h"

void addVectorToTimeSeriesObservation(TimeSeriesObservation *tso, int newVector[ACCELEROMETOR_VECTOR_DIM]);
void transform(TimeSeriesObservation o, SampledObservation *out);
void extractXYZ(TimeSeriesObservation tso, int x[TIME_SERIES_VECTORS_AMOUNT], int y[TIME_SERIES_VECTORS_AMOUNT], int z[TIME_SERIES_VECTORS_AMOUNT]);
void transformTo23Dimensions(TimeSeriesObservation tso, SampledObservation *out);
#endif /* END OF TRANSFORM_H */
