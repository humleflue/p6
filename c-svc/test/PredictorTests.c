#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CuTest/CuTest.h"
#include "../predictor.h"


/* The name of your test should consist of three parts:
	- The name of the method being tested.
	- The scenario under which it's being tested.
	- The expected behavior when the scenario is invoked.
*/

/* Lookup Score START */
void lookupScore_givenStationary_shouldGetStationary(CuTest* tc)
{
	/* Arrange */
	PredictionScore predictionScores[LABELS_AMOUNT] = {
        { DRIVING, 0 },
        { STATIONARY, 0 },
        { USING, 0 },
        { WALKING, 0 },
    };

	/* Act */
    PredictionScore *actual = lookupScore(STATIONARY, predictionScores);

	/* Assert */
	CuAssertTrue(tc, actual->label == STATIONARY);
}

void lookupScore_givenDriving_shouldGetDriving(CuTest* tc)
{
	/* Arrange */
	PredictionScore predictionScores[LABELS_AMOUNT] = {
        { DRIVING, 0 },
        { STATIONARY, 0 },
        { USING, 0 },
        { WALKING, 0 },
    };

	/* Act */
    PredictionScore *actual = lookupScore(DRIVING, predictionScores);

	/* Assert */
	CuAssertTrue(tc, actual->label == DRIVING);
}

void lookupScore_givenUsing_shouldGetUsing(CuTest* tc)
{
	/* Arrange */
	PredictionScore predictionScores[LABELS_AMOUNT] = {
        { DRIVING, 0 },
        { STATIONARY, 0 },
        { USING, 0 },
        { WALKING, 0 },
    };

	/* Act */
    PredictionScore *actual = lookupScore(USING, predictionScores);

	/* Assert */
	CuAssertTrue(tc, actual->label == USING);
}

void lookupScore_givenWalking_shouldGetWalking(CuTest* tc)
{
	/* Arrange */
	PredictionScore predictionScores[LABELS_AMOUNT] = {
        { DRIVING, 0 },
        { STATIONARY, 0 },
        { USING, 0 },
        { WALKING, 0 },
    };

	/* Act */
    PredictionScore *actual = lookupScore(WALKING, predictionScores);

	/* Assert */
	CuAssertTrue(tc, actual->label == WALKING);
}

void lookupScore_givenSomeOtherChar_shouldGetNULL(CuTest* tc)
{
	/* Arrange */
	PredictionScore predictionScores[LABELS_AMOUNT] = {
        { DRIVING, 0 },
        { STATIONARY, 0 },
        { USING, 0 },
        { WALKING, 0 },
    };

	/* Act */
    PredictionScore *actual = lookupScore('a', predictionScores);

	/* Assert */
	CuAssertPtrEquals(tc, NULL, actual);
}
/* Lookup Score END */

/* Predict Point START */
void predictPoint_givenStationaryPointAndDrivingVsStationary_shouldReturnNegativeValue(CuTest* tc)
{
	/* Arrange */
    double vectorA[3] = {1.0, 2.0,  1.0};

	/* Act */
    char actual = predictPoint(vectorA, HYPER_PLANES[0]);

	/* Assert */
	CuAssertTrue(tc, actual == STATIONARY);
}

void predictPoint_givenStationaryPointAndStationaryVsUsing_shouldReturnPositiveValue(CuTest* tc)
{
	/* Arrange */
    double vectorA[3] = {1.0, 2.0,  1.0};

	/* Act */
    char actual = predictPoint(vectorA, HYPER_PLANES[3]);

	/* Assert */
	CuAssertTrue(tc, actual == STATIONARY);
}
/* Predict Point END */

/* Get Prediction Scores START */
void getPredictionScores_givenStationaryPoint_shouldGetSameScoresAsInPython(CuTest* tc)
{
	/* Arrange */
    double vector[3] = {1.0, 2.0,  1.0};
	PredictionScore predictionScores[LABELS_AMOUNT] = {
        { DRIVING, 0 },
        { STATIONARY, 0 },
        { USING, 0 },
        { WALKING, 0 },
    };

	/* Act */
    getPredictionScores(vector, predictionScores);

	/* Assert */
	CuAssertIntEquals(tc, 2, lookupScore(DRIVING, predictionScores)->score);
	CuAssertIntEquals(tc, 3, lookupScore(STATIONARY, predictionScores)->score);
	CuAssertIntEquals(tc, 0, lookupScore(USING, predictionScores)->score);
	CuAssertIntEquals(tc, 1, lookupScore(WALKING, predictionScores)->score);
}
/* Get Prediction Scores END */

/* Predict START */
void predict_givenStationaryPoint_shouldPredictStationary(CuTest* tc)
{
	/* Arrange */
    double vector[3] = {1.0, 2.0,  1.0};

	/* Act */
    double actual = predict(vector);

	/* Assert */
	CuAssertTrue(tc, actual == STATIONARY);
}
/* Predict END */

CuSuite* CuGetPredictorSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	/* Lookup Score */
	SUITE_ADD_TEST(suite, lookupScore_givenStationary_shouldGetStationary);
	SUITE_ADD_TEST(suite, lookupScore_givenDriving_shouldGetDriving);
	SUITE_ADD_TEST(suite, lookupScore_givenUsing_shouldGetUsing);
	SUITE_ADD_TEST(suite, lookupScore_givenWalking_shouldGetWalking);
	SUITE_ADD_TEST(suite, lookupScore_givenSomeOtherChar_shouldGetNULL);
	/* Predict Point */
	SUITE_ADD_TEST(suite, predictPoint_givenStationaryPointAndDrivingVsStationary_shouldReturnNegativeValue);
	SUITE_ADD_TEST(suite, predictPoint_givenStationaryPointAndStationaryVsUsing_shouldReturnPositiveValue);
	/* Get Prediction Scores */
	SUITE_ADD_TEST(suite, getPredictionScores_givenStationaryPoint_shouldGetSameScoresAsInPython);
	/* Predict */
	SUITE_ADD_TEST(suite, predict_givenStationaryPoint_shouldPredictStationary);

	return suite;
}
