#include "../headers/salle.h"
#include "../headers/entree_sortie.h"
#include "../headers/affichage.h"
#include "salle.h"

/**
 * Créer une nouvelle salle
*/
SALLE* creer_salle(SALLE** salles, int* nb_salle)
{
    if (!(*nb_salle<NOMBRE_MAX_SALLE))
    {
        ecrire_texte_rouge("Impossible d'ajouter une salle ! Nombre maximal de salle atteint !");
        return NULL;
    }
    
    SALLE* nouvelle_salle = (SALLE*)malloc(sizeof(SALLE));
    if (nouvelle_salle!=NULL)
    {
        // Initialisation de toutes les variables de la Salle.
        do
        {
            nouvelle_salle->nom = recuperer_chaine(TAILLE_MAX_CHAINE, "Entrez le nom de la Salle : ");
        } while (rechercher_salle(salles, nouvelle_salle->nom)!=NULL);
        nouvelle_salle->nb_rangee = recuperer_entier(1, TAILLE_MAX_RANGEE, "Entrez le nombre de rangée");

        for (int i = 0; i < TAILLE_MAX_RANGEE; i++)
        {
            for (int j = 0; j < TAILLE_MAX_SIEGES_PAR_RANGEE; j++)
            {
                nouvelle_salle->sieges[i][j] = '.';
            }
        }

        printf("Entrez le nombre de siège pour chaque rangée :\n");  
        nouvelle_salle->nb_siege = 0;      
        for (int i = 0; i < nouvelle_salle->nb_rangee; i++)
        {
            char message[TAILLE_MAX_CHAINE];
            snprintf(message, TAILLE_MAX_CHAINE, "Nombre de siège dans la rangée %d", i+1);
            nouvelle_salle->nb_siege_par_rangee[i] = recuperer_entier(1, TAILLE_MAX_SIEGES_PAR_RANGEE, message);
            for (int j = 0; j < nouvelle_salle->nb_siege_par_rangee[i]; j++)
            {
                nouvelle_salle->sieges[i][j] = '0';
            }
            nouvelle_salle->nb_siege += nouvelle_salle->nb_siege_par_rangee[i];
        }
        nouvelle_salle->nb_rangee_A = recuperer_entier(1, nouvelle_salle->nb_rangee-1, "Entrez le nombre de rangées de catégorie A");
        nouvelle_salle->nb_rangee_B = recuperer_entier(1, nouvelle_salle->nb_rangee - nouvelle_salle->nb_rangee_A, "Entrez le nombre de rangées de catégorie B");
        nouvelle_salle->nb_rangee_C = 0;
        if (nouvelle_salle->nb_rangee - nouvelle_salle->nb_rangee_A - nouvelle_salle->nb_rangee_B > 0)
        {
            nouvelle_salle->nb_rangee_C = nouvelle_salle->nb_rangee - nouvelle_salle->nb_rangee_A - nouvelle_salle->nb_rangee_B;
        }
        printf("La catégorie C aura %d rangées\n", nouvelle_salle->nb_rangee_C);
        nouvelle_salle->nb_siege_reserve = 0;
        nouvelle_salle->etat = LIBRE;
        nouvelle_salle->nom_evenement = NULL;
        nouvelle_salle->avec_fausse = false;
        nouvelle_salle->heure_fin.tm_hour = 0;
        nouvelle_salle->heure_fin.tm_min = 0;
        nouvelle_salle->heure_fin.tm_sec = 0;
        nouvelle_salle->prix_cat_A = 0;
        nouvelle_salle->prix_cat_B = 0;
        nouvelle_salle->prix_cat_C = 0;
        salles[*nb_salle] = nouvelle_salle;
        *nb_salle = *nb_salle + 1;
        // Affichage de la nouvelle Salle
        afficher_salle(nouvelle_salle);

        return nouvelle_salle;
    }
    ecrire_texte_rouge("\nSalle non créée !! Erreur d'allocation dynamique !\n\n");
    return NULL;
}

/**
 * Rechercher une Salle avec son nom
*/
SALLE* rechercher_salle(SALLE** salles, char* nom)
{
    int i = 0;
    while (i<NOMBRE_MAX_SALLE && salles[i]!=NULL)
    {
        if (strcmp(nom, salles[i]->nom)==0)
        {
            return salles[i];
        }
        i++;
    }
    return NULL;
}

