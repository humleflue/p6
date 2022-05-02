#ifndef MANUAL_PREDICTOR_H
#define MANUAL_PREDICTOR_H

#define DRIVING 'd'
#define STATIONARY 's'
#define USING 'u'
#define WALKING 'w'
#define HYPER_PLANES_LENGTH 6

#include "math.h"


typedef struct HyperPlane
{
    char label1;
    char label2;
    double vector[3];
    double intercept; 
} HyperPlane;

extern HyperPlane HYPER_PLANES[HYPER_PLANES_LENGTH];

double predict(double pointToPredict[3], HyperPlane hyperPlane);

#endif /*Ending Manual Predictor */
