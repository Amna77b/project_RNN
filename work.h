//this library show some of functions that describe  the work of neurone
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"
#include "Types.h"

#ifndef WORK_H
#define WORK_H

//giving the number of layers ,neurons ...
void Saisie(int* num_couches,int** num_neurones,int** num_xi_par_neurone){

    printf("Entrer le nombre des couches: ");
    scanf("%d",num_couches);

    // Allocation dynamique
    *num_neurones=(int*)malloc(*num_couches * sizeof(int));
    if (*num_neurones == NULL) {
        printf("Erreur d'allocation de mémoire pour le tableau de nombre de neurones par couche.");
        exit;
    }

    // Allouer de la mémoire pour le tableau de nombres d'entrées par neurone par couche
    *num_xi_par_neurone = (int*)malloc(*num_couches * sizeof(int));
    if (*num_xi_par_neurone == NULL) {
        printf("Erreur d'allocation de mémoire pour le tableau de nombre d'entrées par neurone par couche.");
        exit;
    }

    // Demander à l'utilisateur le nombre de neurones par couche
    for (int i=0;i<*num_couches;i++) {
        printf("Entrez le nombre de neurones pour la couche %d: ",i+1);
        scanf("%d", &((*num_neurones)[i]));
    }

    // Demander à l'utilisateur le nombre d'entrées par neurone par couche
    for (int i=0;i<*num_couches;i++) {
        printf("Entrez le nombre d'entrees par neurone pour la couche %d: ",i+1);
        scanf("%d", &((*num_xi_par_neurone)[i]));
    }
}

void SaisieValeurs(Reseau* reseau, int* num_xi_par_neurone) {
    printf("Saisie des valeurs pour la premiere couche:\n");
    for (int j = 0; j < reseau->couches[0]->num_neurones; j++) {
        printf("Choix de la fonction d'activation pour le neurone %d de la couche 1:\n", j + 1);
        printf("1. ReLU\n");
        printf("2. Sigmoid\n");
        printf("3. Softmax\n");
        printf("Choix de la fonction d'activation pour le neurone %d: ", j + 1);
        scanf("%d", &reseau->couches[0]->neurones[j]->activation_function);

        reseau->couches[0]->neurones[j]->xi = (double *)malloc(num_xi_par_neurone[0] * sizeof(double));

        printf("Saisie des valeurs pour le neurone %d de la couche 1:\n", j + 1);
        for (int k = 0; k < num_xi_par_neurone[0]; k++) {
            printf("Saisie la valeur %d pour le neurone %d de la couche 1: ", k + 1, j + 1);
            scanf("%lf", &reseau->couches[0]->neurones[j]->xi[k]);
        }
    }
}

//Initialiser un neurone avec un nombre d'entrées donné
Neurone* initializer_neurone(int num_xi)
{
    Neurone* neurone = (Neurone*)malloc(sizeof(Neurone));
    //Vérifier si l'allocation de mémoire a réussi
    if (neurone==NULL)
    {
        printf( "Erreur : Impossible d'allouer de la mémoire pour le neurone.");
        exit;
    }

    neurone->num_xi=num_xi;
    neurone->xi=(double*)malloc(num_xi*sizeof(double));//Allouer de la mémoire pour le tableau d'entrées (xi)

    //Vérifier si l'allocation de mémoire a réussi
    if (neurone->xi==NULL)
    {
        printf( "Erreur : Impossible d'allouer de la mémoire pour les entrées du neurone.");
        exit;
    }

    neurone->wi=(double*)malloc(num_xi*sizeof(double));//Allouer de la mémoire pour le tableau de poids (weights)(wi)

    //Vérifier si l'allocation de mémoire a réussi
    if (neurone->wi==NULL)
    {
        printf("Erreur : Impossible d'allouer de la mémoire pour les weights du neurone.");
        exit;
    }

    //Initialiser les poids (weight) et le biais (bias) de manière aléatoire
    for (int i=0;i<num_xi;i++)
    {
        neurone->wi[i]=((double)rand()/RAND_MAX)*2-1;//On utilise rand() pour assurer que le nombre soit aléatoire,On divise le nmbre obtenu par RAND_MAX pour obtenir une valeur entre 0 et 1,On maintient la valeur entre -1 et 1 par lamultiplication de 2 et la soustraction de 1
    }
    neurone->bias=((double)rand()/RAND_MAX)*2-1;//Même démarche que wi

    return neurone;
}

