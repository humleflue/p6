#ifndef MATRIXMEMLIB_H
#define MATRIXMEMLIB_H

#include <stdlib.h>
#include <stdio.h>

#define END_OF_ARR '\b'

typedef struct Matrix
{
    double **matrix;
    int rows;
    int columns;
} Matrix;

void *mallocArr(const int size);
Matrix mallocMatrix(const int rows, const int columns);
void freeMatrix(Matrix m);

#endif /* Ends MATRIXMEMLIB_H */
