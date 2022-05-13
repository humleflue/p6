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
int dotProductVectors(const int *input1, const int *input2, int length) {
    int i,
        sum = 0;

    for (i = 0; i < length; i++)
    {
        sum += input1[i] * input2[i];
    }

    return sum;
}

int dotProduct3dVectors(const int input1[3], const int input2[3]) {
    return dotProductVectors((const int*)input1, (const int*)input2, 3);
}

/* Returns floor of square root of x 
 * Found here: https://www.geeksforgeeks.org/square-root-of-an-integer/
 */
unsigned int floorSqrt(unsigned int x) {
    unsigned int i      = 1, 
                 result = 1;

    /* Base cases */
    if (x == 0 || x == 1)
        return x;
 
    /* Starting from 1, try all numbers until
     * i*i is greater than or equal to x.
     */
    while (result <= x)
    {
      i++;
      result = i * i;
    }

    return i - 1;
}
