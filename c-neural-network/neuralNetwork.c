#include "matrixmemlib.h"
#include "matrixmath.h"

#define TRAINING_TIME 1500

void feedForward(Matrix x, Matrix weights1, Matrix weights2, Matrix *layer1, Matrix *output)
{
    matrixDotProduct(x, weights1, layer1);

    Matrix sigmoidedMatrix = mallocMatrix(4, 4);
    sigmoidMatrix(*layer1, &sigmoidedMatrix);

    Matrix outputLayerMatrix = mallocMatrix(4, 1);
    matrixDotProduct(sigmoidedMatrix, weights2, &outputLayerMatrix);
    freeMatrix(&sigmoidedMatrix);

    sigmoidMatrix(outputLayerMatrix, output);
    freeMatrix(&outputLayerMatrix);
}

void backPropagate(Matrix weights2, Matrix weights1, Matrix y, Matrix x, Matrix layer1, Matrix feedForwardOutput, Matrix weights2Output, Matrix weights1Output)
{
    Matrix errorValues = mallocMatrix(y.rows, y.columns),
           sigmoidDeriviateOutput = mallocMatrix(feedForwardOutput.rows, feedForwardOutput.columns),
           sigmoidDeriviateLayer1 = mallocMatrix(layer1.rows, layer1.columns),
           layer1Transposed = mallocMatrix(layer1.columns, layer1.rows),
           xTransposed = mallocMatrix(x.columns, x.rows),
           weights2Transposed = mallocMatrix(x.columns, x.rows),
           errorValueMultSigmoidDerivativeOutput = mallocMatrix(errorValues.rows, 1),
           deltaWeights1IntermediateResult = mallocMatrix(errorValueMultSigmoidDerivativeOutput.rows, weights2Transposed.columns),
           deltaWeights2 = mallocMatrix(weights2.rows, weights2.columns),
           deltaWeights1 = mallocMatrix(weights1.rows, weights1.columns);

    /* Calculate the error of our feed forward predictions */
    for (int i = 0; i < y.rows; i++)
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
    hadamardProduct(deltaWeights1IntermediateResult, weights2Transposed, &deltaWeights1);

    /* Create the output by taking the delta weights into account */
}

/* Returns a random double between 0.00 and 1.00 */
double randDouble()
{
    return (rand() % 101) * 0.01;
}

void fillMatrixWithRandomDoubles(Matrix m)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            m.matrix[i][j] = randDouble();
        }
    }
}

int main()
{
    srand(42);

    // Initializing weights
    Matrix weights1 = mallocMatrix(3, 4);
    fillMatrixWithRandomDoubles(weights1);
    Matrix weights2 = mallocMatrix(4, 1);
    fillMatrixWithRandomDoubles(weights2);

    // Initializing input values
    Matrix x = mallocMatrix(4, 3);
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

    Matrix output = mallocMatrix(4, 1);
    Matrix layer1 = mallocMatrix(4, 4);
    feedForward(x, weights1, weights2, &layer1, &output);
    printMatrix(output);

    // Initializing output values
    Matrix y = mallocMatrix(4, 1);
    y.matrix[0][0] = 0;
    y.matrix[1][0] = 1;
    y.matrix[2][0] = 1;
    y.matrix[3][0] = 0;

    for (int i = 0; i < TRAINING_TIME; i++)
    {
    }

    return 0;
}
