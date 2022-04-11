#include "transform.h"

void addVectorToObservation(Observation *o, double newVector[3]) {
    int i = o->_currentIndex;
    
    if(!o->isFull) {
        o->observation[i  ] = newVector[0];
        o->observation[i+1] = newVector[1];
        o->observation[i+2] = newVector[2];
        
        o->_currentIndex += 3;

        if(o->_currentIndex == OBSERVATION_DIM) {
            o->isFull = true;
        }
    }
}

/* JUST A MOCKED SHELL */
TransformedObservation transform(Observation o) {
    TransformedObservation res;

    res.observation[0] = o.observation[0];
    res.observation[1] = o.observation[1];
    res.observation[2] = o.observation[2];

    return res;
}