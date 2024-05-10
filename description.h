//Here there is a small description of the principal elements of neuronal network

#ifndef NEURONE_DESCRIPTION_H
#define NEURONE_DESCRIPTION_H

//define the structure of the neurone
typedef struct Neurone
{
    int num_xi;

    double *xi;
    double *wi;
    double bias;
    double yi;
    int act_function;/
} Neurone;

//define  the layer
typedef struct Couche
{
    int num_neurones;
    Neurone **neurones;
}Couche;

//define the neuronal network
typedef struct Reseau{
    int num_couches;
    Couche **couches;
}Reseau;

#endif
