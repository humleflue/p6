#include "matrixlib.h"

void printMatrix(Matrix matrix)
{
    int c, d, m = matrix.rows, q = matrix.columns;
    for (c = 0; c < m; c++)
    {
        for (d = 0; d < q; d++)
            printf("%lf\t", matrix.matrix[c][d]);

        printf("\n");
    }
}
