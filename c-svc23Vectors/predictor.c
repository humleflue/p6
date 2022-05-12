#include "predictor.h"

const HyperPlane HYPER_PLANES[HYPER_PLANES_LENGTH] = {
    {DRIVING, STATIONARY, { 0.19360316, -0.05755878,  0.06869084}, -2.11173355},
    {DRIVING, USING,      {-0.01926972, -0.0473883,   0.00589928},  2.78350823},
    {DRIVING, WALKING,    {-0.03895607, -0.0069259,   0.00745679},  3.23086372},
    {STATIONARY, USING,   {-0.14289515,  0.02128519, -0.01012966},  1.80626325},
    {STATIONARY, WALKING, {-0.04405645,  0.01245427, -0.00702321},  2.26081931},
    {USING, WALKING,      {-0.01216422,  0.04764652,  0.00791857}, -1.25052248},
};

const HyperPlane* lookupHyperPlane(char label1, char label2) { 
    bool match = false;
    int i = 0;
    const HyperPlane *hyperPlane;

    while(!match && i < LABELS_AMOUNT) {
        hyperPlane = &HYPER_PLANES[i];

        if(hyperPlane->label1 == label1 && hyperPlane->label2 == label2) {
            match = true;
        }
        else {
            i++;
        }
    }

    if(hyperPlane->label1 != label1 || hyperPlane->label2 != label2) {
        return NULL;
    }
    return &HYPER_PLANES[i];
}

/* Helper function */
PredictionScore* lookupScore(char label, const PredictionScore predictionScores[LABELS_AMOUNT]) {
    const PredictionScore *result;
    PredictionScore predictionScore;
    bool match = false;
    int i = 0;

    while(!match && i < LABELS_AMOUNT) {
        predictionScore = predictionScores[i];

        if(predictionScore.label == label) {
            match = true;
        }
        else {
            i++;
        }
    }

    result = &predictionScores[i];
    if(result->label != label) {
        result = NULL;
    }
    return (PredictionScore *)result;
}

char predictPoint(SampledObservation obs, const HyperPlane *hyperPlane) {
    SampledObservation hyperPlaneAsObservation = sampledObservationConstructor(hyperPlane->vector);
    int result = linearKernel(obs, hyperPlaneAsObservation) + hyperPlane->intercept;
    return result < 0 ? hyperPlane->label2 : hyperPlane->label1;
}

/* Helper function */
void countUpScore(char label, PredictionScore predictionScores[LABELS_AMOUNT]) {
    PredictionScore *predictionScore = lookupScore(label, predictionScores);
    predictionScore->score += 1;
}

/* Helper function */
PredictionScore* getHighestScore(const PredictionScore predictionScores[LABELS_AMOUNT]) {
    int i;
    const PredictionScore *highestPredictionScore = &predictionScores[0];
    /* Used later because we prefer to return stationary */
    PredictionScore *stationaryPredictionScore = lookupScore(STATIONARY, predictionScores);

    /* Start loop from 1, as we initialized highestPredictionScore to the first index */
    for(i = 1; i < LABELS_AMOUNT; i++) {
        highestPredictionScore = predictionScores[i].score > highestPredictionScore->score ? &predictionScores[i] : highestPredictionScore;
    }

    /* Prefer to return stationary */
    if(stationaryPredictionScore->score == highestPredictionScore->score)
        return stationaryPredictionScore;
    else    
        return (PredictionScore*)highestPredictionScore;
}

void gatherPredictionScores(SampledObservation obs, PredictionScore predictionScores[LABELS_AMOUNT]) {
    int i;
    char prediction;

    for(i = 0; i < HYPER_PLANES_LENGTH; i++) {
        prediction = predictPoint(obs, &HYPER_PLANES[i]);
        countUpScore(prediction, predictionScores);
    }
}

char predict(SampledObservation obs) {
    PredictionScore predictionScores[LABELS_AMOUNT] = {
        { DRIVING, 0 },
        { STATIONARY, 0 },
        { USING, 0 },
        { WALKING, 0 },
    };
    gatherPredictionScores(obs, predictionScores);
    return getHighestScore(predictionScores)->label;   
}