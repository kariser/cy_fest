#include "../headers/affichage.h"

/**
 * Effacer l'écran
*/
void effacer_ecran()
{
    printf("\033[H\033[2J");
}

/**
 * Ecrire du texte en rouge
*/
void ecrire_texte_rouge(char* texte)
{
    couleur("31");
    printf("%s", texte);
    couleur("0");
}

/**
 * Ecrire du texte en vert
*/
void ecrire_texte_vert(char* texte)
{
    couleur("32");
    printf("%s", texte);
    couleur("0");
}

/**
 * Ecrire du texte en jaune
*/
void ecrire_texte_jaune(char* texte)
{
    couleur("33");
    printf("%s", texte);
    couleur("0");
}

/**
 * Ecrire du texte en bleu
*/
void ecrire_texte_bleu(char* texte)
{
    couleur("34");
    printf("%s", texte);
    couleur("0");
}

/**
 * Ecrire un caractère en rouge
*/
void ecrire_caractere_rouge(char caractere)
{
    couleur("31");
    printf("%c", caractere);
    couleur("0");
}

/**
 * Ecrire un caractère en vert
*/
void ecrire_caractere_vert(char caractere)
{
    couleur("32");
    printf("%c", caractere);
    couleur("0");
}

/**
 * Ecrire un caractère en jaune
*/
void ecrire_caractere_jaune(char caractere)
{
    couleur("33");
    printf("%c", caractere);
    couleur("0");
}

/**
 * Ecrire un caractère en bleu
*/
void ecrire_caractere_bleu(char caractere)
{
    couleur("34");
    printf("%c", caractere);
    couleur("0");
}

/**
 * Afficher une salle
*/
void afficher_salle(SALLE* salle)
{
    if (salle==NULL)
    {
        return;
    }

    printf("\n\n-----------------------------------------------------\n\n");    
    printf("SALLE : ");
    ecrire_texte_bleu(salle->nom);
    printf("\n");
    switch (salle->etat)
    {
    case RESERVATIONS_EN_COURS:
        printf("Evènement à venir : %s\n", salle->nom_evenement);
        printf("Fin de l'évènement à %d:%d\n\n", salle->heure_fin.tm_hour, salle->heure_fin.tm_min);
        break;
        
    case RESERVATIONS_TERMINEES:
        printf("Evènement terminé : %s\n", salle->nom_evenement);
        printf("Terminé à %d:%d\n\n", salle->heure_fin.tm_hour, salle->heure_fin.tm_min);
        break;
        
    case LIBRE:
        printf("Aucun évènement en cours dans cette salle\n\n");
        break;
    
    default:
        break;
    }

    // Affichage de repère en haut (7 spaces)
    int max_repere_horizontal = 0;
    for (int i = 0; i < salle->nb_rangee; i++)
    {
        max_repere_horizontal = (max_repere_horizontal < salle->nb_siege_par_rangee[i]) ? salle->nb_siege_par_rangee[i] : max_repere_horizontal;
    }
    printf("       ");
    for (int i = 0; i < max_repere_horizontal; i++)
    {
        printf("%d", i+1);
        if (i+1<10)
        {
            printf(" ");
        }
        if (i+1<100)
        {
            printf(" ");
        }
    }
    printf("\n");

    // Affichage des sièges de catégorie A
    for (int i = 0; i < salle->nb_rangee_A; i++)
    {
        printf("R %03d  ", i);
        for (int j = 0; j < salle->nb_siege_par_rangee[i]; j++)
        {
            if (!(salle->avec_fausse && salle->etat==RESERVATIONS_EN_COURS))
            {
                if (salle->sieges[i][j]=='0') // Siège libre
                {
                    ecrire_caractere_vert(salle->sieges[i][j]);
                }
                else // Siège occupé
                {
                    ecrire_caractere_rouge(salle->sieges[i][j]);
                }
            }
            else // Sièges retirés
            {
                ecrire_caractere_vert('.');
            }
            printf("  ");
        }
        printf("\n");
    }

    // Affichage des sièges de catégorie B
    for (int i = salle->nb_rangee_A; i < salle->nb_rangee_A+salle->nb_rangee_B; i++)
    {
        printf("R %03d  ", i);
        for (int j = 0; j < salle->nb_siege_par_rangee[i]; j++)
        {
            if (salle->sieges[i][j]=='0') // Siège libre
            {
                ecrire_caractere_jaune(salle->sieges[i][j]);
            }
            else // Siège occupé
            {
                ecrire_caractere_rouge(salle->sieges[i][j]);
            }
            printf("  ");
        }
        printf("\n");
    }

    // Affichage des sièges de catégorie C
    for (int i = salle->nb_rangee_A+salle->nb_rangee_B; i < salle->nb_rangee; i++)
    {
        printf("R %03d  ", i);
        for (int j = 0; j < salle->nb_siege_par_rangee[i]; j++)
        {
            if (salle->sieges[i][j]=='0') // Siège libre
            {
                printf("%c", salle->sieges[i][j]);
            }
            else // Siège occupé
            {
                ecrire_caractere_rouge(salle->sieges[i][j]);
            }
            printf("  ");
        }
        printf("\n");
    }
    printf("\n");

    // Légende
    printf("Légende : \n");
    ecrire_caractere_vert('0');
    printf(" - Catégorie A (%d euros)\n", salle->prix_cat_A);
    ecrire_caractere_jaune('0');
    printf(" - Catégorie B (%d euros)\n", salle->prix_cat_B);
    printf("0 - Catégorie C (%d euros)\n", salle->prix_cat_C);

    printf("Nombre de sièges réservés : %d\n", salle->nb_siege_reserve);
    printf("Nombre de sièges au total : %d\n", salle->nb_siege);

    printf("\n-----------------------------------------------------\n\n");
}

/**
 * Afficher la liste des salles
*/
void afficher_liste_salle(SALLE** salles)
{
    printf("\n\nLISTE DES SALLES :\n\n");
    if (salles==NULL || (salles!=NULL && salles[0]==NULL))
    {
        ecrire_texte_jaune("LISTE VIDE !\n");
    }
    else
    {
        int i=0;
        while (salles[i]!=NULL)
        {
            printf("%d - ", i+1);
            ecrire_texte_bleu(salles[i]->nom);
            printf(" (%d sièges)\n", salles[i]->nb_siege);
            i++;
        }
    }
    printf("\n");
}