/**
 * Attribuer un concert à une salle
*/
void attribuer_concert(SALLE* salle_a_attribuer)
{
    salle_a_attribuer->nom_evenement = recuperer_chaine(TAILLE_MAX_CHAINE, "Entrez le nom de l'évènement : ");
    printf("Evènement avec fausse ? (o = Oui | n = Non) : ");
    char choix=' ';
    do
    {
        choix = getc(stdin);
    } while (choix!='o' && choix!='O' && choix!='n' && choix!='N');

    // Modification de la configuration de la salle s'il s'agit d'une salle existente
    if (salle_a_attribuer->etat==RESERVATIONS_TERMINEES)
    {
        salle_a_attribuer->nb_rangee_A = recuperer_entier(1, salle_a_attribuer->nb_rangee-1, "Entrez le nombre de rangées de catégorie A");
        salle_a_attribuer->nb_rangee_B = recuperer_entier(1, salle_a_attribuer->nb_rangee - salle_a_attribuer->nb_rangee_A, "Entrez le nombre de rangées de catégorie B");
        salle_a_attribuer->nb_rangee_C = 0;
        if (salle_a_attribuer->nb_rangee - salle_a_attribuer->nb_rangee_A - salle_a_attribuer->nb_rangee_B > 0)
        {
            salle_a_attribuer->nb_rangee_C = salle_a_attribuer->nb_rangee - salle_a_attribuer->nb_rangee_A - salle_a_attribuer->nb_rangee_B;
        }
        printf("La catégorie C aura %d rangées\n", salle_a_attribuer->nb_rangee_C);
    }

    // Initialisation du nombre de place en fonction de la présence ou non de fausse
    salle_a_attribuer->nb_siege = 0;
    salle_a_attribuer->nb_siege_fausse = 0;
    if (choix=='o') // On retire les sièges de catégorie A
    {
        // On rajoute de la place pour chaque siège de catégorie A retiré
        salle_a_attribuer->avec_fausse = true;
        for (int i = 0; i < salle_a_attribuer->nb_rangee_A; i++)
        {
            salle_a_attribuer->nb_siege += salle_a_attribuer->nb_siege_par_rangee[i];
            salle_a_attribuer->nb_siege_fausse += 2 * salle_a_attribuer->nb_siege_par_rangee[i];
        }
    }
    else
    {
        salle_a_attribuer->avec_fausse = false;
    }
    // Mise à jour du nombre de place
    for (int i = 0; i < salle_a_attribuer->nb_rangee; i++)
    {
        salle_a_attribuer->nb_siege += salle_a_attribuer->nb_siege_par_rangee[i];
    }
    salle_a_attribuer->nb_siege_reserve = 0;
    printf("Entrez l'heure et la minute de fin du concert :\n");
    salle_a_attribuer->heure_fin.tm_hour = recuperer_entier(0, 23, "Heure");
    salle_a_attribuer->heure_fin.tm_min = recuperer_entier(0, 59, "Minute");
    salle_a_attribuer->prix_cat_A = recuperer_entier(0, PRIX_MAX_PAR_SIEGE, "Prix des places de catégorie A");
    if (salle_a_attribuer->nb_rangee_B!=0)
    {
        salle_a_attribuer->prix_cat_B = recuperer_entier(0, PRIX_MAX_PAR_SIEGE, "Prix des places de catégorie B");
    }
    if (salle_a_attribuer->nb_rangee_C!=0)
    {
        salle_a_attribuer->prix_cat_C = recuperer_entier(0, PRIX_MAX_PAR_SIEGE, "Prix des places de catégorie C");
    }
    salle_a_attribuer->etat = RESERVATIONS_EN_COURS;
    // Affichage de la salle réservée
    afficher_salle(salle_a_attribuer);
}

/**
 * Modifier la configuration d'une salle et programmer le prochain évènement
*/
void modifier_configuration(SALLE** salles)
{
    SALLE* salle = NULL;
    do
    {
        char* nom = recuperer_chaine(TAILLE_MAX_CHAINE, "Entrez le nom de la Salle à configurer : ");
        salle = rechercher_salle(salles, nom);
    } while (salle==NULL);
    attribuer_concert(salle);
}

