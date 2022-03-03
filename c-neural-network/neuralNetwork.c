#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "matrixmemlib.h"
#include "matrixmath.h"

#define TRAINING_TIME 1500

void feedForward(Matrix x, Matrix weights1, Matrix weights2, Matrix output)
{
    Matrix firstLayerDotProductResult = mallocMatrix(4, 4);
    matrixDotProduct(x, weights1, firstLayerDotProductResult);

    Matrix sigmoidedMatrix = mallocMatrix(4, 4);
    sigmoidMatrix(firstLayerDotProductResult, sigmoidedMatrix);
    freeMatrix(firstLayerDotProductResult);

    Matrix outputLayerMatrix = mallocMatrix(4, 1);
    matrixDotProduct(sigmoidedMatrix, weights2, outputLayerMatrix);
    freeMatrix(sigmoidedMatrix);

    sigmoidMatrix(outputLayerMatrix, output);
    freeMatrix(outputLayerMatrix);
}

// void backPropagate(double **x, double **y)
// {
// }

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

    // Initializing output values
    // double y[ROWS][1] = {
    //     {0},
    //     {1},
    //     {1},
    //     {0}
    // };

    Matrix output = mallocMatrix(4, 1);
    feedForward(x, weights1, weights2, output);

    printMatrix(output);

    // sigmoidMatrix(matrixResult, ROWS, WEIGHT_COLUMNS);

    for (int i = 0; i < TRAINING_TIME; i++)
    {
    }

    return 0;
}
