#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <time.h>
#include <stdbool.h>
#include <assert.h>

#define OBSERVATION_DIM 36
#define TRANSFORMED_OBSERVATION_DIM 3

typedef struct Observation {
    bool isFull;
    double observation[OBSERVATION_DIM];
    int _currentIndex;
} Observation;

typedef struct TransformedObservation {
    double observation[TRANSFORMED_OBSERVATION_DIM];
} TransformedObservation;

void addVectorToObservation(Observation *o, double newVector[3]);
TransformedObservation transform(Observation o);

#endif /* END OF TRANSFORM_H */
