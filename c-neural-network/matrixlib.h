#ifndef MATRIXLIB_H
#define MATRIXLIB_H

#include <stdio.h>

typedef struct Matrix
{
    double **matrix;
    int rows;
    int columns;
} Matrix;

void printMatrix(Matrix matrix);

#endif /* END OF MATRIXLIB_H */
