#include "math.h"
#include "types.h"
#include <stdio.h>

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

double getBiggestNumber(double axisArray[], int length){
    double highestNumber = 0;
    int negativeOrPositive = 1;
    int i;
    for (i = 0; i < TIME_SERIES_VECTORS_AMOUNT; i++)
    {
        double currentNumber = axisArray[i];
        if(currentNumber > 0)
        {
            if (currentNumber > highestNumber)
            {
                highestNumber = currentNumber;
                negativeOrPositive = 1;
            }
            
        } else
        {
            if (-1 * currentNumber > highestNumber)
            {
                highestNumber = -1 * currentNumber;
                negativeOrPositive = -1;
            }
            
        }
    }
    return negativeOrPositive * highestNumber;
}

double getSmallestNumber(double axisArray[], int length){
    double smallestNumber = 999999;
    int negativeOrPositive = 1;
    int i;
    for (i = 0; i < TIME_SERIES_VECTORS_AMOUNT; i++)
    {
        double currentNumber = axisArray[i];
        if(currentNumber > 0)
        {
            if (currentNumber < smallestNumber)
            {
                smallestNumber = currentNumber;
                negativeOrPositive = 1;
            }
            
        } else
        {
            if (-1 * currentNumber < smallestNumber)
            {
                smallestNumber = -1 * currentNumber;
                negativeOrPositive = -1;
            }
            
        }
    }
    return negativeOrPositive * smallestNumber;
}

double absMean(double axisArray[], int length){
    double result = absSum(axisArray, length);
    return result / length;    
}

double mean(double axisArray[], int length){
    double result = sum(axisArray, length);
    return result / length;    
}

double absSum(double axisArray[], int length){
    double result = 0;
    int i;
    for (i = 0; i < length; i++)
    {
        if(axisArray[i] < 0)
        {
            result += -1 * axisArray[i];
        } else {
            result += axisArray[i];
        }
    }
    return result;   
}

double sum(double axisArray[], int length){
    double result = 0;
    int i;
    for (i = 0; i < length; i++)
    {
        result += axisArray[i];
    }
    return result;   
}
