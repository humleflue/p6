#ifndef MATRIXMEMLIB_H
#define MATRIXMEMLIB_H

#include <stdlib.h>
#include <stdio.h>
#include "matrixlib.h"

#define END_OF_ARR '\b'

void *mallocArr(const int size);
Matrix mallocMatrix(const int rows, const int columns);
void freeMatrix(Matrix *m);

#endif /* Ends MATRIXMEMLIB_H */
