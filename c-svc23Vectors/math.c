#include "math.h"
#include "types.h"

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

int getBiggestNumber(int axisArray[], int length){
    int highestNumber = 0;
    int negativeOrPositive = 1;
    int i;
    for (i = 0; i < length; i++)
    {
        int currentNumber = axisArray[i];
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

int getBiggestNumberInRow(int xAxisArray[], int yAxisArray[], int zAxisArray[], int length){
    int biggestX = getBiggestNumber(xAxisArray, length),
        biggestY = getBiggestNumber(yAxisArray, length),
        biggestZ = getBiggestNumber(zAxisArray, length),
        xyz[3];

    xyz[0] = biggestX;
    xyz[1] = biggestY;
    xyz[2] = biggestZ;

    return getBiggestNumber(xyz, 3);
}

int getSmallestNumberInRow(int xAxisArray[], int yAxisArray[], int zAxisArray[], int length){
    int smallestX = getSmallestNumber(xAxisArray, length),
        smallestY = getSmallestNumber(yAxisArray, length),
        smallestZ = getSmallestNumber(zAxisArray, length),
        xyz[3];

    xyz[0] = smallestX;
    xyz[1] = smallestY;
    xyz[2] = smallestZ;
        
    return getSmallestNumber(xyz, 3);
}

int getSmallestNumber(int axisArray[], int length){
    int smallestNumber = 999999;
    int negativeOrPositive = 1;
    int i;
    for (i = 0; i < length; i++)
    {
        int currentNumber = axisArray[i];
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

double absMean(int axisArray[], int length){
    double result = absSum(axisArray, length);
    return result / length;    
}

double mean(int axisArray[], int length){
    double result = sum(axisArray, length);
    return result / length;    
}

double meanDouble(double axisArray[], int length){
    double result = sumDouble(axisArray, length);
    return result / length;    
}

int absSum(int axisArray[], int length){
    int result = 0;
    int i;
    for (i = 0; i < length; i++)
    {
        result += absValue(axisArray[i]);
    }
    return result;   
}

int sum(int axisArray[], int length){
    int result = 0;
    int i;
    for (i = 0; i < length; i++)
    {
        result += axisArray[i];
    }
    return result;   
}

double sumDouble(double axisArray[], int length){
    double result = 0;
    int i;
    for (i = 0; i < length; i++)
    {
        result += axisArray[i];
    }
    return result;   
}

double absVariance(int axisArray[], double differencesSquared[], int length) {
    double abs_mean = absMean(axisArray, length),
           variance;
    int i;
    for (i = 0; i < length; i++)
    {   
        double difference = axisArray[i] - abs_mean;
        differencesSquared[i] = difference * difference;
    }
    
    variance = meanDouble(differencesSquared, length);
    return variance;
}

double absStd(int axisArray[], double differencesSquared[], int length) {
    unsigned int abs_variance = (unsigned int) absVariance(axisArray, differencesSquared, length);
    return (double) floorSqrt(abs_variance);
}

int absValue(int input){
    if(input < 0) {
        return input * -1;
    } else {
        return input;
    }
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
