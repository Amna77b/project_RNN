//  utilisation de  cette fonction pour entraîner un neurone à prédire une sortie cible à partir d'une seule entrée,
// en utilisant des fonctions d'activation sigmoid et leurs dérivées pour la rétropropagation

#include "lib.h"
#include "fct_activation_derivation.h"

#ifndef NEURONE_SORTIE_CIBLE_H
#define NEURONE_SORTIE_CIBLE_H

double gradient_descent(double input, double target_output, double learning_rate, int num_iterations, double *weight, double *bias) {
    double predicted_output, error, loss_value;

    for (int i = 0; i < num_iterations; i++) {
        // Forward pass
        predicted_output = sigmoid((*weight) * input + (*bias));

        // Backpropagation
        error = predicted_output - target_output;

        // Gradient descent update
        *weight -= learning_rate * error * derivative_sigmoid(predicted_output) * input;
        *bias -= learning_rate * error * derivative_sigmoid(predicted_output);

        // Calculate loss for monitoring
        loss_value = Calcul_Loss_Sigmoid(predicted_output, target_output);
        printf("Iteration %d: Predicted Output = %.4f, Error = %.4f, Loss = %.4f\n", i + 1, predicted_output, error, loss_value);
    }
    printf("FINAL Predicted Output = %.4f, FINAL Error = %.4f, FINAL Loss = %.4f\n", predicted_output, error, loss_value);
    return predicted_output;
}

#endif

