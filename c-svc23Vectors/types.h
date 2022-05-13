#ifndef TYPES_H
#define TYPES_H

#include "bool.h"

#define ACCELEROMETOR_VECTOR_DIM 3
#define TIME_SERIES_VECTORS_AMOUNT 36
#define TIME_SERIES_OBSERVATION_DIM (TIME_SERIES_VECTORS_AMOUNT * ACCELEROMETOR_VECTOR_DIM)
#define SAMPLED_OBSERVATION_DIM 23
/* The most important thing here is that _currentIndex is set to 0 */
#define TIME_SERIES_OBSERVATION_INIT { false, { 0 }, 0 }
#define TIME_SERIES_OBSERVATION_INIT_108_VALUES {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3}

typedef struct TimeSeriesObservation_s {
    bool isFull;
    int  observation[TIME_SERIES_OBSERVATION_DIM];
    int  _currentIndex;
} TimeSeriesObservation;

typedef struct SampledObservation_s {
    int observation[SAMPLED_OBSERVATION_DIM];
} SampledObservation;

#endif /* END OF TYPES_H */
