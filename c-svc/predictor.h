#ifndef PREDICTOR_H
#define PREDICTOR_H

#define DRIVING 'd'
#define STATIONARY 's'
#define USING 'u'
#define WALKING 'w'
#define HYPER_PLANES_LENGTH 6
#define LABELS_AMOUNT 4
#define NULL ((void *)0)

#include "bool.h"
#include "types.h"
#include "kernels.h"

typedef struct HyperPlane
{
    const char label1;
    const char label2;
    const double vector[3];
    const double intercept; 
} HyperPlane;

typedef struct PredictionScore
{
    char label;
    int score;
} PredictionScore;

extern const HyperPlane HYPER_PLANES[HYPER_PLANES_LENGTH];

const HyperPlane* lookupHyperPlane(char label1, char label2);
PredictionScore* lookupScore(char label, const PredictionScore predictionScores[LABELS_AMOUNT]);
char predictPoint(SampledObservation obs, const HyperPlane *hyperPlane);
PredictionScore* getHighestScore(const PredictionScore predictionScores[LABELS_AMOUNT]);
void gatherPredictionScores(SampledObservation obs, PredictionScore predictionScores[LABELS_AMOUNT]);
char predict(SampledObservation obs);

#endif /* END OF PREDICTOR_H */
