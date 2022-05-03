#ifndef PREDICTOR_H
#define PREDICTOR_H

#define DRIVING 'd'
#define STATIONARY 's'
#define USING 'u'
#define WALKING 'w'
#define HYPER_PLANES_LENGTH 6
#define LABELS_AMOUNT 4
#define NULL ((void *)0)

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

extern const HyperPlane HYPER_PLANES[HYPER_PLANES_LENGTH];

PredictionScore* lookupScore(char label, PredictionScore predictionScores[LABELS_AMOUNT]);
char predictPoint(double pointToPredict[3], HyperPlane hyperPlane);
void getPredictionScores(double pointToPredict[3], PredictionScore predictionScores[LABELS_AMOUNT]);
char predict(double pointToPredict[3]);

#endif /* END OF PREDICTOR_H */
