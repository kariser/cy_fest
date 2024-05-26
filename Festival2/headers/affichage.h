#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#define couleur(code_couleur) printf("\033[%sm", code_couleur)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/salle.h"

/**
 * Effacer l'écran
*/
void effacer_ecran();

/**
 * Ecrire du texte en rouge
*/
void ecrire_texte_rouge(char* texte);

/**
 * Ecrire du texte en vert
*/
void ecrire_texte_vert(char* texte);

/**
 * Ecrire du texte en jaune
*/
void ecrire_texte_jaune(char* texte);

/**
 * Ecrire du texte en bleu
*/
void ecrire_texte_bleu(char* texte);

/**
 * Ecrire un caractère en rouge
*/
void ecrire_caractere_rouge(char caractere);

/**
 * Ecrire un caractère en vert
*/
void ecrire_caractere_vert(char caractere);

/**
 * Ecrire un caractère en jaune
*/
void ecrire_caractere_vert(char caractere);

/**
 * Ecrire un caractère en bleu
*/
void ecrire_caractere_bleu(char caractere);

/**
 * Afficher une salle
*/
void afficher_salle(SALLE* salle);

/**
 * Afficher la liste des salles
*/
void afficher_liste_salle(SALLE** salles);

#endif