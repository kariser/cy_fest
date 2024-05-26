#include "../headers/entree_sortie.h"
#include "../headers/affichage.h"
#include "entree_sortie.h"

/**
 * Récupère une chaine de caractère
*/
char* recuperer_chaine(int taille, char* message)
{
    char* chaine = (char*)malloc(taille*sizeof(char));
    if (chaine!=NULL)
    {
        char caractere = ' ';
        int i = 0;
        printf("%s", message);
        while (caractere!='\n' && i<taille)
        {
            caractere = getc(stdin);
            chaine[i] = caractere;
            i++;
        }
        chaine[i] = '\0';
        return chaine;
    }
    return NULL;
}

/**
 * Récupère un entier se trouvant dans l'intervalle des deux entiers entrés en paramètre
*/
int recuperer_entier(int minimum, int maximum, char* message)
{
    char* chaine = NULL;
    int entier = 0;
    do
    {
        printf("%s (MIN : %d | MAX : %d) : ", message, minimum, maximum);
        chaine = recuperer_chaine(10, "");
        entier = atoi(chaine);
        free(chaine);
    }while (entier<minimum || entier>maximum);
    
    return entier;
}

/**
 * Enrégistre toutes les salles dans un fichier
*/
void enregistrer_salles(SALLE** salles, char* nom_fichier)
{
    // Ouvrir le fichier en mode écriture
    FILE* fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        ecrire_texte_rouge("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    int total = 0;
    while (salles[total]!=NULL)
    {
        total++;
    }
    fprintf(fichier, "%d\n", total);

    for (int i = 0; i < total; i++)
    {
        /*for (int j = 0; j < strlen(salles[i]->nom); i++)
        {
            if (salles[i]->nom[j]=='\n')
            {
                salles[i]->nom[j] = ' ';
            }
        }
        for (int j = 0; j < strlen(salles[i]->nom_evenement); i++)
        {
            if (salles[i]->nom_evenement[j]=='\n')
            {
                salles[i]->nom_evenement[j] = ' ';
            }
        }*/
        fprintf(fichier, "%s\n", salles[i]->nom);
        fprintf(fichier, "%d\n", salles[i]->nb_rangee);
        fprintf(fichier, "%d\n", salles[i]->nb_siege_fausse);
        fprintf(fichier, "%d\n", salles[i]->nb_rangee);
        for (int j = 0; j < salles[i]->nb_rangee; j++)
        {
            fprintf(fichier, "%d\n", salles[i]->nb_siege_par_rangee[j]);
        }
        fprintf(fichier, "%d\n", salles[i]->nb_rangee_A);
        fprintf(fichier, "%d\n", salles[i]->nb_rangee_B);
        fprintf(fichier, "%d\n", salles[i]->nb_rangee_C);
        for (int j = 0; j < salles[i]->nb_rangee; j++)
        {
            for (int k = 0; k < salles[i]->nb_siege_par_rangee[j]; k++)
            {
                fprintf(fichier, "%c", salles[i]->sieges[j][k]);
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "%d\n", salles[i]->nb_siege_reserve);
        switch (salles[i]->etat)
        {
        case LIBRE:
            fprintf(fichier, "LIBRE\n");
            break;
            
        case RESERVATIONS_EN_COURS:
            fprintf(fichier, "RESERVATIONS_EN_COURS\n");
            break;
            
        case RESERVATIONS_TERMINEES:
            fprintf(fichier, "RESERVATIONS_TERMINEES\n");
            break;
        
        default:
            fprintf(fichier, "\n");
            break;
        }
        fprintf(fichier, "%s\n", salles[i]->nom_evenement);
        if (salles[i]->avec_fausse)
        {
            fprintf(fichier, "AVEC_FAUSSE\n");
        }
        else
        {
            fprintf(fichier, "SANS_FAUSSE\n");
        }
        fprintf(fichier, "%d:%d\n", salles[i]->heure_fin.tm_hour, salles[i]->heure_fin.tm_min);
        fprintf(fichier, "%d\n", salles[i]->prix_cat_A);
        fprintf(fichier, "%d\n", salles[i]->prix_cat_B);
        fprintf(fichier, "%d\n", salles[i]->prix_cat_C);
    }
    fclose(fichier);
}

/**
 * Restaurer toutes les salles enrégistrées dans le fichier passé en paramètre
*/
SALLE** restaurer_salles(char* nom_fichier)
{
    // Ouvrir le fichier en mode lecture
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    // Lire le nombre total de salles enregistrées
    int total;
    fscanf(fichier, "%d", &total);

    // Allouer de la mémoire pour le tableau de pointeurs vers les structures SALLE
    SALLE** salles = (SALLE**)malloc(NOMBRE_MAX_SALLE * sizeof(SALLE*));
    if (salles == NULL) {
        ecrire_texte_rouge("Erreur d'allocation de mémoire.\n");
        fclose(fichier);
        return NULL;
    }

    // Parcourir les salles enregistrées dans le fichier
    for (int i = 0; i < total; i++) {
        // Allouer de la mémoire pour une nouvelle structure SALLE
        salles[i] = (SALLE*)malloc(sizeof(SALLE));
        if (salles[i] == NULL) {
            ecrire_texte_rouge("Erreur d'allocation de mémoire.\n");
            fclose(fichier);
            // Libérer la mémoire allouée précédemment pour les structures SALLE
            for (int j = 0; j < i; j++) {
                free(salles[j]);
            }
            free(salles);
            return NULL;
        }

        // Lire les membres de la structure SALLE depuis le fichier
        salles[i]->nom = lire_ligne(fichier);
        fscanf(fichier, "%d", &(salles[i]->nb_rangee));
        fscanf(fichier, "%d", &(salles[i]->nb_siege_fausse));
        for (int j = 0; j < salles[i]->nb_rangee; j++) {
            fscanf(fichier, "%d", &(salles[i]->nb_siege_par_rangee[j]));
        }
        fscanf(fichier, "%d", &(salles[i]->nb_rangee_A));
        fscanf(fichier, "%d", &(salles[i]->nb_rangee_B));
        fscanf(fichier, "%d", &(salles[i]->nb_rangee_C));
        for (int j = 0; j < salles[i]->nb_rangee; j++) {
            fscanf(fichier, "%s", salles[i]->sieges[j]);
        }
        fscanf(fichier, "%d", &(salles[i]->nb_siege_reserve));
        char etat[20];
        fscanf(fichier, "%s", etat);
        if (strcmp(etat, "LIBRE") == 0) {
            salles[i]->etat = LIBRE;
        } else if (strcmp(etat, "RESERVATIONS_EN_COURS") == 0) {
            salles[i]->etat = RESERVATIONS_EN_COURS;
        } else if (strcmp(etat, "RESERVATIONS_TERMINEES") == 0) {
            salles[i]->etat = RESERVATIONS_TERMINEES;
        }
        salles[i]->nom_evenement = lire_ligne(fichier);
        char avec_fausse[20];
        fscanf(fichier, "%s", avec_fausse);
        salles[i]->avec_fausse = (strcmp(avec_fausse, "AVEC_FAUSSE") == 0) ? 1 : 0;
        fscanf(fichier, "%d:%d", &(salles[i]->heure_fin.tm_hour), &(salles[i]->heure_fin.tm_min));
        fscanf(fichier, "%d", &(salles[i]->prix_cat_A));
        fscanf(fichier, "%d", &(salles[i]->prix_cat_B));
        fscanf(fichier, "%d", &(salles[i]->prix_cat_C));
    }

    // Fermer le fichier
    fclose(fichier);

    return salles;
}

/**
 * Fonction utilitaire pour lire une ligne de texte depuis un fichier
*/
char* lire_ligne(FILE* fichier) {
    char* ligne = NULL;
    size_t taille = 0;
    // getline(&ligne, &taille, fichier);
    fgets(&ligne, TAILLE_MAX_CHAINE, fichier);
    // Supprimer le caractère de nouvelle ligne (\n) à la fin de la ligne si présent
    if (ligne[strlen(ligne) - 1] == '\n') {
        ligne[strlen(ligne) - 1] = '\0';
    }
    return ligne;
}