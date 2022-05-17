#include "transform.h"
#include "math.h"

/* Adds the x, y and z from newVector to the observation array in the tso,
 * If the tso.observation array is full we do nothing
 * Note: tso is both input and output param 
 * WARNING: This function will FAIL if the tso object's _currentIndex is not initialized to 0 - use TIME_SERIES_OBSERVATION_INIT for this.
 */
void addVectorToTimeSeriesObservation(TimeSeriesObservation *tso, int newVector[ACCELEROMETOR_VECTOR_DIM]) {
    int i = tso->_currentIndex,
        j;
    
    if(!tso->isFull) {
        for(j = 0; j < ACCELEROMETOR_VECTOR_DIM; j++) {
            tso->observation[i+j] = newVector[j];
        }
        
        tso->_currentIndex += ACCELEROMETOR_VECTOR_DIM;

        if(tso->_currentIndex == TIME_SERIES_OBSERVATION_DIM) {
            tso->isFull = true;
        }
    }
}

/* Transforms a time series observation into an aggregated observation,
 * by taking the average of all x, y and z values
 */
void transform(TimeSeriesObservation tso, SampledObservation *out) {
    int i,
        x = 0.0, y = 0.0, z = 0.0;

    for(i = 0; i < TIME_SERIES_OBSERVATION_DIM; i+=3) {
        x += tso.observation[i];
        y += tso.observation[i+1];
        z += tso.observation[i+2];
    }

    out->observation[0] = x / TIME_SERIES_VECTORS_AMOUNT;
    out->observation[1] = y / TIME_SERIES_VECTORS_AMOUNT;
    out->observation[2] = z / TIME_SERIES_VECTORS_AMOUNT;
}

void extractXYZ(TimeSeriesObservation tso, int x[TIME_SERIES_VECTORS_AMOUNT], int y[TIME_SERIES_VECTORS_AMOUNT], int z[TIME_SERIES_VECTORS_AMOUNT]){
    int i, j = 0;
    for(i = 0; i < TIME_SERIES_OBSERVATION_DIM; i+=3) {
        x[j] = tso.observation[i];
        y[j] = tso.observation[i+1];
        z[j] = tso.observation[i+2];
        j++;
    }
}

void transformTo23Dimensions(TimeSeriesObservation tso, SampledObservation *out){
    int x[TIME_SERIES_VECTORS_AMOUNT];
    int y[TIME_SERIES_VECTORS_AMOUNT];
    int z[TIME_SERIES_VECTORS_AMOUNT];
    extractXYZ(tso, x, y, z);
    //np.mean()
    out->observation[0] = mean(x, ACCELEROMETOR_VECTOR_DIM);
    out->observation[1] = mean(y, ACCELEROMETOR_VECTOR_DIM);
    out->observation[2] = mean(z, ACCELEROMETOR_VECTOR_DIM);
    
    //np.max()
    out->observation[3] = getBiggestNumber(x, ACCELEROMETOR_VECTOR_DIM);
    out->observation[4] = getBiggestNumber(y, ACCELEROMETOR_VECTOR_DIM);
    out->observation[5] = getBiggestNumber(z, ACCELEROMETOR_VECTOR_DIM);
    
    //np.min()
    out->observation[6] = getSmallestNumber(x, ACCELEROMETOR_VECTOR_DIM);
    out->observation[7] = getSmallestNumber(y, ACCELEROMETOR_VECTOR_DIM);
    out->observation[8] = getSmallestNumber(z, ACCELEROMETOR_VECTOR_DIM);
    
    //sum([abs(num) for num in x])
    out->observation[9] = absSum(x, ACCELEROMETOR_VECTOR_DIM);
    out->observation[10] = absSum(y, ACCELEROMETOR_VECTOR_DIM);
    out->observation[11] = absSum(z, ACCELEROMETOR_VECTOR_DIM);

    //np.mean([abs(num) for num in x])
    out->observation[12]  = absMean(x, ACCELEROMETOR_VECTOR_DIM);
    out->observation[13] = absMean(y, ACCELEROMETOR_VECTOR_DIM);
    out->observation[14] = absMean(z, ACCELEROMETOR_VECTOR_DIM);
    
    //np.std([abs(num) for num in x])
    out->observation[15] = absStd(x, ACCELEROMETOR_VECTOR_DIM);
    out->observation[16] = absStd(y, ACCELEROMETOR_VECTOR_DIM);
    out->observation[17] = absStd(z, ACCELEROMETOR_VECTOR_DIM);

    //np.max(row)
    out->observation[18] = getBiggestNumberInRow(x, y, z, ACCELEROMETOR_VECTOR_DIM);

    //np.min(row)
    out->observation[19] = getSmallestNumberInRow(x, y, z, ACCELEROMETOR_VECTOR_DIM);

    //sum([abs(num) for num in row])
    out->observation[20] = absSum(tso.observation, TIME_SERIES_OBSERVATION_DIM);
 
    //np.mean([abs(num) for num in row])
    out->observation[21] = absMean(tso.observation, TIME_SERIES_OBSERVATION_DIM);

    //np.std([abs(num) for num in row])
    out->observation[22] = absStd(tso.observation, TIME_SERIES_OBSERVATION_DIM);
}
