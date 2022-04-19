#ifndef TYPES_H
#define TYPES_H

#include "bool.h"

#define ACCELEROMETOR_VECTOR_DIM 3
#define TIME_SERIES_VECTORS_AMOUNT 12
#define TIME_SERIES_OBSERVATION_DIM (TIME_SERIES_VECTORS_AMOUNT * ACCELEROMETOR_VECTOR_DIM)
#define SAMPLED_OBSERVATION_DIM 3
/* The most important thing here is that _currentIndex is set to 0 */
#define TIME_SERIES_OBSERVATION_INIT { false, { 0 }, 0 }


typedef struct TimeSeriesObservation_s {
    bool isFull;
    double observation[TIME_SERIES_OBSERVATION_DIM];
    int _currentIndex;
} TimeSeriesObservation;

typedef struct AggregatedObservation_s {
    double observation[SAMPLED_OBSERVATION_DIM];
} SampledObservation;

#endif /* END OF TYPES_H */
