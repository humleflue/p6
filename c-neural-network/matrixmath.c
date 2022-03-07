#include "matrixmath.h"

double sigmoid(double input)
{
    return 1 / (1 + pow(EULER, input * -1.0));
}

void sigmoidArray(const double *input, const int length, double *output)
{
    int i;

    for (i = 0; i < length; i++)
    {
        output[i] = sigmoid(input[i]);
    }
}

void sigmoidMatrix(Matrix m, const Matrix *output)
{
    int i;

    assert(m.columns == output->columns && m.rows == output->rows);

    for (i = 0; i < m.rows; i++)
    {
        sigmoidArray(m.matrix[i], m.columns, output->matrix[i]);
    }
}

double sigmoidDeriviate(double input)
{
    return input * (1 - input);
}

void sigmoidDeriviateMatrix(Matrix in, const Matrix *out)
{
    int i, j;

    assert(in.rows == out->rows && in.columns == out->columns);

    for (i = 0; i < in.rows; i++)
    {
        for (j = 0; j < in.columns; j++)
        {
            out->matrix[i][j] = sigmoidDeriviate(in.matrix[i][j]);
        }
    }
}

void dotProduct(double *input1, double *input2, int length, double *output)
{
    int i;

    for (i = 0; i < length; i++)
    {
        output[i] = input1[i] * input2[i];
    }
}

void matrixDotProduct(Matrix m1, Matrix m2, const Matrix *output)
{
    int c, d, k;
    double sum = 0;

    assert(m1.columns == m2.rows);
    assert(m1.rows == output->rows);
    assert(m2.columns == output->columns);

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

/* Element wise multiplication */
void hadamardProduct(Matrix m1, Matrix m2, const Matrix *output)
{
    int i, j;

    assert(m1.rows == m2.rows);
    assert(m1.columns == m2.columns);
    assert(m1.rows == output->rows);
    assert(m1.columns == output->columns);

    for (i = 0; i < m1.rows; i++)
    {
        for (j = 0; j < m1.columns; j++)
        {
            output->matrix[i][j] = m1.matrix[i][j] * m2.matrix[i][j];
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

void add(Matrix m1, Matrix m2, const Matrix *out)
{
    int i, j;

    assert(m1.rows == m2.rows);
    assert(m1.columns == m2.columns);

    for (i = 0; i < m1.rows; i++)
    {
        for (j = 0; j < m1.columns; j++)
        {
            out->matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
        }
    }
}
