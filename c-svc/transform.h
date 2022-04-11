#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <time.h>
#include <stdbool.h>
#include <assert.h>

#define OBSERVATION_DIM 36

typedef struct Observation {
    bool isFull;
    double observation[OBSERVATION_DIM];
    int _currentIndex;
} Observation;

void transform(Observation *o, double newVector[3]);

#endif /* END OF TRANSFORM_H */
