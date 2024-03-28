#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure pour une couche de neurones
typedef struct {
    int num_neurons;    // Nombre de neurones dans la couche
    float *inputs;      // Entrées de la couche
    float *weights;     // Poids des connexions
    float *biases;      // Biais des neurones
    float *outputs;     // Sorties de la couche
} Layer;

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
// Initialiser une couche de neurones avec des poids et des biais aléatoires
void initialize_layer(Layer *layer, int num_inputs, int num_neurons) {
    layer->num_neurons = num_neurons;

    // Allouer de la mémoire pour les entrées, les poids, les biais et les sorties
    layer->inputs = (float*)malloc(num_inputs * sizeof(float));
    layer->weights = (float*)malloc(num_inputs * num_neurons * sizeof(float));
    layer->biases = (float*)malloc(num_neurons * sizeof(float));
    layer->outputs = (float*)malloc(num_neurons * sizeof(float));

// Initialiser les poids et les biais aléatoirement
    for (int i = 0; i < num_inputs * num_neurons; i++) {
        layer->weights[i] = ((float)rand() / RAND_MAX) - 0.5; // Valeurs entre -0.5 et 0.5
    }
    for (int i = 0; i < num_neurons; i++) {
        layer->biases[i] = ((float)rand() / RAND_MAX) - 0.5; // Valeurs entre -0.5 et 0.5
    }
}

// Propagation avant à travers une couche de neurones avec fonction d'activation ReLU
void forward_propagation(Layer *prev_layer, Layer *current_layer) {
    for (int j = 0; j < current_layer->num_neurons; j++) {
        float weighted_sum = 0;
        for (int i = 0; i < prev_layer->num_neurons; i++) {
            weighted_sum += prev_layer->outputs[i] * current_layer->weights[i * current_layer->num_neurons + j];
        }
        weighted_sum += current_layer->biases[j];
        current_layer->outputs[j] = relu(weighted_sum);
    }
}

int main() {
    srand(1234); // Initialiser le générateur de nombres aléatoires pour la reproductibilité

    // Créer une couche cachée avec 3 neurones
    Layer hidden;
    initialize_layer(&hidden, 3, 3);

    // Créer une couche de sortie avec 1 neurone
    Layer output;
    initialize_layer(&output, hidden.num_neurons, 1);

    // Effectuer la propagation avant à travers le réseau
    forward_propagation(&hidden, &output);

    // Afficher les sorties de la couche de sortie
    printf("Sorties de la couche de sortie :\n");
    for (int i = 0; i < output.num_neurons; i++) {
        printf("%f ", output.outputs[i]);
    }
    printf("\n");

    // Libérer la mémoire allouée
    free(hidden.inputs);
    free(hidden.weights);
    free(hidden.biases);
    free(hidden.outputs);
    free(output.inputs);
    free(output.weights);
    free(output.biases);
    free(output.outputs);

return 0;
}
