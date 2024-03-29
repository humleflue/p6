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

/* Lookup Hyper Plane START */
void lookupHyperPlane_givenDrivingStationary_shouldGetDrivingStationary(CuTest* tc)
{
	/* Act */
    const HyperPlane *actual = lookupHyperPlane(DRIVING, STATIONARY);

	/* Assert */
	CuAssertTrue(tc, actual->label1 == DRIVING);
	CuAssertTrue(tc, actual->label2 == STATIONARY);
}

void lookupHyperPlane_givenStationaryUsing_shouldGetStationaryUsing(CuTest* tc)
{
	/* Act */
    const HyperPlane *actual = lookupHyperPlane(STATIONARY, USING);

	/* Assert */
	CuAssertTrue(tc, actual->label1 == STATIONARY);
	CuAssertTrue(tc, actual->label2 == USING);
}

void lookupHyperPlane_givenInvalidInvalid_shouldGetNULL(CuTest* tc)
{
	/* Act */
    const HyperPlane *actual = lookupHyperPlane('a', 'b');

	/* Assert */
	CuAssertPtrEquals(tc, NULL, (HyperPlane *)actual);
}

void lookupHyperPlane_givenValidInvalid_shouldGetNULL(CuTest* tc)
{
	/* Act */
    const HyperPlane *actual = lookupHyperPlane(STATIONARY, 'a');

	/* Assert */
	CuAssertPtrEquals(tc, NULL, (HyperPlane *)actual);
}

void lookupHyperPlane_givenInvalidValid_shouldGetNULL(CuTest* tc)
{
	/* Act */
    const HyperPlane *actual = lookupHyperPlane('a', STATIONARY);

	/* Assert */
	CuAssertPtrEquals(tc, NULL, (HyperPlane *)actual);
}
/* Lookup Hyper Plane END */

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
    SampledObservation obs = {{1.0, 2.0,  1.0}};
	const HyperPlane *hyperPlane = lookupHyperPlane(DRIVING, STATIONARY);

	/* Act */
    char actual = predictPoint(obs, hyperPlane);

	/* Assert */
	CuAssertTrue(tc, actual == STATIONARY);
}

void predictPoint_givenStationaryPointAndStationaryVsUsing_shouldReturnPositiveValue(CuTest* tc)
{
	/* Arrange */
    SampledObservation obs = {{1.0, 2.0,  1.0}};
	const HyperPlane *hyperPlane = lookupHyperPlane(STATIONARY, USING);

	/* Act */
    char actual = predictPoint(obs, hyperPlane);

	/* Assert */
	CuAssertTrue(tc, actual == STATIONARY);
}
/* Predict Point END */

/* Get Highest Score START */
void getHighestScore_givenDrivingIsHighestScore_shouldReturnDriving(CuTest* tc)
{
	/* Arrange */
    PredictionScore predictionScores[LABELS_AMOUNT] = {
        { DRIVING, 3 },
        { STATIONARY, 2 },
        { USING, 1 },
        { WALKING, 0 },
    };

	/* Act */
    PredictionScore *actual = getHighestScore(predictionScores);

	/* Assert */
	CuAssertPtrEquals(tc, &predictionScores[0] ,actual);
}

void getHighestScore_givenTieBreakerBetweenStationaryAndOther_shouldReturnStationary(CuTest* tc)
{
	/* Arrange */
    PredictionScore predictionScores[LABELS_AMOUNT] = {
        { DRIVING, 2 },
        { STATIONARY, 2 },
        { USING, 2 },
        { WALKING, 0 },
    };

	/* Act */
    PredictionScore *actual = getHighestScore(predictionScores);

	/* Assert */
	CuAssertPtrEquals(tc, &predictionScores[1] ,actual);
}

void getHighestScore_givenTieBreakerNotIncludingStationary_shouldNotReturnStationary(CuTest* tc)
{
	/* Arrange */
    PredictionScore predictionScores[LABELS_AMOUNT] = {
        { DRIVING, 2 },
        { STATIONARY, 0 },
        { USING, 2 },
        { WALKING, 2 },
    };

	/* Act */
    PredictionScore *actual = getHighestScore(predictionScores);

	/* Assert */
	CuAssertTrue(tc, actual->label != STATIONARY);
}
/* Get Highest Score END */

/* Get Prediction Scores START */
void getPredictionScores_givenStationaryPoint_shouldGetSameScoresAsInPython(CuTest* tc)
{
	/* Arrange */
    SampledObservation obs = {{1.0, 2.0,  1.0}};
	PredictionScore predictionScores[LABELS_AMOUNT] = {
        { DRIVING, 0 },
        { STATIONARY, 0 },
        { USING, 0 },
        { WALKING, 0 },
    };

	/* Act */
    gatherPredictionScores(obs, predictionScores);

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
    SampledObservation obs = {{1.0, 2.0,  1.0}};

	/* Act */
    char actual = predict(obs);

	/* Assert */
	CuAssertTrue(tc, actual == STATIONARY);
}
/* Predict END */

CuSuite* CuGetPredictorSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	/* Lookup Hyper Plane */
	SUITE_ADD_TEST(suite, lookupHyperPlane_givenDrivingStationary_shouldGetDrivingStationary);
	SUITE_ADD_TEST(suite, lookupHyperPlane_givenStationaryUsing_shouldGetStationaryUsing);
	SUITE_ADD_TEST(suite, lookupHyperPlane_givenInvalidInvalid_shouldGetNULL);
	SUITE_ADD_TEST(suite, lookupHyperPlane_givenValidInvalid_shouldGetNULL);
	SUITE_ADD_TEST(suite, lookupHyperPlane_givenInvalidValid_shouldGetNULL);
	/* Lookup Score */
	SUITE_ADD_TEST(suite, lookupScore_givenStationary_shouldGetStationary);
	SUITE_ADD_TEST(suite, lookupScore_givenDriving_shouldGetDriving);
	SUITE_ADD_TEST(suite, lookupScore_givenUsing_shouldGetUsing);
	SUITE_ADD_TEST(suite, lookupScore_givenWalking_shouldGetWalking);
	SUITE_ADD_TEST(suite, lookupScore_givenSomeOtherChar_shouldGetNULL);
	/* Predict Point */
	SUITE_ADD_TEST(suite, predictPoint_givenStationaryPointAndDrivingVsStationary_shouldReturnNegativeValue);
	SUITE_ADD_TEST(suite, predictPoint_givenStationaryPointAndStationaryVsUsing_shouldReturnPositiveValue);
	/* Get Highest Score */
	SUITE_ADD_TEST(suite, getHighestScore_givenDrivingIsHighestScore_shouldReturnDriving);
	SUITE_ADD_TEST(suite, getHighestScore_givenTieBreakerBetweenStationaryAndOther_shouldReturnStationary);
	SUITE_ADD_TEST(suite, getHighestScore_givenTieBreakerNotIncludingStationary_shouldNotReturnStationary);
	/* Get Prediction Scores */
	SUITE_ADD_TEST(suite, getPredictionScores_givenStationaryPoint_shouldGetSameScoresAsInPython);
	/* Predict */
	SUITE_ADD_TEST(suite, predict_givenStationaryPoint_shouldPredictStationary);

	return suite;
}
