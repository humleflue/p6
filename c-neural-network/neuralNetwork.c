#include <time.h>
#include "matrixmemlib.h"
#include "matrixmath.h"

#define TRAINING_TIME 15000000

void feedForward(Matrix x, Matrix weights1, Matrix weights2, Matrix *layer1, Matrix *output)
{
    Matrix dotProductOutput = mallocMatrix(4, 4),
           outputLayerMatrix = mallocMatrix(4, 1);

    matrixDotProduct(x, weights1, &dotProductOutput);
    sigmoidMatrix(dotProductOutput, layer1);

    matrixDotProduct(*layer1, weights2, &outputLayerMatrix);
    sigmoidMatrix(outputLayerMatrix, output);

    freeMatrix(&dotProductOutput);
    freeMatrix(&outputLayerMatrix);
}

void backPropagate(Matrix weights2, Matrix weights1, Matrix y, Matrix x, Matrix layer1, Matrix feedForwardOutput, Matrix *weights1Output, Matrix *weights2Output)
{
    int i;
    Matrix errorValues = mallocMatrix(y.rows, y.columns),
           sigmoidDeriviateOutput = mallocMatrix(feedForwardOutput.rows, feedForwardOutput.columns),
           sigmoidDeriviateLayer1 = mallocMatrix(layer1.rows, layer1.columns),
           layer1Transposed = mallocMatrix(layer1.columns, layer1.rows),
           xTransposed = mallocMatrix(x.columns, x.rows),
           weights2Transposed = mallocMatrix(weights2.columns, weights2.rows),
           errorValueMultSigmoidDerivativeOutput = mallocMatrix(errorValues.rows, 1),
           deltaWeights1IntermediateResult = mallocMatrix(errorValueMultSigmoidDerivativeOutput.rows, weights2Transposed.columns),
           deltaWeights1IntermediateResult2 = mallocMatrix(sigmoidDeriviateLayer1.rows, sigmoidDeriviateLayer1.columns),
           deltaWeights2 = mallocMatrix(weights2.rows, weights2.columns),
           deltaWeights1 = mallocMatrix(weights1.rows, weights1.columns);

    /* Calculate the error of our feed forward predictions */
    for (i = 0; i < y.rows; i++)
    {
        errorValues.matrix[i][0] = 2 * (y.matrix[i][0] - feedForwardOutput.matrix[i][0]);
    }

    sigmoidDeriviateMatrix(feedForwardOutput, &sigmoidDeriviateOutput);
    sigmoidDeriviateMatrix(layer1, &sigmoidDeriviateLayer1);

    hadamardProduct(errorValues, sigmoidDeriviateOutput, &errorValueMultSigmoidDerivativeOutput);

    /* Calculate delta weights for weights2 */
    transpose(layer1, &layer1Transposed);
    matrixDotProduct(layer1Transposed, errorValueMultSigmoidDerivativeOutput, &deltaWeights2);
    /* Calculate delta weights for weights1 */
    transpose(x, &xTransposed);
    transpose(weights2, &weights2Transposed);
    matrixDotProduct(errorValueMultSigmoidDerivativeOutput, weights2Transposed, &deltaWeights1IntermediateResult);
    hadamardProduct(deltaWeights1IntermediateResult, sigmoidDeriviateLayer1, &deltaWeights1IntermediateResult2);
    matrixDotProduct(xTransposed, deltaWeights1IntermediateResult2, &deltaWeights1);

    /* Create the output by taking the delta weights into account */
    add(weights1, deltaWeights1, weights1Output);
    add(weights2, deltaWeights2, weights2Output);
    /* printMatrix(sigmoidDeriviateLayer1); */

    /* Free matricies */
    freeMatrix(&errorValues);
    freeMatrix(&sigmoidDeriviateOutput);
    freeMatrix(&sigmoidDeriviateLayer1);
    freeMatrix(&layer1Transposed);
    freeMatrix(&xTransposed);
    freeMatrix(&weights2Transposed);
    freeMatrix(&errorValueMultSigmoidDerivativeOutput);
    freeMatrix(&deltaWeights1IntermediateResult);
    freeMatrix(&deltaWeights1IntermediateResult2);
    freeMatrix(&deltaWeights2);
    freeMatrix(&deltaWeights1);
}

/* Returns a random double between 0.00 and 1.00 */
double randDouble()
{
    return (rand() % 101) * 0.01;
}

void fillMatrixWithRandomDoubles(Matrix m)
{
    int i, j;

    for (i = 0; i < m.rows; i++)
    {
        for (j = 0; j < m.columns; j++)
        {
            m.matrix[i][j] = randDouble();
        }
    }
}

int main()
{
    /* Initializing weights */
    Matrix weights1 = mallocMatrix(3, 4),
           weights2 = mallocMatrix(4, 1),
           output = mallocMatrix(4, 1),
           layer1 = mallocMatrix(4, 4),
           x = mallocMatrix(4, 3),
           y = mallocMatrix(4, 1);
    clock_t start, end;
    double cpu_time_used;
    int i;

    srand(42);
    fillMatrixWithRandomDoubles(weights1);
    fillMatrixWithRandomDoubles(weights2);

    /* Initializing input values */
    x.matrix[0][0] = 0;
    x.matrix[0][1] = 0;
    x.matrix[0][2] = 1;

    x.matrix[1][0] = 0;
    x.matrix[1][1] = 1;
    x.matrix[1][2] = 1;

    x.matrix[2][0] = 1;
    x.matrix[2][1] = 0;
    x.matrix[2][2] = 1;

    x.matrix[3][0] = 1;
    x.matrix[3][1] = 1;
    x.matrix[3][2] = 1;

    /* Initializing output values */
    y.matrix[0][0] = 0;
    y.matrix[1][0] = 1;
    y.matrix[2][0] = 1;
    y.matrix[3][0] = 0;

    start = clock();
    for (i = 0; i < TRAINING_TIME; i++)
    {
        feedForward(x, weights1, weights2, &layer1, &output);
        backPropagate(weights2, weights1, y, x, layer1, output, &weights1, &weights2);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time used: %f seconds.\n\n", cpu_time_used);
    printMatrix(output);

    return 0;
}
