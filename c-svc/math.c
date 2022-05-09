#include "math.h"

double power(double base, int exponent) {
    double result = 1.0;
    int    i;

    for(i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}

int roundDouble(double num) {
    if (num < 0.0)
        return (int)(num - 0.5);
    else
        return (int)(num + 0.5);
}

/* More generic helper function */
double dotProductVectors(const double *input1, const double *input2, int length) {
    int    i;
    double sum = 0;

    for (i = 0; i < length; i++)
    {
        sum += input1[i] * input2[i];
    }

    return sum;
}

double dotProduct3dVectors(const double input1[3], const double input2[3]) {
    return dotProductVectors((const double*)input1, (const double*)input2, 3);
}
