#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CuTest/CuTest.h"

void AssertTrue(CuTest* tc)
{
	CuAssertTrue(tc, 1);
}

CuSuite* CuGetSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, AssertTrue);

	return suite;
}