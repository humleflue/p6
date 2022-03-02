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
double **mallocMatrix(const int rows, const int columns)
{
    int rows_freeable = rows + 1, /* +1 to be able to free the array again */
        i;
    double **arr = mallocArr(rows_freeable * sizeof(double*));

    for (i = 0; i < rows; i++)
    {
        arr[i] = mallocArr(columns * sizeof(double));
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

void sigmoidMatrix(double** matrix, int rows, int columns, double** outputMatrix){
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

void feedForward(double **x, double** output) {
    double** firstLayerDotProductResult = mallocMatrix(4, 4);
    matrixDotProduct(x, weights1, ROWS, COLUMNS, WEIGHT_COLUMNS, firstLayerDotProductResult);
    double** sigmoidedMatrix = mallocMatrix(4, 4);    
    sigmoidMatrix(firstLayerDotProductResult, 4, 4, sigmoidedMatrix);
    freeMatrix(firstLayerDotProductResult);
    double** outputLayerMatrix = mallocMatrix(4, 1);    
    matrixDotProduct(sigmoidedMatrix, weights2, 4, 4, 1, outputLayerMatrix);
    freeMatrix(sigmoidedMatrix);
    sigmoidMatrix(outputLayerMatrix, 4, 1, output);
    freeMatrix(outputLayerMatrix);
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

void matrixDotProduct(double** matrix1, double** matrix2, int matrix1Rows, int matrixSharedDimension, int matrix2Columns, double** outputMatrix) {
    int c, d, k;
    double sum = 0;
    
    for (c = 0; c < matrix1Rows; c++) {
      for (d = 0; d < matrix2Columns; d++) {
        for (k = 0; k < matrixSharedDimension; k++) {
          sum = sum + matrix1[c][k]*matrix2[k][d];
        }
 
        outputMatrix[c][d] = sum;
        sum = 0;
      }
    }
}


double randDouble(){
    return (rand() % 101) * 0.01;
}

void fillMatrixWithRandomDoubles(int rows, int columns, double** matrix){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            matrix[i][j] = randDouble();
        }
    }
}

int main()
{
    srand(42);
    // Initializing weights
    double** weights1 = mallocMatrix(4, 4);
    fillMatrixWithRandomDoubles(4, 4, weights1);
    double** weights2 = mallocMatrix(4, 1);
    fillMatrixWithRandomDoubles(4, 1, weights2);

    // Initializing input values
    double** x = mallocMatrix(ROWS, COLUMNS);
    x[0][0] = 0;
    x[0][1] = 0;
    x[0][2] = 1;

    x[1][0] = 0;
    x[1][1] = 1;
    x[1][2] = 1;
    
    x[2][0] = 1;
    x[2][1] = 0;
    x[2][2] = 1;
    
    x[3][0] = 1;
    x[3][1] = 1;
    x[3][2] = 1;

    // Initializing output values
    // double y[ROWS][1] = {
    //     {0},
    //     {1},
    //     {1},
    //     {0}
    // };

    
    double** output = mallocMatrix(4, 1);
    feedForward(output);

    
    
    
    printMatrix(output, 4, 1);

    //sigmoidMatrix(matrixResult, ROWS, WEIGHT_COLUMNS);    

    for(int i = 0; i < TRAINING_TIME; i++) {

    }


    return 0;
}
