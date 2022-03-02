#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define EULER 2.71828
#define ROWS 4
#define COLUMNS 3
#define WEIGHT_ROWS 3
#define WEIGHT_COLUMNS 4
#define END_OF_ARR '\b'
#define FALSE 0
#define TRUE 1

#define TRAINING_TIME 1500

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
        puts("FATAL ERROR! mallocArr could not alllocate the requested memory.\nThe program will now exit.");
        exit(EXIT_FAILURE);
    }

    return arr;
}

/* Dynamicly allocates memory for an array of strings. */
/** Function that allocates space a 2D array with calloc.
 * @param [in] str_amount The amount of strings wanted in the array
 * @param [in] length The length of the string.
 * @return Returns *arr The space allocated.
 */
double **mallocMatrix(const int rows, const int columns, const int sizeOfColumnEntry)
{
    int rows_freeable = rows + 1, /* +1 to be able to free the array again */
        i;
    double **arr = mallocArr(rows_freeable * sizeof(double*));

    for (i = 0; i < rows; i++)
    {
        arr[i] = mallocArr(columns * sizeOfColumnEntry);
    }
    /* Readies array to get freed */
    arr[i] = mallocArr(1);
    arr[i][0] = END_OF_ARR;

    return arr;
}

/* Frees the memory allocated by callocStrArr */
/** Frees the amount of space allocated with calloc
 * @param [in] arr The array that must be free'd.
 */
void freeMatrix(double **arr)
{
    int i = 0, done = FALSE;

    while (!done)
    {
        if (arr[i][0] == END_OF_ARR)
        {
            done = 1;
        }
        free(arr[i]);
        i++;
    }
    free(arr);
}


double sigmoid(double input) {
    return 1/(1+pow(EULER, input * -1.0));
}

double sigmoidDeriviate(double input) {
    return input * (1 - input);
}

void sigmoidArray(const double *input, const int length, double * output) {
    for(int i = 0; i < length; i++) {
        output[i] = sigmoid(input[i]);
    }
}

void sigmoidMatrix(const double** matrix, int rows, int columns, double** outputMatrix){
    for (int i = 0; i < rows; i++)
    {
        sigmoidArray(matrix[i], columns, outputMatrix[i]);
    }
}


void dotProduct(double *input1, double *input2, int length, double *output) {
    for(int i = 0; i < length; i++) {
        output[i] = input1[i] * input2[i];
    }

}

void feedForward(double **x, double **y, double** output) {


}

void backPropagate(double **x, double **y) {

}


void printMatrix(double** matrix, int rows, int columns){
    int c, d, m = rows, q = columns;
    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++)
        printf("%lf\t", matrix[c][d]);
 
      printf("\n");
    }
}

void matrixDotProduct(double x[4][3], double weights[3][4], double** outputMatrix) {
    int m = 4, p = 3, q = 4, c, d, k;
    double sum = 0;
    

    for (c = 0; c < m; c++) {
      for (d = 0; d < q; d++) {
        for (k = 0; k < p; k++) {
          sum = sum + x[c][k]*weights[k][d];
        }
 
        outputMatrix[c][d] = sum;
        sum = 0;
      }
    }
}


int main()
{
    double x[ROWS][COLUMNS] = {
        {0, 0, 1},
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };
    // double y[ROWS][1] = {
    //     {0},
    //     {1},
    //     {1},
    //     {0}
    // };

    double weights1[WEIGHT_ROWS][WEIGHT_COLUMNS] = {
        {0.1, 0.1, 0.1, 0.1},
        {0.2, 0.2, 0.2, 0.2},
        {0.3, 0.3, 0.3, 0.3},
    };


    double** matrixResult = mallocMatrix(4, 4, sizeof(double));
    matrixDotProduct(x, weights1, matrixResult);

    double** sigmoidedMatrix = mallocMatrix(4, 4, sizeof(double));    
    sigmoidMatrix(matrixResult, 4, 4, sigmoidedMatrix);
    freeMatrix(matrixResult);
    printMatrix(sigmoidedMatrix, 4, 4);

    //sigmoidMatrix(matrixResult, ROWS, WEIGHT_COLUMNS);
    

    for(int i = 0; i < TRAINING_TIME; i++) {

    }


    return 0;
}
