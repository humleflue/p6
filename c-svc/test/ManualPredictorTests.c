#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CuTest/CuTest.h"
#include "../manualPredictor.h"


/* The name of your test should consist of three parts:
	- The name of the method being tested.
	- The scenario under which it's being tested.
	- The expected behavior when the scenario is invoked.
*/

void manualPredictor_givenStationaryPointAndDrivingVsStationary_shouldReturnNegativeValue(CuTest* tc)
{
	/* Arrange */
    double vectorA[3] = {1.0, 2.0,  1.0};

	/* Act */
    char actual = predictPoint(vectorA, HYPER_PLANES[0]);

	/* Assert */
	CuAssertTrue(tc, actual == STATIONARY);
}

void manualPredictor_givenStationaryPointAndStationaryVsUsing_shouldReturnPositiveValue(CuTest* tc)
{
	/* Arrange */
    double vectorA[3] = {1.0, 2.0,  1.0};

	/* Act */
    double actual = predictPoint(vectorA, HYPER_PLANES[3]);

	/* Assert */
	CuAssertTrue(tc, actual == STATIONARY);
}


CuSuite* CuGetManualPredictorSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, manualPredictor_givenStationaryPointAndDrivingVsStationary_shouldReturnNegativeValue);
	SUITE_ADD_TEST(suite, manualPredictor_givenStationaryPointAndStationaryVsUsing_shouldReturnPositiveValue);

	return suite;
}
