#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "matrixmemlib.h"

#define EULER 2.71828
#define ROWS 4
#define COLUMNS 3
#define WEIGHT_ROWS 3
#define WEIGHT_COLUMNS 4
#define FALSE 0
#define TRUE 1

#define TRAINING_TIME 1500

double sigmoid(double input)
{
    return 1 / (1 + pow(EULER, input * -1.0));
}

double sigmoidDeriviate(double input)
{
    return input * (1 - input);
}

void sigmoidArray(const double *input, const int length, double *output)
{
    for (int i = 0; i < length; i++)
    {
        output[i] = sigmoid(input[i]);
    }
}

void sigmoidMatrix(Matrix m, Matrix output)
{
    assert(m.columns == output.columns && m.rows == output.rows);

    for (int i = 0; i < m.rows; i++)
    {
        sigmoidArray(m.matrix[i], m.columns, output.matrix[i]);
    }
}

void dotProduct(double *input1, double *input2, int length, double *output)
{
    for (int i = 0; i < length; i++)
    {
        output[i] = input1[i] * input2[i];
    }
}

void matrixDotProduct(Matrix m1, Matrix m2, Matrix output)
{
    int c, d, k;
    double sum = 0;

    // printf("%d, %d\n", m1.columns, m2.rows); // DEBUG
    assert(m1.columns == m2.rows);

    for (c = 0; c < m1.rows; c++)
    {
        for (d = 0; d < m2.columns; d++)
        {
            for (k = 0; k < m1.columns; k++)
            {
                sum = sum + m1.matrix[c][k] * m2.matrix[k][d];
            }

            output.matrix[c][d] = sum;
            sum = 0;
        }
    }
}

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
