#include "matrixmemlib.h"

/* Dynamicly allocates memory for an array */
/** Function that allocates space for an array with malloc.
 * @param [in] size The size of the array.
 * @return Returns *arr The space allocated.
 */
void *mallocArr(const int size)
{
    void *arr;

    arr = malloc(size);
    if (arr == NULL)
    {
        puts("FATAL ERROR! mallocArr could not allocate the requested memory.\nThe program will now exit.");
        exit(0);
    }

    return arr;
}

/* Dynamicly allocates memory for a matrix. */
/** Function that allocates space a 2D array with malloc.
 * @param [in] rows The amount of rows in the matrix
 * @param [in] columns The amount of columns in the matrix
 * @return Returns the dynamically allocated matrix
 */
Matrix mallocMatrix(const int rows, const int columns)
{
    int rows_freeable = rows + 1, /* +1 to be able to free the array again */
        i;
    Matrix m;

    m.matrix = mallocArr(rows_freeable * sizeof(double *));
    m.rows = rows;
    m.columns = columns;

    for (i = 0; i < rows; i++)
    {
        m.matrix[i] = mallocArr(columns * sizeof(double));
    }
    /* Readies array to get freed */
    m.matrix[i] = mallocArr(1);
    m.matrix[i][0] = END_OF_ARR;

    return m;
}

/* Frees the memory allocated by mallocMatrix */
/** Frees the amount of space allocated with malloc
 * @param [in] m The matrix that must be freed.
 */
void freeMatrix(Matrix *m)
{
    int i = 0, done = 0;

    while (!done)
    {
        if (m->matrix[i][0] == END_OF_ARR)
        {
            done = 1;
        }
        free(m->matrix[i]);
        i++;
    }
    free(m->matrix);
}
