#include <stdio.h>
#include <stdlib.h>
#include "depense.h"

/* ------------------------------------------------------------------ */
/*  Utilitaires d'affichage                                             */
/* ------------------------------------------------------------------ */

static void afficherMenu(void) {
    printf("\n========================================\n");
    printf("   Gestion des Depenses - Groupe        \n");
    printf("========================================\n");
    printf("  1. Ajouter un etudiant\n");
    printf("  2. Ajouter une depense\n");
    printf("  3. Afficher les depenses d'un etudiant\n");
    printf("  4. Total des depenses d'un etudiant\n");
    printf("  5. Total des depenses par categorie\n");
    printf("  6. Lister tous les etudiants\n");
    printf("  7. Quitter\n");
    printf("========================================\n");
    printf("Votre choix : ");
}

static void listerEtudiants(Etudiant groupe[], int nb) {
    if (nb == 0) {
        printf("  (aucun etudiant enregistre)\n");
        return;
    }
    printf("\n  Etudiants enregistres (%d / %d) :\n", nb, MAX_ETUDIANTS);
    for (int i = 0; i < nb; i++)
        printf("    %d. %s\n", i + 1, groupe[i].nom);
}

/* ------------------------------------------------------------------ */
/*  Programme principal                                                 */
/* ------------------------------------------------------------------ */

int main(void) {
    Etudiant groupe[MAX_ETUDIANTS];
    int      nb     = 0;
    int      choix  = 0;
    char     nom[20], cat[20], desc[50];
    float    montant;

    initialiserGroupe(groupe);

    do {
        afficherMenu();

        if (scanf("%d", &choix) != 1) {
            /* Vider le buffer en cas de saisie invalide */
            while (getchar() != '\n');
            printf("[ERREUR] Entree invalide.\n");
            continue;
        }

        switch (choix) {

            /* ----- 1. Ajouter un étudiant ----- */
            case 1:
                printf("Nom de l'etudiant : ");
                scanf("%19s", nom);
                ajouterEtudiant(groupe, &nb, nom);
                break;

            /* ----- 2. Ajouter une dépense ----- */
            case 2: {
                printf("Nom de l'etudiant : ");
                scanf("%19s", nom);
                Etudiant *e = trouverEtudiant(groupe, nb, nom);
                if (!e) {
                    printf("[ERREUR] Etudiant '%s' introuvable.\n", nom);
                    break;
                }
                printf("Categorie        : ");
                scanf("%19s", cat);
                printf("Montant (MAD)    : ");
                scanf("%f", &montant);
                printf("Description      : ");
                scanf(" %49[^\n]", desc);
                ajouterDepense(e, montant, cat, desc);
                break;
            }

            /* ----- 3. Afficher les dépenses ----- */
            case 3: {
                printf("Nom de l'etudiant : ");
                scanf("%19s", nom);
                Etudiant *e = trouverEtudiant(groupe, nb, nom);
                if (!e) {
                    printf("[ERREUR] Etudiant '%s' introuvable.\n", nom);
                    break;
                }
                printf("\nDepenses de %s :\n", e->nom);
                afficherDepenses(e);
                break;
            }

            /* ----- 4. Total d'un étudiant ----- */
            case 4: {
                printf("Nom de l'etudiant : ");
                scanf("%19s", nom);
                Etudiant *e = trouverEtudiant(groupe, nb, nom);
                if (!e) {
                    printf("[ERREUR] Etudiant '%s' introuvable.\n", nom);
                    break;
                }
                printf("  Total de %s : %.2f MAD\n", e->nom, totalEtudiant(e));
                break;
            }

            /* ----- 5. Total par catégorie ----- */
            case 5:
                totalParCategorie(groupe, nb);
                break;

            /* ----- 6. Lister les étudiants ----- */
            case 6:
                listerEtudiants(groupe, nb);
                break;

            /* ----- 7. Quitter ----- */
            case 7:
                printf("\nLiberation de la memoire...\n");
                libererGroupe(groupe, nb);
                printf("Au revoir !\n");
                break;

            default:
                printf("[ERREUR] Choix invalide. Entrez un nombre entre 1 et 7.\n");
        }

    } while (choix != 7);

    return 0;
}
