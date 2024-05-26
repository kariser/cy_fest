#ifndef SALLE_H
#define SALLE_H

#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOMBRE_MAX_SALLE 100
#define TAILLE_MAX_CHAINE 256
#define TAILLE_MAX_TABLEAU 256
#define TAILLE_MAX_RANGEE 256
#define TAILLE_MAX_SIEGES_PAR_RANGEE 256
#define PRIX_MAX_PAR_SIEGE 1000

typedef struct tm HEURE;

/**
 * Etat d'une salle
*/
typedef enum etat_salle 
{
    LIBRE = 1, RESERVATIONS_EN_COURS, RESERVATIONS_TERMINEES
} ETAT_SALLE;

/**
 * Structure représentant une salle
*/
typedef struct salle
{
    char* nom;
    int nb_siege;
    int nb_siege_fausse;
    int nb_rangee;
    int nb_siege_par_rangee[TAILLE_MAX_RANGEE];
    int nb_rangee_A;
    int nb_rangee_B;
    int nb_rangee_C;
    char sieges[TAILLE_MAX_RANGEE][TAILLE_MAX_SIEGES_PAR_RANGEE];
    int nb_siege_reserve;
    ETAT_SALLE etat;
    char* nom_evenement;
    bool avec_fausse;
    HEURE heure_fin;
    int prix_cat_A;
    int prix_cat_B;
    int prix_cat_C;
} SALLE;

/**
 * Créer une nouvelle salle
*/
SALLE* creer_salle(SALLE** salles, int* nb_salle);

/**
 * Rechercher une salle avec son nom
*/
SALLE* rechercher_salle(SALLE** salles, char* nom);

/**
 * Attribuer un concert à une salle
*/
void attribuer_concert(SALLE* salle_a_attribuer);

/**
 * Modifier la configuration d'une salle et programmer le prochain évènement
*/
void modifier_configuration(SALLE** salles);

/**
 * Réserver une place
*/
void reserver_place(SALLE** salles);

/**
 * Actualise l'état de la salle en comparant l'heure de fin d'évènement et l'heure actuelle
*/
void actualiser_etat_salle(SALLE* salle);

/**
 * Libère la mémoire occupée par les salles
*/
void liberer_memoire_salles(SALLE*** salles);

#endif