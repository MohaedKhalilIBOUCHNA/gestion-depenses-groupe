# 💸 Gestion des Dépenses d'un Groupe d'Étudiants

> Devoir – Structures de Données | 1ère Année  
> Réalisé par : **Mohamed Khalil IBOUCHNA**

---

## 📋 Description

Application en **langage C** permettant à un groupe d'étudiants de gérer leurs dépenses communes (repas, transport, loisirs, etc.).

Le programme exploite une **architecture combinant tableau et listes chaînées** avec allocation dynamique de la mémoire, dans une approche de **programmation modulaire**.

---

## 🏗️ Architecture du projet

```
gestion-depenses-groupe/
├── src/
│   ├── depense.h      # Déclaration des structures et prototypes
│   ├── depense.c      # Implémentation des fonctions
│   └── main.c         # Programme principal et menu interactif
├── Makefile           # Compilation automatisée
├── .gitignore
└── README.md
```

---

## 🧱 Structures de données

```
┌─────────────────────────────────────────┐
│  groupe[MAX_ETUDIANTS]  (tableau)        │
│                                          │
│  groupe[0] → Etudiant                   │
│              nom: "Alice"               │
│              premiereDepense ──────────►│
│                                          │
│         ListDepense ──► ListDepense ──► NULL
│         │ montant: 45.0│ montant: 12.5 │
│         │ cat: "Repas" │ cat: "Bus"    │
│         └──────────────┴───────────────┘
└─────────────────────────────────────────┘
```

Chaque étudiant possède une **liste chaînée de dépenses** construite dynamiquement avec `malloc`.

---

## ⚙️ Fonctionnalités

| # | Fonctionnalité                             |
|---|--------------------------------------------|
| 1 | Ajouter un étudiant au groupe              |
| 2 | Ajouter une dépense à un étudiant          |
| 3 | Afficher les dépenses d'un étudiant        |
| 4 | Calculer le total des dépenses d'un étudiant |
| 5 | Afficher le total des dépenses par catégorie |
| 6 | Lister tous les étudiants du groupe        |
| 7 | Quitter (avec libération de la mémoire)    |

---

## 🚀 Compilation et exécution

### Prérequis
- `gcc` (GNU Compiler Collection)
- `make`

### Avec Makefile

```bash
# Compiler
make

# Compiler et lancer directement
make run

# Nettoyer les fichiers compilés
make clean
```

### Sans Makefile

```bash
gcc -Wall -Wextra -std=c11 -o gestion_depenses src/main.c src/depense.c
./gestion_depenses
```

---

## 🖥️ Exemple d'utilisation

```
========================================
   Gestion des Depenses - Groupe
========================================
  1. Ajouter un etudiant
  2. Ajouter une depense
  ...
Votre choix : 1
Nom de l'etudiant : Alice
[OK] Etudiant 'Alice' ajoute avec succes.

Votre choix : 2
Nom de l'etudiant : Alice
Categorie        : Repas
Montant (MAD)    : 45.50
Description      : Dejeuner au restaurant
[OK] Depense de 45.50 MAD ajoutee pour 'Alice'.
```

---

## 🧪 Tests réalisés

- ✅ Ajout de plusieurs étudiants (vérification des doublons)
- ✅ Ajout de plusieurs dépenses par étudiant
- ✅ Calcul correct des totaux individuels
- ✅ Calcul correct des totaux par catégorie
- ✅ Libération propre de la mémoire dynamique
- ✅ Gestion des cas limites (groupe plein, étudiant introuvable, montant invalide)

---

## 📚 Concepts mis en œuvre

- Structures imbriquées (`struct`)
- Listes chaînées (insertion en tête)
- Allocation dynamique (`malloc`, `free`)
- Programmation modulaire (`.h` / `.c`)
- Gestion de la mémoire (sans fuites)
- Menus interactifs en C

---

## 👨‍💻 Auteur

**Mohamed Khalil IBOUCHNA** — 1ère Année, Groupe 5
