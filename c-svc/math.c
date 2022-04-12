#include "math.h"

double power(double base, int exponent) {
    double result = 1.0;
    int i;

    for(i = 0; i < exponent; i++) {
        result *= base;
    }

    return result;
}

int round(double num) {
    if (num < 0.0)
        return (int)(num - 0.5);
    else
        return (int)(num + 0.5);
}
