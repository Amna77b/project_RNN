// cette bibiliothéque contient les fonctions d'activation 

#include <stdio.h>
#include <math.h>
#ifndef LIB_H_
#define LIB_H_

// Fonction d'activation ReLU
float relu(float x) {
    return fmaxf(0, x); // Retourne x si x > 0, sinon 0
}
// Fonction d'activation Softmax
void softmax(float *inputs, int num_inputs) {
    double max_xi = x[0];
    double sum_exp = 0.0;

    //Rechercher le maximum dans le tableau d'entrées
    for (int i = 1; i < numb_xi; i++) {
        if (x[i] > max_xi) {
            max_xi = x[i];
        }
    }

    //Calculer la somme exponentielle
    for (int i = 0; i < numb_xi; i++) {
        sum_exp += exp(x[i] - max_xi); // Soustraction du maximum pour éviter le débordement numérique
    }

    
    for (int i = 0; i < numb_xi; i++) {
        yi[i] = exp(x[i] - max_xi) / sum_exp;
    }
}

// Fonction Sigmoid
float sigmoid(float x)
{
	return 1.0f / (1.0f + expf(-x));
}
#endif
