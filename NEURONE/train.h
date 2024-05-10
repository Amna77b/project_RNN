#include <stdio.h>
#include <stdlib.h>
#include "work.h"
#include "optimation_tools.h"
#include "lib.h"
#include "fct_activation_derivation.h"
#include "description.h"
#include "Save.h"
#include "sortie_cible.h"

#ifndef NEURONE_TRAIN_H
#define NEURONE_TRAIN_H

// Apply train on the neuronal network
void train_single_neuron_network(const char* filename) {
    // Initializaton
    int num_couches = 1;
    int num_neurones[1] = {1};
    int num_xi_par_neurone[1] = {2};
    Reseau* reseau = initializer_reseau(num_couches, num_neurones, num_xi_par_neurone);


    double learning_rate = 0.01;
    int num_iterations = 100;

    // apply sigmoid
    reseau->couches[0]->neurones[0]->activation_function = 2;

    // using the datset excel file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("you can not open the file  %s\n", filename);
        liberer_reseau(reseau);
        return;
    }

    // Read feature 1, feature 2, and label from each row
    double feature1, feature2, label;
    int count = 0; // Déclaration de count et l'inntialization a 0
    while (fscanf(file, "%lf %lf %lf", &feature1, &feature2, &label) == 3) {

        reseau->couches[0]->neurones[0]->xi[0] = feature1;
        reseau->couches[0]->neurones[0]->xi[1] = feature2;


        double predicted_output = compter_couche_yi(reseau->couches[0], reseau->couches[0]->neurones[0]->xi);


        double error = predicted_output - label;
        gradient_descent(feature1, label, learning_rate, num_iterations, &reseau->couches[0]->neurones[0]->wi[0], &reseau->couches[0]->neurones[0]->bias);
        gradient_descent(feature2, label, learning_rate, num_iterations, &reseau->couches[0]->neurones[0]->wi[1], &reseau->couches[0]->neurones[0]->bias);


        if (count % 10 == 0) {
            double loss_value = Calcul_Loss_Sigmoid(predicted_output, label);
            printf("Iteration %d: Predicted Output = %.4f, Loss = %.4f\n", count, predicted_output, loss_value);
        }
        count++;
    }

    fclose(file);


    // Cleanup
    liberer_reseau(reseau);
}




#endif
