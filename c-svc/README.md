# Support Vector Classifier in C

## Getting started
To run the SVC run `make` in your terminal/console and execute the generated svc.out/svc.exe file.

If you want to fire a single command, then run the following: `make && svc.out` (use svc.exe on Windows).

## Testing
We are using CuTest for our unit tests (http://cutest.sourceforge.net/).

### Running the tests
To run all the tests, first compile the svc with `make`, then run `make testw` on Windows or `make testu` on Unix. 

This will generate a file called AllTests.out (AllTests.exe on Windows).

To run all the tests, execute the AllTests.out file.

If you want to fire a single command, then run the following: `make && make testu && AllTests.out` on Unix or `make ; make testw ; AllTests.exe` on Windows.

### Creating new tests
**IMPORTANT**: There is absolutely no need to modify anything in the CuTest directory.

The **AllTests.c** file is responsible for adding the different test suites. A test suite can be seen as a new file.

Add your suites inside the `/* ADD NEW SUITES IN THIS REGION */` comments.

To write new tests in a new test file, take a look at the examples from TransformTests.c or ./CuTest/Examples.c.