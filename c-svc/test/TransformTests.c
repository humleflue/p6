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

void addVectorToObservation_tryToStackSmash_shouldNotAffectStack(CuTest* tc)
{
	/* Arrange */
	Observation o;
	double newVector[3], arbitraryDouble = 0.42;
	int i;

	o._currentIndex = 0;
	newVector[0] = arbitraryDouble;
	newVector[1] = arbitraryDouble;
	newVector[2] = arbitraryDouble;

	/* Act */
	/* We try to add one more vector (+1), than there's space for */
	for(i = 0; i < OBSERVATION_DIM / 3 + 1; i++) {
		addVectorToObservation(&o, newVector);
	}

	/* Assert */
	CuAssertTrue(tc, o.observation[OBSERVATION_DIM] != arbitraryDouble);
}

void addVectorToObservation_fillUpObservations_shouldFillUpLastIndex(CuTest* tc)
{
	/* Arrange */
	Observation o;
	double newVector[3], arbitraryDouble = 0.42;
	int i;

	o._currentIndex = 0;
	newVector[0] = arbitraryDouble;
	newVector[1] = arbitraryDouble;
	newVector[2] = arbitraryDouble;

	/* Act */
	for(i = 0; i < OBSERVATION_DIM / 3; i++) {
		addVectorToObservation(&o, newVector);
	}

	/* Assert */
	CuAssertTrue(tc, o.observation[OBSERVATION_DIM - 1] == arbitraryDouble);
}

CuSuite* CuGetSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, addVectorToObservation_tryToStackSmash_shouldNotAffectStack);
	SUITE_ADD_TEST(suite, addVectorToObservation_fillUpObservations_shouldFillUpLastIndex);

	return suite;
}