#ifndef MATRIXMATH_H
#define MATRIXMATH_H

#include <assert.h>
#include <math.h>
#include "matrixlib.h"

#define EULER 2.71828

double sigmoid(double input);
double sigmoidDeriviate(double input);
void sigmoidArray(const double *input, const int length, double *output);
void sigmoidMatrix(Matrix m, Matrix output);
void dotProduct(double *input1, double *input2, int length, double *output);
void matrixDotProduct(Matrix m1, Matrix m2, Matrix output);

#endif /* END OF MATRIXMATH_H */