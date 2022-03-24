#include <time.h>
#include "matrixmemlib.h"
#include "matrixmath.h"

#define LABEL_DIMENSION 1

void feedForward(Matrix x, Matrix weights1, Matrix weights2, Matrix *layer1, Matrix *output)
{
    Matrix dotProductOutput = mallocMatrix(x.rows, weights1.columns),
           outputLayerMatrix = mallocMatrix(layer1->rows, weights2.columns);

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
           errorValueMultSigmoidDerivativeOutput = mallocMatrix(errorValues.rows, errorValues.columns),
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

void startTraining(Matrix input, Matrix label, int epochs, Matrix *output)
{
    /* Initializing weights */
    Matrix weights1 = mallocMatrix(input.columns, input.rows),
           weights2 = mallocMatrix(input.rows, output->columns),
           layer1 = mallocMatrix(input.rows, input.rows);
    int i;

    srand(42);
    fillMatrixWithRandomDoubles(weights1);
    fillMatrixWithRandomDoubles(weights2);

    for (i = 0; i < epochs; i++)
    {
        feedForward(input, weights1, weights2, &layer1, output);
        backPropagate(weights2, weights1, label, input, layer1, *output, &weights1, &weights2);
    }

    freeMatrix(&weights1);
    freeMatrix(&weights2);
    freeMatrix(&layer1);
}

void trainNeuralNetwork(Matrix input, Matrix label, int epochs, int loggingEnabled, Matrix *output)
{
    clock_t start, end;
    double cpu_time_used;

    if (loggingEnabled)
    {
        puts("Starting training.");
        start = clock();
    }

    startTraining(input, label, epochs, output);

    if (loggingEnabled)
    {
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("Training done.\nTime used: %f seconds.\n\n", cpu_time_used);
    }
}

int main(void)
{
    int rows = 5;
    Matrix x = mallocMatrix(rows, 5),
           y = mallocMatrix(rows, 1),
           output = mallocMatrix(rows, 1);

    /* Initializing input values */
    x.matrix[0][0] = 0;
    x.matrix[0][1] = 0;
    x.matrix[0][2] = 1;
    x.matrix[0][3] = 1;
    x.matrix[0][4] = 1;

    x.matrix[1][0] = 0;
    x.matrix[1][1] = 1;
    x.matrix[1][2] = 1;
    x.matrix[1][3] = 1;
    x.matrix[1][4] = 1;

    x.matrix[2][0] = 1;
    x.matrix[2][1] = 0;
    x.matrix[2][2] = 1;
    x.matrix[2][3] = 1;
    x.matrix[2][4] = 1;

    x.matrix[3][0] = 1;
    x.matrix[3][1] = 1;
    x.matrix[3][2] = 1;
    x.matrix[3][3] = 1;
    x.matrix[3][4] = 1;

    x.matrix[4][0] = 1;
    x.matrix[4][1] = 1;
    x.matrix[4][2] = 1;
    x.matrix[4][3] = 1;
    x.matrix[4][4] = 1;

    /* Initializing label values */
    y.matrix[0][0] = 0;
    y.matrix[1][0] = 1;
    y.matrix[2][0] = 1;
    y.matrix[3][0] = 0;
    y.matrix[4][0] = 1;

    trainNeuralNetwork(x, y, 1500000, 0, &output);
    printMatrix(output);

    return EXIT_SUCCESS;
}