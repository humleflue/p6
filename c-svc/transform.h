#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <time.h>
#include <stdbool.h>
#include <assert.h>

#define VECTOR_DIM 3
#define TIME_SERIES_VECTORS_AMOUNT 12
#define TIME_SERIES_OBSERVATION_DIM (TIME_SERIES_VECTORS_AMOUNT * VECTOR_DIM)
#define AGGREGATED_OBSERVATION_DIM 3

typedef struct TimeSeriesObservation {
    bool isFull;
    double observation[TIME_SERIES_OBSERVATION_DIM];
    int _currentIndex;
} TimeSeriesObservation;

typedef struct AggregatedObservation {
    double observation[AGGREGATED_OBSERVATION_DIM];
} AggregatedObservation;

void addVectorToTimeSeriesObservation(TimeSeriesObservation *tso, double newVector[VECTOR_DIM]);
void transform(TimeSeriesObservation o, AggregatedObservation *out);

#endif /* END OF TRANSFORM_H */
