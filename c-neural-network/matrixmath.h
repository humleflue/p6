#ifndef MATRIXMATH_H
#define MATRIXMATH_H

#include <assert.h>
#include <math.h>
#include "matrixlib.h"

#define EULER 2.71828

double sigmoid(double input);
void sigmoidArray(const double *input, const int length, double *output);
void sigmoidMatrix(Matrix m, const Matrix *output);
double sigmoidDeriviate(double input);
void sigmoidDeriviateMatrix(Matrix in, const Matrix *out);
void dotProduct(double *input1, double *input2, int length, double *output);
void matrixDotProduct(Matrix m1, Matrix m2, const Matrix *output);
void hadamardProduct(Matrix m1, Matrix m2, const Matrix *output);
void transpose(Matrix in, const Matrix *transposed);

#endif /* END OF MATRIXMATH_H */