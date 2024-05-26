#ifndef ENTREE_SORTIE_H
#define ENTREE_SORTIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salle.h"

/**
 * Récupère une chaine de caractère
*/
char* recuperer_chaine(int taille, char* message);

/**
 * Récupère un entier se trouvant dans l'intervalle des deux entiers entrés en paramètre
*/
int recuperer_entier(int minimum, int maximum, char* message);

/**
 * Enrégistre toutes les salles dans un fichier
*/
void enregistrer_salles(SALLE** salles, char* nom_fichier);

/**
 * Restaurer toutes les salles enrégistrées dans le fichier passé en paramètre
*/
SALLE** restaurer_salles(char* nom_fichier);

/**
 * Fonction utilitaire pour lire une ligne de texte depuis un fichier
*/
char* lire_ligne(FILE* fichier);

#endif