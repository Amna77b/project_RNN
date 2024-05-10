#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Définition de la structure Neurone
typedef struct {
    int num_entrees;     // Nombre d'entrées pour ce neurone
    double *poids;       // Poids associés à chaque entrée
    double *entrees;     // Valeurs des entrées
    double sortie;       // Sortie du neurone après activation
} Neurone;

// Définition de la structure Couche
typedef struct {
    int num_neurones;    // Nombre de neurones dans la couche
    Neurone **neurones;  // Tableau de pointeurs vers les neurones de cette couche
} Couche;

// Fonction pour initialiser un réseau avec les spécifications données
Couche *initialiser_reseau(int num_couches, int *num_neurones, int *num_entrees) {
    Couche *reseau = (Couche *)malloc(num_couches * sizeof(Couche));

    for (int i = 0; i < num_couches; i++) {
        reseau[i].num_neurones = num_neurones[i];
        reseau[i].neurones = (Neurone **)malloc(num_neurones[i] * sizeof(Neurone *));
        
        for (int j = 0; j < num_neurones[i]; j++) {
            Neurone *neurone = (Neurone *)malloc(sizeof(Neurone));
            neurone->num_entrees = num_entrees[i];
            neurone->poids = (double *)malloc(num_entrees[i] * sizeof(double));
            neurone->entrees = (double *)malloc(num_entrees[i] * sizeof(double));
            neurone->sortie = 0.0;
            reseau[i].neurones[j] = neurone;
        }
    }

    return reseau;
}

// Fonction pour saisir les valeurs des entrées pour la première couche
void saisie_valeurs_premiere_couche(Couche *premiere_couche) {
    printf("Saisie des valeurs pour la première couche :\n");

    for (int i = 0; i < premiere_couche->num_neurones; i++) {
        printf("Valeurs d'entrée pour le neurone %d :\n", i + 1);
        
        for (int j = 0; j < premiere_couche->neurones[i]->num_entrees; j++) {
            printf("Entrée %d : ", j + 1);
            scanf("%lf", &(premiere_couche->neurones[i]->entrees[j]));
        }
    }
}

// Fonction principale
int main() {
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    int num_couches;
    printf("Nombre de couches : ");
    scanf("%d", &num_couches);

    int *num_neurones = (int *)malloc(num_couches * sizeof(int));
    int *num_entrees = (int *)malloc(num_couches * sizeof(int));

    for (int i = 0; i < num_couches; i++) {
        printf("Nombre de neurones dans la couche %d : ", i + 1);
        scanf("%d", &num_neurones[i]);

        printf("Nombre d'entrées par neurone dans la couche %d : ", i + 1);
        scanf("%d", &num_entrees[i]);
    }

    // Initialisation du réseau neuronal
    Couche *reseau = initialiser_reseau(num_couches, num_neurones, num_entrees);

    // Saisie des valeurs pour la première couche
    saisie_valeurs_premiere_couche(&reseau[0]);

    // Afficher les sorties de la première couche
    printf("\nSortie de la premiere couche :\n");
    for (int i = 0; i < reseau[0].num_neurones; i++) {
        printf("Sortie du neurone %d : %.2f\n", i + 1, reseau[0].neurones[i]->sortie);
    }

    // Libération de la mémoire allouée
    for (int i = 0; i < num_couches; i++) {
        for (int j = 0; j < num_neurones[i]; j++) {
            free(reseau[i].neurones[j]->poids);
            free(reseau[i].neurones[j]->entrees);
            free(reseau[i].neurones[j]);
        }
        free(reseau[i].neurones);
    }
    free(reseau);
    free(num_neurones);
    free(num_entrees);

    return 0;
}
