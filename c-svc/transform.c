#include "transform.h"

void transform(Observation *o, double newVector[3]) {
    int i = o->_currentIndex;
    
    assert(!o->isFull);
    
    o->observation[i  ] = newVector[0];
    o->observation[i+1] = newVector[1];
    o->observation[i+2] = newVector[2];
    
    o->_currentIndex += 3;

    if(o->_currentIndex == OBSERVATION_DIM) {
        o->isFull = true;
    }
}