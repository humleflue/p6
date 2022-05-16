#ifndef MATH_H
#define MATH_H
#include "types.h"

#define EULER 2.71828

double power(double base, int exponent);
double getBiggestNumber(double axisArray[], int length);
double getSmallestNumber(double axisArray[], int length);
double absMean(double axisArray[], int length);
double mean(double axisArray[], int length);
double absSum(double axisArray[], int length);
double sum(double axisArray[], int length);
double getBiggestNumberInRow(double xAxisArray[], double yAxisArray[], double zAxisArray[], int length);
int    roundDouble(double num);
int    dotProduct3dVectors(const int input1[3], const int input2[3]);

#endif /* END OF MATH_H */