/**
 * Réserver une place
*/
void reserver_place(SALLE** salles)
{
    SALLE* salle = NULL;
    do
    {
        char* nom = recuperer_chaine(TAILLE_MAX_CHAINE, "Entrez le nom de la Salle dans laquelle vous voulez réserver : ");
        salle = rechercher_salle(salles, nom);
        actualiser_etat_salle(salle);
        if (salle!=NULL && salle->etat==RESERVATIONS_TERMINEES)
        {
            ecrire_texte_jaune("Les réservations sont déjà terminées dans cette salle ! Choisissez une autre.\n");
            salle = NULL;
        }
        if (salle!=NULL && salle->nb_siege_reserve==salle->nb_siege)
        {
            ecrire_texte_jaune("Il n'y a plus de place dans cette salle !\n");
            salle = NULL;
        }
    } while (salle==NULL);

    char choix = ' ';
    if (salle->avec_fausse)
    {
        printf("Réserver une place dans la fausse ou un siège ? (f = fausse | s = siège) : ");
        choix = getc(stdin);
    }
    else
    {
        choix = 's';
    }
    
    if (choix=='f')
    {
        if (salle->nb_siege_fausse==0)
        {
            ecrire_texte_jaune("Il n'y a plus de place dans cette catégorie !\n");
            return;
        }
        else
        {
            salle->nb_siege_fausse --;
            salle->nb_siege_reserve ++;
            ecrire_texte_vert("Réservation effectuée !\n");
            printf("Coût de la réservation : %d euros", salle->prix_cat_A);
        }
    }
    else
    {
        bool siege_libre = false;
        do
        {
            int rangee = recuperer_entier(1, salle->nb_rangee, "Entrez le numéro de la rangée");
            rangee--;
            int num_siege = recuperer_entier(1, salle->nb_siege_par_rangee[rangee], "Entrez le numéro du siège dans la rangée");
            num_siege--;
            if (salle->sieges[rangee][num_siege]=='X')
            {
                ecrire_texte_jaune("Cette place est déjà réservée ! Choisissez une autre.\n");
            }
            else if (salle->sieges[rangee][num_siege]=='0')
            {
                // Réservation
                salle->sieges[rangee][num_siege] = 'X';
                salle->nb_siege_reserve = salle->nb_siege_reserve + 1;
                ecrire_texte_vert("Réservation effectuée !\n");
                int montant = 0;
                if (rangee<salle->nb_rangee_A)
                {
                    montant = salle->prix_cat_A;
                }
                else if (rangee>=salle->nb_rangee_B)
                {
                    montant = salle->prix_cat_C;
                }
                else
                {
                    montant = salle->prix_cat_B;
                }
                
                printf("Coût de la réservation : %d euros", montant);
                siege_libre = true;
            }
            else
            {
                ecrire_texte_rouge("Place non trouvée ! Essayez une autre place.\n");
            }
        } while (siege_libre!=true);
    }
    

    // Affichage de la salle pour voir la différence
    afficher_salle(salle);
}

/**
 * Actualise l'état de la salle en comparant l'heure de fin d'évènement et l'heure actuelle
*/
void actualiser_etat_salle(SALLE *salle)
{
    if (salle==NULL)
    {
        return;
    }
    // Heure actuelle
    time_t temps_actuel;
    time(&temps_actuel);
    time_t heure_fin_evenement = mktime(&salle->heure_fin);

    // Comparer les deux time_t
    double difference = difftime(temps_actuel, heure_fin_evenement);
    
    // Modifier l'état en fonction du résultat
    if (difference >= 0) {
        // Heure de fin dépassée
        if (salle->etat==RESERVATIONS_EN_COURS)
        {
            salle->etat = RESERVATIONS_TERMINEES;
        }
    }
}

/**
 * Libère la mémoire occupée par les salles
*/
void liberer_memoire_salles(SALLE*** salles)
{
    if (*salles==NULL)
    {
        return;
    }
    
    int i=0;
    while (salles[i]!=NULL && i<NOMBRE_MAX_SALLE)
    {
        free((*salles)[i]->nom);
        free((*salles)[i]->nom_evenement);
        free((*salles)[i]);
        i++;
    }
    free(*salles);
}