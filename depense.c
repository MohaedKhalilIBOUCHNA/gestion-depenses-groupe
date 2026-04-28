#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "depense.h"

/* ------------------------------------------------------------------ */
/*  Initialisation                                                      */
/* ------------------------------------------------------------------ */

void initialiserGroupe(Etudiant groupe[]) {
    for (int i = 0; i < MAX_ETUDIANTS; i++) {
        groupe[i].nom[0]          = '\0';
        groupe[i].premiereDepense = NULL;
    }
}

/* ------------------------------------------------------------------ */
/*  Gestion des étudiants                                               */
/* ------------------------------------------------------------------ */

int ajouterEtudiant(Etudiant groupe[], int *nb, char nom[]) {
    if (*nb >= MAX_ETUDIANTS) {
        printf("[ERREUR] Le groupe est plein (%d etudiants max).\n", MAX_ETUDIANTS);
        return 0;
    }
    /* Vérifier doublon */
    if (trouverEtudiant(groupe, *nb, nom) != NULL) {
        printf("[ERREUR] L'etudiant '%s' existe deja.\n", nom);
        return 0;
    }
    strcpy(groupe[*nb].nom, nom);
    groupe[*nb].premiereDepense = NULL;
    (*nb)++;
    printf("[OK] Etudiant '%s' ajoute avec succes.\n", nom);
    return 1;
}

Etudiant *trouverEtudiant(Etudiant groupe[], int nb, char nom[]) {
    for (int i = 0; i < nb; i++)
        if (strcmp(groupe[i].nom, nom) == 0)
            return &groupe[i];
    return NULL;
}

/* ------------------------------------------------------------------ */
/*  Gestion des dépenses                                                */
/* ------------------------------------------------------------------ */

void ajouterDepense(Etudiant *e, float montant, char categorie[], char description[]) {
    if (montant <= 0) {
        printf("[ERREUR] Le montant doit etre positif.\n");
        return;
    }

    ListDepense *nv = malloc(sizeof(ListDepense));
    if (!nv) { perror("malloc ListDepense"); return; }

    nv->dpi = malloc(sizeof(DepenseInfo));
    if (!nv->dpi) { perror("malloc DepenseInfo"); free(nv); return; }

    nv->dpi->montant = montant;
    strncpy(nv->dpi->categorie,   categorie,   sizeof(nv->dpi->categorie)   - 1);
    strncpy(nv->dpi->description, description, sizeof(nv->dpi->description) - 1);
    nv->dpi->categorie[sizeof(nv->dpi->categorie)   - 1] = '\0';
    nv->dpi->description[sizeof(nv->dpi->description) - 1] = '\0';

    /* Insertion en tête */
    nv->suivant        = e->premiereDepense;
    e->premiereDepense = nv;

    printf("[OK] Depense de %.2f MAD ajoutee pour '%s'.\n", montant, e->nom);
}

void afficherDepenses(Etudiant *e) {
    if (e->premiereDepense == NULL) {
        printf("  (aucune depense enregistree)\n");
        return;
    }
    ListDepense *p = e->premiereDepense;
    int i = 1;
    printf("\n  %-4s %-15s %-10s %s\n", "N°", "Categorie", "Montant", "Description");
    printf("  %-4s %-15s %-10s %s\n",   "---", "---------", "-------", "-----------");
    while (p) {
        printf("  %-4d %-15s %-10.2f %s\n",
               i++, p->dpi->categorie, p->dpi->montant, p->dpi->description);
        p = p->suivant;
    }
}

float totalEtudiant(Etudiant *e) {
    float total = 0.0f;
    ListDepense *p = e->premiereDepense;
    while (p) {
        total += p->dpi->montant;
        p = p->suivant;
    }
    return total;
}

void totalParCategorie(Etudiant groupe[], int nb) {
    char  categories[MAX_CATEGORIES][20];
    float totaux[MAX_CATEGORIES];
    int   cpt = 0;

    /* Initialiser le tableau des totaux */
    for (int i = 0; i < MAX_CATEGORIES; i++) totaux[i] = 0.0f;

    for (int i = 0; i < nb; i++) {
        ListDepense *p = groupe[i].premiereDepense;
        while (p) {
            int trouve = -1;
            for (int j = 0; j < cpt; j++)
                if (strcmp(categories[j], p->dpi->categorie) == 0)
                    trouve = j;

            if (trouve == -1) {
                strncpy(categories[cpt], p->dpi->categorie, 19);
                categories[cpt][19] = '\0';
                totaux[cpt++]       = p->dpi->montant;
            } else {
                totaux[trouve] += p->dpi->montant;
            }
            p = p->suivant;
        }
    }

    if (cpt == 0) {
        printf("  (aucune depense enregistree dans le groupe)\n");
        return;
    }

    printf("\n  %-20s %s\n", "Categorie", "Total (MAD)");
    printf("  %-20s %s\n",   "---------", "-----------");
    for (int i = 0; i < cpt; i++)
        printf("  %-20s %.2f\n", categories[i], totaux[i]);
}

/* ------------------------------------------------------------------ */
/*  Libération de la mémoire                                            */
/* ------------------------------------------------------------------ */

void libererGroupe(Etudiant groupe[], int nb) {
    for (int i = 0; i < nb; i++) {
        ListDepense *p = groupe[i].premiereDepense;
        while (p) {
            ListDepense *tmp = p->suivant;
            free(p->dpi);
            free(p);
            p = tmp;
        }
        groupe[i].premiereDepense = NULL;
    }
}
