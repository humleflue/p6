#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CuTest/CuTest.h"
#include "../math.h"

#define TIME_SERIES_OBSERVATION_INIT_108_VALUES {1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3}

/* The name of your test should consist of three parts:
	- The name of the method being tested.
	- The scenario under which it's being tested.
	- The expected behavior when the scenario is invoked.
*/

void dotProduct3dVector_givenVectorsOfIntegers_expectsTheCorrectDotProduct(CuTest* tc)
{
	/* Arrange */
    int vectorA[3] = {9, 2,  7};
    int vectorB[3] = {4, 8, 10};

	/* Act */
    int actual = dotProduct3dVectors(vectorA, vectorB);


	/* Assert */
	CuAssertIntEquals(tc, 122, actual);
}

/*
	void dotProduct3dVector_givenVectorsOfDoubles_expectsTheCorrectDotProduct(CuTest* tc)
	{
		* Arrange *
		double vectorA[3] = {9.123, 2.1,  7.1};
		double vectorB[3] = {4.1, 8.987, 10.1};

		* Act *
		double actual = dotProduct3dVectors(vectorA, vectorB);

		* Assert *
		CuAssertDblEquals(tc,  127.987, actual, 0.01);
	}
*/

void getBiggestNumber_givenArrayOfNegativeNumbers_ShouldReturnNumberWithLowestNegativeValue(CuTest* tc)
{
	/* Arrange */
    double numbers[TIME_SERIES_VECTORS_AMOUNT] = {-5,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3};
	double expected = -5;

	/* Act */
    double actual = getBiggestNumber(numbers, TIME_SERIES_VECTORS_AMOUNT);


	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void getBiggestNumber_givenArrayOfPositiveNumbers_ShouldReturnNumberWithHighestPositiveValue(CuTest* tc)
{
	/* Arrange */
    double numbers[TIME_SERIES_VECTORS_AMOUNT] = {5,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3};
	double expected = 5;

	/* Act */
    double actual = getBiggestNumber(numbers, TIME_SERIES_VECTORS_AMOUNT);


	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void getBiggestNumber_givenArrayOfNegativeAndPositiveNumbers_ShouldReturnNumberWithBiggestAbosluteValue(CuTest* tc)
{
	/* Arrange */
    double numbers[TIME_SERIES_VECTORS_AMOUNT] = {4,2,3,1,2,3,1,2,3,1,2,3,1,2,3,-5,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3};
	double expected = -5;

	/* Act */
    double actual = getBiggestNumber(numbers, TIME_SERIES_VECTORS_AMOUNT);


	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void getSmallestNumber_givenArrayOfNegativeNumbers_ShouldReturnNumberWithHighestNegativeValue(CuTest* tc)
{
	/* Arrange */
    double numbers[TIME_SERIES_VECTORS_AMOUNT] = {-5,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-2,-3,-1,-2};
	double expected = -1;

	/* Act */
    double actual = getSmallestNumber(numbers, TIME_SERIES_VECTORS_AMOUNT);


	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void getSmallestNumber_givenArrayOfPositiveNumbers_ShouldReturnNumberWithLowestPositiveValue(CuTest* tc)
{
	/* Arrange */
    double numbers[TIME_SERIES_VECTORS_AMOUNT] = {5,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,3,1,2,3,1,2};
	double expected = 1;

	/* Act */
    double actual = getSmallestNumber(numbers, TIME_SERIES_VECTORS_AMOUNT);


	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void getSmallestNumber_givenArrayOfNegativeAndPositiveNumbers_ShouldReturnNumberWithSmallestAbosluteValue(CuTest* tc)
{
	/* Arrange */
    double numbers[TIME_SERIES_VECTORS_AMOUNT] = {4,2,3,1,2,3,1,2,3,1,2,3,1,2,3,-5,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3,-1,-2,-3};
	double expected = 1;

	/* Act */
    double actual = getSmallestNumber(numbers, TIME_SERIES_VECTORS_AMOUNT);


	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void absMean_givenAllPositives_shouldReturnCorrectMean(CuTest* tc)
{
	/* Arrange */
    double numbers[3] = {1.5, 1.5, 3};
	double expected = 2;

	/* Act */
    double actual = absMean(numbers, 3);


	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void absMean_givenPositiveAndNegativeNumbers_shouldReturnCorrectMean(CuTest* tc)
{
	/* Arrange */
    double numbers[3] = {-1.5, 1.5, -3};
	double expected = 2;

	/* Act */
    double actual = absMean(numbers, 3);


	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void mean_givenAllPositives_shouldReturnCorrectMean(CuTest* tc)
{
	/* Arrange */
    double numbers[3] = {1.5, 1.5, 3};
	double expected = 2;

	/* Act */
    double actual = mean(numbers, 3);


	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void mean_givenPositiveAndNegativeNumbers_shouldReturnCorrectMean(CuTest* tc)
{
	/* Arrange */
    double numbers[3] = {-1.5, 1.5, -3};
	double expected = -1;

	/* Act */
    double actual = mean(numbers, 3);


	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void absSum_givenPositiveAndNegativeNumbers_shouldReturnCorrectSum(CuTest* tc)
{
	/* Arrange */
    double numbers[3] = {-1.5, 1.5, -3};
	double expected = 6;

	/* Act */
    double actual = absSum(numbers, 3);

	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void absSum_givenPositiveNumbers_shouldReturnCorrectSum(CuTest* tc)
{
	/* Arrange */
    double numbers[3] = {1.5, 1.5, 3};
	double expected = 6;

	/* Act */
    double actual = absSum(numbers, 3);

	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void sum_givenPositiveAndNegativeNumbers_shouldReturnCorrectSum(CuTest* tc)
{
	/* Arrange */
    double numbers[3] = {-1.5, 1.5, -3};
	double expected = -3;

	/* Act */
    double actual = sum(numbers, 3);

	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void sum_givenPositiveNumbers_shouldReturnCorrectSum(CuTest* tc)
{
	/* Arrange */
    double numbers[3] = {1.5, 1.5, 3};
	double expected = 6;

	/* Act */
    double actual = sum(numbers, 3);

	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void getBiggestNumberInRow_givenRowWith3Arrays_shouldReturnBiggestValueOfAll(CuTest* tc)
{
	/* Arrange */
    double x[3] = {1.0, 2.0, 3.0};
    double y[3] = {5.0, 4.0, 3.0};
    double z[3] = {2.0, 1.0, 1.0};
	double expected = 5;

	/* Act */
    double actual = getBiggestNumberInRow(x, y, z, 3);

	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void getBiggestNumberInRow_givenRowWith3ArraysWithPositiveAndNegativeNumbers_shouldReturnNumberWithBiggestAbsoluteValue(CuTest* tc)
{
	/* Arrange */
    double x[3] = {-1.0, -2.0, -3.0};
    double y[3] = {-5.0, 4.0, 3.0};
    double z[3] = {-2.0, 1.0, 1.0};
	double expected = -5;

	/* Act */
    double actual = getBiggestNumberInRow(x, y, z, 3);

	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void absVariance_givenArrayOfPositiveNumber_shouldReturnCorrectVariance(CuTest* tc)
{
	/* Arrange */
    double numbers[5] = {600, 470, 170, 430, 300};
	double expected = 21704;

	/* Act */
    double actual = absVariance(numbers, 5);

	/* Assert */
	CuAssertTrue(tc, expected == actual);
}

void absStd_givenArrayOfPositiveNumber_shouldReturnCorrectVariance(CuTest* tc)
{
	/* Arrange */
    double numbers[5] = {600, 470, 170, 430, 300};
	int expected = 147;

	/* Act */
    int actual = (int) absStd(numbers, 5);

	/* Assert */
	CuAssertTrue(tc, expected == actual);
}


CuSuite* CuGetMathSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, getBiggestNumber_givenArrayOfNegativeNumbers_ShouldReturnNumberWithLowestNegativeValue);
	SUITE_ADD_TEST(suite, getBiggestNumber_givenArrayOfPositiveNumbers_ShouldReturnNumberWithHighestPositiveValue);
	SUITE_ADD_TEST(suite, getBiggestNumber_givenArrayOfNegativeAndPositiveNumbers_ShouldReturnNumberWithBiggestAbosluteValue);
	SUITE_ADD_TEST(suite, getSmallestNumber_givenArrayOfNegativeNumbers_ShouldReturnNumberWithHighestNegativeValue);
	SUITE_ADD_TEST(suite, getSmallestNumber_givenArrayOfPositiveNumbers_ShouldReturnNumberWithLowestPositiveValue);
	SUITE_ADD_TEST(suite, getSmallestNumber_givenArrayOfNegativeAndPositiveNumbers_ShouldReturnNumberWithSmallestAbosluteValue);
	SUITE_ADD_TEST(suite, absMean_givenAllPositives_shouldReturnCorrectMean);
	SUITE_ADD_TEST(suite, absMean_givenPositiveAndNegativeNumbers_shouldReturnCorrectMean);
	SUITE_ADD_TEST(suite, mean_givenAllPositives_shouldReturnCorrectMean);
	SUITE_ADD_TEST(suite, mean_givenPositiveAndNegativeNumbers_shouldReturnCorrectMean);
	SUITE_ADD_TEST(suite, absSum_givenPositiveAndNegativeNumbers_shouldReturnCorrectSum);
	SUITE_ADD_TEST(suite, absSum_givenPositiveNumbers_shouldReturnCorrectSum);
	SUITE_ADD_TEST(suite, sum_givenPositiveAndNegativeNumbers_shouldReturnCorrectSum);
	SUITE_ADD_TEST(suite, sum_givenPositiveNumbers_shouldReturnCorrectSum);
	SUITE_ADD_TEST(suite, getBiggestNumberInRow_givenRowWith3Arrays_shouldReturnBiggestValueOfAll);
	SUITE_ADD_TEST(suite, getBiggestNumberInRow_givenRowWith3ArraysWithPositiveAndNegativeNumbers_shouldReturnNumberWithBiggestAbsoluteValue);
	SUITE_ADD_TEST(suite, absVariance_givenArrayOfPositiveNumber_shouldReturnCorrectVariance);
	SUITE_ADD_TEST(suite, absStd_givenArrayOfPositiveNumber_shouldReturnCorrectVariance);
	/* SUITE_ADD_TEST(suite, dotProduct3dVector_givenVectorsOfDoubles_expectsTheCorrectDotProduct); */

	return suite;
}
