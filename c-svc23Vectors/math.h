#ifndef MATH_H
#define MATH_H
#include "types.h"

#define EULER 2.71828

double power(double base, int exponent);
double getBiggestNumber(double axisArray[TIME_SERIES_VECTORS_AMOUNT]);
double getSmallestNumber(double axisArray[TIME_SERIES_VECTORS_AMOUNT]);
int    roundDouble(double num);
int    dotProduct3dVectors(const int input1[3], const int input2[3]);

#endif /* END OF MATH_H */
