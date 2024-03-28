#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <lib.h>

/*Structure pour une couche de neurones*/
typedef struct {

    float *inputs;      // Entr�es de la couche
    float *weights;     // Poids des connexions
    float *biases;      // Biais des neurones
    float *outputs;     // Sorties de la couche
} neurone;
typedef struct {
 int num_neurons;    // Nombre de neurones dans la couche
 neuron *noeud;

}Layer;

/* Initialiser une couche de neurones avec des poids et des biais al�atoires*/
void initialize_layer(Layer *layer, int num_inputs, int num_neurons) {
    layer->num_neurons = num_neurons;

    /* Allouer de la m�moire pour les entr�es, les poids, les biais et les sorties*/
    layer->noeud->inputs = (float*)malloc(num_inputs * sizeof(float));
    layer->noeud->weights = (float*)malloc(num_inputs * num_neurons * sizeof(float));
    layer->noeud->biases = (float*)malloc(num_neurons * sizeof(float));
    layer->noeud->outputs = (float*)malloc(num_neurons * sizeof(float));

/*Initialiser les poids et les biais al�atoirement*/
    for (int i = 0; i < num_inputs * num_neurons; i++) {
        layer->noeud->weights[i] = ((float)rand() / RAND_MAX) - 0.5; // Valeurs entre -0.5 et 0.5
    }
    for (int i = 0; i < num_neurons; i++) {
        layer->noeud->biases[i] = ((float)rand() / RAND_MAX) - 0.5; // Valeurs entre -0.5 et 0.5
    }
}

// Propagation avant � travers une couche de neurones avec fonction d'activation ReLU
void parcourir(Layer *prev_layer, Layer *current_layer) {
    for (int j = 0; j < current_layer->num_neurons; j++) {
        float weighted_sum = 0;
        for (int i = 0; i < prev_layer->num_neurons; i++) {
            weighted_sum += prev_layer->noeud->outputs[i] * current_layer->noeud->weights[i * current_layer->num_neurons + j];
        }
        weighted_sum += current_layer->noeud->biases[j];
        current_layer->noeud->outputs[j] = relu(weighted_sum);
    }
}

int main() {
    srand(1234); /*Initialiser le g�n�ra-teur de nombres al�atoires*/
    // Cr�er une couche cach�e avec 3 neurones
    Layer hidden;
    initialize_layer(&hidden, 3, 3);

    // Cr�er une couche de sortie avec 1 neurone
    Layer output;
    initialize_layer(&output, hidden.num_neurons, 1);

    // parcourir le r�seau de neurone
    parcourir(&hidden, &output);

    // Afficher les sorties de la couche de sortie
    printf("Sorties de la couche de sortie :\n");
    for (int i = 0; i < output.num_neurons; i++) {
        printf("%f ", output.outputs[i]);
    }
    printf("\n");

    // Lib�rer la m�moire allou�e
    free(hidden.noeud.inputs);
    free(hidden.noeud.weights);
    free(hidden.noeud.biases);
    free(hidden.noeud.outputs);
    free(output.noeud.inputs);
    free(output.noeud.weights);
    free(output.noeud.biases);
    free(output.noeud.outputs);

return 0;
}
