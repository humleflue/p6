#include "transform.h"
#include "predictor.h"

char svc() {
    int data[TIME_SERIES_VECTORS_AMOUNT][ACCELEROMETOR_VECTOR_DIM] = {
        {0, -1, 0},
        {-1, -6, -35},
        {0, 4, 32},
        {-1, -1, 1},
        {0, 1, 2},
        {1, 0, -2},
        {-25, 5, -1},
        {24, -5, 1},
        {-2, -2, 0},
        {0, 2, -1},
        {0, 0, 0},
        {1, -1, -1},
        {-1, -1, 0},
        {-1, 0, 0},
        {0, -1, -2},
        {0, -1, 0},
        {-1, 0, 0},
        {0, 0, -1},
        {-1, 2, 2},
        {2, -2, -2},
        {6, 4, 1},
        {-9, -5, 0},
        {-6, -3, 9},
        {16, -2, -13},
        {-18, 1, 2},
        {9, -3, -2},
        {-1, 4, 0},
        {-2, 3, 1},
        {-1, 0, -1},
        {1, -1, 0},
        {1, -2, -1},
        {-4, 0, -1},
        {2, 0, -1},
        {-3, -1, 2},
        {4, 0, -1},
        {-3, 0, -2}
    };
    int i;
    TimeSeriesObservation timeSeriesObservation = TIME_SERIES_OBSERVATION_INIT;
    SampledObservation sampledObservation;

    for(i = 0; i < TIME_SERIES_VECTORS_AMOUNT; i++) {
        addVectorToTimeSeriesObservation(&timeSeriesObservation, data[i]);
    }

    transformTo23Dimensions(timeSeriesObservation, &sampledObservation);
    return predict(sampledObservation);
}
