#ifndef LIB_H_
#define LIB_H_

#include <stdio.h>
#include <math.h>


// Fonction d'activation ReLU
float relu(float x) {
    return fmaxf(0, x); // Retourne x si x > 0, sinon 0
}
// Fonction d'activation Softmax
void softmax(float *inputs, int num_inputs) {
    float sum = 0.0;
    for (int i = 0; i < num_inputs; i++) {
        sum += expf(inputs[i]);
    }
    for (int i = 0; i < num_inputs; i++) {
        inputs[i] = expf(inputs[i]) / sum;
    }
}
// Fonction Sigmoid
float sigmoid(float x)
{
	return 1.0f / (1.0f + expf(-x));
}
#endif
