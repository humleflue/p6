#include "matrixmath.h"

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

void sigmoidMatrix(Matrix m, const Matrix *output)
{
    assert(m.columns == output->columns && m.rows == output->rows);

    for (int i = 0; i < m.rows; i++)
    {
        sigmoidArray(m.matrix[i], m.columns, output->matrix[i]);
    }
}

void dotProduct(double *input1, double *input2, int length, double *output)
{
    for (int i = 0; i < length; i++)
    {
        output[i] = input1[i] * input2[i];
    }
}

void matrixDotProduct(Matrix m1, Matrix m2, const Matrix *output)
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

            output->matrix[c][d] = sum;
            sum = 0;
        }
    }
}

void transpose(Matrix in, const Matrix *transposed)
{
    int i, j;
    assert(in.rows == transposed->columns && in.columns == transposed->rows);

    for (i = 0; i < in.rows; i++)
    {
        for (j = 0; j < in.columns; j++)
        {
            transposed->matrix[j][i] = in.matrix[i][j];
        }
    }
}
