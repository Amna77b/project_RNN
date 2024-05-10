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
        printf("Erreur d'allocation de m�moire pour le tableau de nombre de neurones par couche.");
        exit;
    }

    // Allouer de la m�moire pour le tableau de nombres d'entr�es par neurone par couche
    *num_xi_par_neurone = (int*)malloc(*num_couches * sizeof(int));
    if (*num_xi_par_neurone == NULL) {
        printf("Erreur d'allocation de m�moire pour le tableau de nombre d'entr�es par neurone par couche.");
        exit;
    }

    // Demander � l'utilisateur le nombre de neurones par couche
    for (int i=0;i<*num_couches;i++) {
        printf("Entrez le nombre de neurones pour la couche %d: ",i+1);
        scanf("%d", &((*num_neurones)[i]));
    }

    // Demander � l'utilisateur le nombre d'entr�es par neurone par couche
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

//Initialiser un neurone avec un nombre d'entr�es donn�
Neurone* initializer_neurone(int num_xi)
{
    Neurone* neurone = (Neurone*)malloc(sizeof(Neurone));
    //V�rifier si l'allocation de m�moire a r�ussi
    if (neurone==NULL)
    {
        printf( "Erreur : Impossible d'allouer de la m�moire pour le neurone.");
        exit;
    }

    neurone->num_xi=num_xi;
    neurone->xi=(double*)malloc(num_xi*sizeof(double));//Allouer de la m�moire pour le tableau d'entr�es (xi)

    //V�rifier si l'allocation de m�moire a r�ussi
    if (neurone->xi==NULL)
    {
        printf( "Erreur : Impossible d'allouer de la m�moire pour les entr�es du neurone.");
        exit;
    }

    neurone->wi=(double*)malloc(num_xi*sizeof(double));//Allouer de la m�moire pour le tableau de poids (weights)(wi)

    //V�rifier si l'allocation de m�moire a r�ussi
    if (neurone->wi==NULL)
    {
        printf("Erreur : Impossible d'allouer de la m�moire pour les weights du neurone.");
        exit;
    }

    //Initialiser les poids (weight) et le biais (bias) de mani�re al�atoire
    for (int i=0;i<num_xi;i++)
    {
        neurone->wi[i]=((double)rand()/RAND_MAX)*2-1;//On utilise rand() pour assurer que le nombre soit al�atoire,On divise le nmbre obtenu par RAND_MAX pour obtenir une valeur entre 0 et 1,On maintient la valeur entre -1 et 1 par lamultiplication de 2 et la soustraction de 1
    }
    neurone->bias=((double)rand()/RAND_MAX)*2-1;//M�me d�marche que wi

    return neurone;
}

//Initialiser une couche de neuron
Couche* initializer_couche(int num_neurones, int num_xi_par_neurone)
{
    Couche* couche=(Couche*)malloc(sizeof(Couche)); //Allouer de la m�moire pour une nouvelle couche

    //V�rifier si l'allocation de m�moire a r�ussi
    if (couche==NULL)
    {
        printf("Erreur : Impossible d'allouer de la m�moire pour la couche de neurones.\n");
        exit;
    }
    couche->num_neurones=num_neurones;
    couche->neurones=(Neurone**)malloc(num_neurones*sizeof(Neurone*));//Allouer de la m�moire pour le tableau de pointeurs de neurones

    //V�rifier si l'allocation de m�moire a r�ussi
    if (couche->neurones==NULL)
    {
        printf ("Erreur : Impossible d'allouer de la m�moire pour les neurones de la couche.\n");
        exit;
    }

    //Initialiser les neurones dans la couche
    for (int i=0;i<num_neurones;i++)
    {
        couche->neurones[i]=initializer_neurone(num_xi_par_neurone);
    }

    return couche;
}

//Initializer un r�seau neurone
Reseau* initializer_reseau(int num_couches,int* num_neurones,int* num_xi_par_neurone){
    Reseau* reseau=(Reseau*)malloc(sizeof(Reseau));
    //V�rifier si l'allocation de m�moire a r�ussi
    if (reseau==NULL) {
        printf("Erreur : Impossible d'allouer de la m�moire pour le r�seau neuronal.");
        exit;
    }
    reseau->num_couches=num_couches;
    reseau->couches=(Couche**)malloc(num_couches*sizeof(Couche*));

    //V�rifier si l'allocation de m�moire a r�ussi
    if (reseau->couches==NULL) {
        printf("Erreur : Impossible d'allouer de la m�moire pour les couches du r�seau neuronal.");
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
        neurone->xi[j]=xi_valeurs[j]; //Assigner les valeurs d'entr�e au neurone
    }

    //Calculer la somme pond�r�e des entr�es et du biais
    double somme=neurone->bias;
    for (int j=0;j<neurone->num_xi;j++) {
        somme=somme+(neurone->xi[j]*neurone->wi[j]);//Ajouter le produit pond�r� de l'entr�e et du poids
    }

    // Appliquer la fonction d'activation appropri�e
    switch (neurone->activation_function) {
        case 1:
            return relu(somme);//Renvoyer la sortie calcul�e
        case 2:
            return sigmoid(somme);//Renvoyer la sortie calcul�e
        case 3:
            //Appliquer la fonction d'activation Softmax
            softmax(xi_valeurs, neurone->num_xi, &yi);
            return yi;//Renvoyer la sortie calcul�e
        default:
            return 0.0;//Valeur par d�faut si la fonction d'activation n'est pas reconnue
    }
}


// D�claration de la fonction liberer_reseau
void liberer_reseau(Reseau* reseau) {
    if (reseau == NULL) {
        return;
    }

    // Lib�rer la m�moire allou�e pour chaque couche du r�seau
    for (int i = 0; i < reseau->num_couches; ++i) {
        Couche* couche = reseau->couches[i];
        if (couche != NULL) {
            // Lib�rer la m�moire allou�e pour chaque neurone de la couche
            for (int j = 0; j < couche->num_neurones; ++j) {
                Neurone* neurone = couche->neurones[j];
                if (neurone != NULL) {
                    // Lib�rer la m�moire allou�e pour les poids du neurone
                    if (neurone->wi != NULL) {
                        free(neurone->wi);
                    }
                    // Lib�rer la m�moire allou�e pour les entr�es du neurone
                    if (neurone->xi != NULL) {
                        free(neurone->xi);
                    }
                    // Lib�rer la m�moire allou�e pour le neurone
                    free(neurone);
                }
            }
            // Lib�rer la m�moire allou�e pour les neurones de la couche
            free(couche->neurones);
            // Lib�rer la m�moire allou�e pour la couche
            free(couche);
        }
    }

    // Lib�rer la m�moire allou�e pour les couches du r�seau
    free(reseau->couches);
    // Lib�rer la m�moire allou�e pour le r�seau
    free(reseau);
}


#endif
