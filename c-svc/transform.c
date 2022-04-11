#include "transform.h"

/* Adds the x, y and z from newVector to the observation array in the tso,
 * If the tso.observation array is full we do nothing
 * Note: tso is both input and output param 
 */
void addVectorToTimeSeriesObservation(TimeSeriesObservation *tso, double newVector[VECTOR_DIM]) {
    int i = tso->_currentIndex;
    
    if(!tso->isFull) {
        tso->observation[i  ] = newVector[0];
        tso->observation[i+1] = newVector[1];
        tso->observation[i+2] = newVector[2];
        
        tso->_currentIndex += 3;

        if(tso->_currentIndex == TIME_SERIES_OBSERVATION_DIM) {
            tso->isFull = true;
        }
    }
}

/* Transforms a time series observation into an aggregated observation,
 * by taking the average of all x, y and z values
 */
void transform(TimeSeriesObservation o, AggregatedObservation *out) {
    int i;
    double x = 0.0, y = 0.0, z = 0.0;

    for(i = 0; i < TIME_SERIES_OBSERVATION_DIM; i+=3) {
        x += o.observation[i];
        y += o.observation[i+1];
        z += o.observation[i+2];
    }

    out->observation[0] = x / TIME_SERIES_VECTORS_AMOUNT;
    out->observation[1] = y / TIME_SERIES_VECTORS_AMOUNT;
    out->observation[2] = z / TIME_SERIES_VECTORS_AMOUNT;
}
