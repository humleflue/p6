#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CuTest/CuTest.h"
#include "../math.h"


/* The name of your test should consist of three parts:
	- The name of the method being tested.
	- The scenario under which it's being tested.
	- The expected behavior when the scenario is invoked.
*/

void dotProduct3dVector_givenVectorsOfIntegers_expectsTheCorrectDotProduct(CuTest* tc)
{
	/* Arrange */
    double vectorA[3] = {9.0, 2.0,  7.0};
    double vectorB[3] = {4.0, 8.0, 10.0};

	/* Act */
    double actual = dotProduct3dVectors(vectorA, vectorB);


	/* Assert */
	CuAssertDblEquals(tc, 122.0, actual, 0.1);
}

void dotProduct3dVector_givenVectorsOfDoubles_expectsTheCorrectDotProduct(CuTest* tc)
{
	/* Arrange */
    double vectorA[3] = {9.123, 2.1,  7.1};
    double vectorB[3] = {4.1, 8.987, 10.1};

	/* Act */
    double actual = dotProduct3dVectors(vectorA, vectorB);

	/* Assert */
	CuAssertDblEquals(tc,  127.987, actual, 0.01);
}


CuSuite* CuGetMathSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, dotProduct3dVector_givenVectorsOfIntegers_expectsTheCorrectDotProduct);
	SUITE_ADD_TEST(suite, dotProduct3dVector_givenVectorsOfDoubles_expectsTheCorrectDotProduct);

	return suite;
}
