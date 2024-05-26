#include <stdio.h>
#include <stdlib.h>
#include "./headers/salle.h"
#include "./headers/affichage.h"
#include "./headers/entree_sortie.h"
#include <locale.h>

int main()
{
    int nb_salles = 0;
    SALLE** salles = (SALLE**)malloc(NOMBRE_MAX_SALLE * sizeof(SALLE*));
    for (int i = 0; i < NOMBRE_MAX_SALLE; i++)
    {
        salles[i] = NULL;
    }

    // Exemple d'utilisation :
    // Ajout d'une salle 
    salles[nb_salles] = creer_salle(salles, &nb_salles);

    // Sauvegarde la liste dans un fichier salles.txt
    enregistrer_salles(salles, "salles.txt");

    // Libération de la mémoire
    liberer_memoire_salles(&salles);
    return 0;
}
