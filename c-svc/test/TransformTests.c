#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CuTest/CuTest.h"
#include "../transform.h"

/* The name of your test should consist of three parts:
	- The name of the method being tested.
	- The scenario under which it's being tested.
	- The expected behavior when the scenario is invoked.
*/

void addVectorToTimeSeriesObservation_tryToStackSmash_shouldNotAffectStack(CuTest* tc)
{
	/* Arrange */
	TimeSeriesObservation o;
	double newVector[3], arbitraryDouble = 0.42;
	int i;

	o._currentIndex = 0;
	newVector[0] = arbitraryDouble;
	newVector[1] = arbitraryDouble;
	newVector[2] = arbitraryDouble;

	/* Act */
	/* We try to add one more vector (+1), than there's space for */
	for(i = 0; i < TIME_SERIES_OBSERVATION_DIM / 3 + 1; i++) {
		addVectorToTimeSeriesObservation(&o, newVector);
	}

	/* Assert */
	CuAssertTrue(tc, o.observation[TIME_SERIES_OBSERVATION_DIM] != arbitraryDouble);
	CuAssertTrue(tc, o.isFull);
}

void addVectorToTimeSeriesObservation_fillUpObservations_shouldFillUpLastIndex(CuTest* tc)
{
	/* Arrange */
	TimeSeriesObservation o;
	double newVector[3], arbitraryDouble = 0.42;
	int i;

	o._currentIndex = 0;
	newVector[0] = arbitraryDouble;
	newVector[1] = arbitraryDouble;
	newVector[2] = arbitraryDouble;

	/* Act */
	for(i = 0; i < TIME_SERIES_OBSERVATION_DIM / 3; i++) {
		addVectorToTimeSeriesObservation(&o, newVector);
	}

	/* Assert */
	CuAssertTrue(tc, o.observation[TIME_SERIES_OBSERVATION_DIM - 1] == arbitraryDouble);
	CuAssertTrue(tc, o.isFull);
}

void transform_transformTso_xYZShouldBeAverage(CuTest* tc)
{
	/* Arrange */
	TimeSeriesObservation tso;
	AggregatedObservation ao;
	int i;
	double expected = 3.1;

	/* We fill up the tso's observations with the expected value,
	   which means that the average will always be the expected value */
	for(i = 0; i < TIME_SERIES_OBSERVATION_DIM; i++) {
		tso.observation[i] = expected;
	}

	/* Act */
	transform(tso, &ao);

	/* Assert */
	CuAssertDblEquals(tc, expected, ao.observation[0], 0.01);
	CuAssertDblEquals(tc, expected, ao.observation[1], 0.01);
	CuAssertDblEquals(tc, expected, ao.observation[2], 0.01);
}


CuSuite* CuGetSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, addVectorToTimeSeriesObservation_tryToStackSmash_shouldNotAffectStack);
	SUITE_ADD_TEST(suite, addVectorToTimeSeriesObservation_fillUpObservations_shouldFillUpLastIndex);

	SUITE_ADD_TEST(suite, transform_transformTso_xYZShouldBeAverage);

	return suite;
}
