#include <stdio.h>
#include<math.h>

#define EULER 2.71828
#define ROWS 4
#define COLLUMNS 3
#define TRAINING_TIME 1500

double sigmoid(double input) {
    return 1/(1+pow(EULER, input * -1.0));
}

double sigmoidDeriviate(double input) {
    return input * (1 - input);
}

void sigmoidArray(const double *input, const int length, double * output) {
    for(int i = 0; i < length; i++) {
        output[i] = sigmoid(input[i]);
    }
}

void dotProduct(double *input1, double *input2, int length, double *output) {
    for(int i = 0; i < length; i++) {
        output[i] = input1[i] * input2[i];
    }
}

void feedForward(int **x, int **y) {

}

void backPropagate(int **x, int **y) {

}

int main()
{
    int x[ROWS][COLLUMNS] = {
        {0, 0, 1},
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };
    int y[ROWS][1] = {
        {0},
        {1},
        {1},
        {0}
    };

    double w1 = 0.5;
    double w2 = 0.7;


    for(int i = 0; i < TRAINING_TIME; i++) {

    }


    return 0;
}
