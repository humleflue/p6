#include <stdio.h>

#include "CuTest/CuTest.h"

CuSuite* CuGetTransformSuite();
CuSuite* CuGetMathSuite();
CuSuite* CuGetPredictorSuite();
CuSuite* CuGetEndToEndSuite();

void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	/* ADD NEW SUITES IN THIS REGION */
	CuSuiteAddSuite(suite, CuGetTransformSuite());
	CuSuiteAddSuite(suite, CuGetMathSuite());
	CuSuiteAddSuite(suite, CuGetPredictorSuite());
	CuSuiteAddSuite(suite, CuGetEndToEndSuite());
	/* ADD NEW SUITES IN THIS REGION */

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

int main(void)
{
	RunAllTests();
}