//Initialiser une couche de neuron
Couche* initializer_couche(int num_neurones, int num_xi_par_neurone)
{
    Couche* couche=(Couche*)malloc(sizeof(Couche)); //Allouer de la mémoire pour une nouvelle couche

    //Vérifier si l'allocation de mémoire a réussi
    if (couche==NULL)
    {
        printf("Erreur : Impossible d'allouer de la mémoire pour la couche de neurones.\n");
        exit;
    }
    couche->num_neurones=num_neurones;
    couche->neurones=(Neurone**)malloc(num_neurones*sizeof(Neurone*));//Allouer de la mémoire pour le tableau de pointeurs de neurones

    //Vérifier si l'allocation de mémoire a réussi
    if (couche->neurones==NULL)
    {
        printf ("Erreur : Impossible d'allouer de la mémoire pour les neurones de la couche.\n");
        exit;
    }

    //Initialiser les neurones dans la couche
    for (int i=0;i<num_neurones;i++)
    {
        couche->neurones[i]=initializer_neurone(num_xi_par_neurone);
    }

    return couche;
}

//Initializer un réseau neurone
Reseau* initializer_reseau(int num_couches,int* num_neurones,int* num_xi_par_neurone){
    Reseau* reseau=(Reseau*)malloc(sizeof(Reseau));
    //Vérifier si l'allocation de mémoire a réussi
    if (reseau==NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour le réseau neuronal.");
        exit;
    }
    reseau->num_couches=num_couches;
    reseau->couches=(Couche**)malloc(num_couches*sizeof(Couche*));

    //Vérifier si l'allocation de mémoire a réussi
    if (reseau->couches==NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour les couches du réseau neuronal.");
        exit;
    }

    //Saisie des couches
    for (int i=0;i<num_couches;++i) {
        reseau->couches[i]=initializer_couche(num_neurones[i], num_xi_par_neurone[i]);
    }

    return reseau;
}

//Calculer la sortie d'une couche
double compter_couche_yi(Couche* couche, double xi_valeurs[]) {
    double yi;
    // Calculer la sortie du premier neurone
    Neurone *neurone=couche->neurones[0];
    for (int j=0;j<neurone->num_xi;j++) {
        neurone->xi[j]=xi_valeurs[j]; //Assigner les valeurs d'entrée au neurone
    }

    //Calculer la somme pondérée des entrées et du biais
    double somme=neurone->bias;
    for (int j=0;j<neurone->num_xi;j++) {
        somme=somme+(neurone->xi[j]*neurone->wi[j]);//Ajouter le produit pondéré de l'entrée et du poids
    }

    // Appliquer la fonction d'activation appropriée
    switch (neurone->activation_function) {
        case 1:
            return relu(somme);//Renvoyer la sortie calculée
        case 2:
            return sigmoid(somme);//Renvoyer la sortie calculée
        case 3:
            //Appliquer la fonction d'activation Softmax
            softmax(xi_valeurs, neurone->num_xi, &yi);
            return yi;//Renvoyer la sortie calculée
        default:
            return 0.0;//Valeur par défaut si la fonction d'activation n'est pas reconnue
    }
}


// Déclaration de la fonction liberer_reseau
void liberer_reseau(Reseau* reseau) {
    if (reseau == NULL) {
        return;
    }

    // Libérer la mémoire allouée pour chaque couche du réseau
    for (int i = 0; i < reseau->num_couches; ++i) {
        Couche* couche = reseau->couches[i];
        if (couche != NULL) {
            // Libérer la mémoire allouée pour chaque neurone de la couche
            for (int j = 0; j < couche->num_neurones; ++j) {
                Neurone* neurone = couche->neurones[j];
                if (neurone != NULL) {
                    // Libérer la mémoire allouée pour les poids du neurone
                    if (neurone->wi != NULL) {
                        free(neurone->wi);
                    }
                    // Libérer la mémoire allouée pour les entrées du neurone
                    if (neurone->xi != NULL) {
                        free(neurone->xi);
                    }
                    // Libérer la mémoire allouée pour le neurone
                    free(neurone);
                }
            }
            // Libérer la mémoire allouée pour les neurones de la couche
            free(couche->neurones);
            // Libérer la mémoire allouée pour la couche
            free(couche);
        }
    }

    // Libérer la mémoire allouée pour les couches du réseau
    free(reseau->couches);
    // Libérer la mémoire allouée pour le réseau
    free(reseau);
}


#endif
