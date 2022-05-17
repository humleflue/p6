#ifndef MATH_H
#define MATH_H
#include "types.h"

#define EULER 2.71828

double power(double base, int exponent);
int getBiggestNumber(int axisArray[], int length);
int getSmallestNumber(int axisArray[], int length);
double absMean(int axisArray[], int length);
double mean(int axisArray[], int length);
double meanDouble(double axisArray[], int length);
int absSum(int axisArray[], int length);
int sum(int axisArray[], int length);
double sumDouble(double axisArray[], int length);
int getBiggestNumberInRow(int xAxisArray[], int yAxisArray[], int zAxisArray[], int length);
int getSmallestNumberInRow(int xAxisArray[], int yAxisArray[], int zAxisArray[], int length);
double absVariance(int axisArray[], int length);
double absStd(int axisArray[], int length);
int roundDouble(double num);
int dotProduct3dVectors(const int input1[3], const int input2[3]);
double power(double base, int exponent);
int roundDouble(double num);
int dotProduct3dVectors(const int input1[3], const int input2[3]);
unsigned int floorSqrt(unsigned int x);
int absValue(int input);

#endif /* END OF MATH_H */
