#ifndef MANUAL_PREDICTOR_H
#define MANUAL_PREDICTOR_H

#define DRIVING 'd'
#define STATIONARY 's'
#define USING 'u'
#define WALKING 'w'
#define HYPER_PLANES_LENGTH 6
#define LABELS_AMOUNT 4

#include "math.h"
#include "bool.h"

typedef struct HyperPlane
{
    char label1;
    char label2;
    double vector[3];
    double intercept; 
} HyperPlane;

typedef struct PredictionScore
{
    char label;
    int score;
} PredictionScore;

extern HyperPlane HYPER_PLANES[HYPER_PLANES_LENGTH];

char predictPoint(double pointToPredict[3], HyperPlane hyperPlane);
char predict(double pointToPredict[3]);

#endif /* END OF MANUAL_PREDICTOR_H */
