#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CuTest/CuTest.h"
#include "../transform.h"

/*-------------------------------------------------------------------------*
 * Helper functions
 *-------------------------------------------------------------------------*/
void fillArrayWithInts(int size, int vector[size], int value) {
	int i;
	for(i = 0; i < size; i++){
		vector[i] = value;
	}
}


/* The name of your test should consist of three parts:
	- The name of the method being tested.
	- The scenario under which it's being tested.
	- The expected behavior when the scenario is invoked.
*/

void addVectorToTimeSeriesObservation_tryToStackSmash_shouldNotAffectStack(CuTest* tc)
{
	/* Arrange */
	TimeSeriesObservation tso = TIME_SERIES_OBSERVATION_INIT;
	int vector[ACCELEROMETOR_VECTOR_DIM], 
	    arbitraryInt = 42,
		i;

	fillArrayWithInts(ACCELEROMETOR_VECTOR_DIM, vector, arbitraryInt);

	/* Act */
	/* We try to add one more vector (+1), than there's space for */
	for(i = 0; i < TIME_SERIES_OBSERVATION_DIM / 3 + 1; i++) {
		addVectorToTimeSeriesObservation(&tso, vector);
	}

	/* Assert */
	CuAssertTrue(tc, tso.observation[TIME_SERIES_OBSERVATION_DIM] != arbitraryInt);
	CuAssertTrue(tc, tso.isFull);
}

void addVectorToTimeSeriesObservation_fillUpObservations_shouldFillUpLastIndex(CuTest* tc)
{
	/* Arrange */
	TimeSeriesObservation tso = TIME_SERIES_OBSERVATION_INIT;
	int vector[ACCELEROMETOR_VECTOR_DIM], 
		arbitraryInt = 42,
		i;

	fillArrayWithInts(ACCELEROMETOR_VECTOR_DIM, vector, arbitraryInt);

	/* Act */
	for(i = 0; i < TIME_SERIES_OBSERVATION_DIM / 3; i++) {
		addVectorToTimeSeriesObservation(&tso, vector);
	}

	/* Assert */
	CuAssertTrue(tc, tso.observation[TIME_SERIES_OBSERVATION_DIM - 1] == arbitraryInt);
	CuAssertTrue(tc, tso.isFull);
}

void transform_transformTso_xYZShouldBeAverage(CuTest* tc)
{
	/* Arrange */
	TimeSeriesObservation tso = TIME_SERIES_OBSERVATION_INIT;
	SampledObservation ao;
	int i;
	int expected = 3;

	/* We fill up the tso's observations with the expected value,
	   which means that the average will always be the expected value */
	fillArrayWithInts(TIME_SERIES_OBSERVATION_DIM, tso.observation, expected);

	/* Act */
	transform(tso, &ao);

	/* Assert */
	CuAssertIntEquals(tc, expected, ao.observation[0]);
	CuAssertIntEquals(tc, expected, ao.observation[1]);
	CuAssertIntEquals(tc, expected, ao.observation[2]);
}


CuSuite* CuGetTransformSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, addVectorToTimeSeriesObservation_tryToStackSmash_shouldNotAffectStack);
	SUITE_ADD_TEST(suite, addVectorToTimeSeriesObservation_fillUpObservations_shouldFillUpLastIndex);

	SUITE_ADD_TEST(suite, transform_transformTso_xYZShouldBeAverage);

	return suite;
}
