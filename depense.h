#ifndef __DEPENSE__H__
#define __DEPENSE__H__

#define MAX_ETUDIANTS 20
#define MAX_CATEGORIES 20

/* ===== Structures ===== */

typedef struct {
    float montant;
    char  categorie[20];
    char  description[50];
} DepenseInfo;

typedef struct ListDepense {
    DepenseInfo      *dpi;
    struct ListDepense *suivant;
} ListDepense;

typedef struct {
    char        nom[20];
    ListDepense *premiereDepense;
} Etudiant;

/* ===== Prototypes ===== */

/**
 * Initialise toutes les entrées du tableau groupe.
 */
void initialiserGroupe(Etudiant groupe[]);

/**
 * Ajoute un étudiant au groupe.
 * Retourne 1 si succès, 0 si le groupe est plein.
 */
int ajouterEtudiant(Etudiant groupe[], int *nb, char nom[]);

/**
 * Recherche un étudiant par nom.
 * Retourne un pointeur vers l'étudiant, ou NULL s'il n'existe pas.
 */
Etudiant *trouverEtudiant(Etudiant groupe[], int nb, char nom[]);

/**
 * Ajoute une dépense à la liste chaînée d'un étudiant.
 */
void ajouterDepense(Etudiant *e, float montant, char categorie[], char description[]);

/**
 * Affiche toutes les dépenses d'un étudiant.
 */
void afficherDepenses(Etudiant *e);

/**
 * Retourne le total des dépenses d'un étudiant.
 */
float totalEtudiant(Etudiant *e);

/**
 * Affiche le total des dépenses par catégorie pour tout le groupe.
 */
void totalParCategorie(Etudiant groupe[], int nb);

/**
 * Libère toute la mémoire allouée dynamiquement pour le groupe.
 */
void libererGroupe(Etudiant groupe[], int nb);

#endif /* __DEPENSE__H__ */
