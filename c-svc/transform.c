#include "transform.h"

/* Adds the x, y and z from newVector to the observation array in the tso,
 * If the tso.observation array is full we do nothing
 * Note: tso is both input and output param 
 */
void addVectorToTimeSeriesObservation(TimeSeriesObservation *tso, double newVector[ACCELEROMETOR_VECTOR_DIM]) {
    int i = tso->_currentIndex,
        j;
    
    if(!tso->isFull) {
        for(j = 0; j < ACCELEROMETOR_VECTOR_DIM; j++) {
            tso->observation[i+j] = newVector[j];
        }
        
        tso->_currentIndex += 3;

        if(tso->_currentIndex == TIME_SERIES_OBSERVATION_DIM) {
            tso->isFull = true;
        }
    }
}

/* Transforms a time series observation into an aggregated observation,
 * by taking the average of all x, y and z values
 */
void transform(TimeSeriesObservation tso, AggregatedObservation *out) {
    int i;
    double x = 0.0, y = 0.0, z = 0.0;

    for(i = 0; i < TIME_SERIES_OBSERVATION_DIM; i+=3) {
        x += tso.observation[i];
        y += tso.observation[i+1];
        z += tso.observation[i+2];
    }

    out->observation[0] = x / TIME_SERIES_VECTORS_AMOUNT;
    out->observation[1] = y / TIME_SERIES_VECTORS_AMOUNT;
    out->observation[2] = z / TIME_SERIES_VECTORS_AMOUNT;
}
