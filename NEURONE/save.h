#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "description.h" // Assumant que le type Reseau et Neurone sont définis dans "description.h"

#ifndef NEURONE_SAVE_H
#define NEURONE_SAVE_H

// Sauvegarder les poids et les biais dans un fichier texte
void sauvegarder_reseau(Reseau* reseau, const char* fichier) {
    int fd = open(fichier, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char buffer[256]; // Tampon de lecture/écriture

    for (int i = 0; i < reseau->num_couches; ++i) {
        for (int j = 0; j < reseau->couches[i]->num_neurones; ++j) {
            Neurone* neurone = reseau->couches[i]->neurones[j];
            int offset = 0;

            for (int k = 0; k < neurone->num_xi; ++k) {
                offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%.6lf,", neurone->wi[k]);
            }
            snprintf(buffer + offset, sizeof(buffer) - offset, "%.6lf\n", neurone->bias);

            if (write(fd, buffer, sizeof(buffer)) == -1) {
                perror("Erreur lors de l'écriture dans le fichier");
                close(fd);
                exit(EXIT_FAILURE);
            }
        }
    }

    close(fd);
}

// Charger les poids et les biais depuis un fichier texte
void charger_reseau(Reseau* reseau, const char* fichier) {
    int fd = open(fichier, O_RDONLY);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char buffer[256]; // Tampon de lecture/écriture
    char* token;
    const char* delimiter = ",";

    for (int i = 0; i < reseau->num_couches; ++i) {
        for (int j = 0; j < reseau->couches[i]->num_neurones; ++j) {
            Neurone* neurone = reseau->couches[i]->neurones[j];
            if (read(fd, buffer, sizeof(buffer)) == -1) {
                perror("Erreur lors de la lecture du fichier");
                close(fd);
                exit(EXIT_FAILURE);
            }

            // Parsing des poids à partir du buffer
            token = strtok(buffer, delimiter);
            for (int k = 0; k < neurone->num_xi && token != NULL; ++k) {
                neurone->wi[k] = atof(token);
                token = strtok(NULL, delimiter);
            }

            // Lecture du biais
            token = strtok(NULL, delimiter);
            neurone->bias = atof(token);
        }
    }

    close(fd);
}

#endif

