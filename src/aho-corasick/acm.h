#ifndef ACM__H
#define ACM__H

#include <stdlib.h>

// Définition de la structure de matrice de transition modélisant
// le dictionnaire de l'algorithme Aho-Corasick
typedef struct m_tran m_tran;

// Fonction de création de la structure de matrice de transition
m_tran *matrix_create(size_t maxNode);

// Fonction d'insertion d'un mot dans la matrice de transition
int matrix_insert(m_tran *p, const char *word);

// Procédure de construction de la fonction suppléante
int matrix_organize(m_tran *p) ;

// Fonction de recherche dans un texte via le dictionnaire construit
// dans la matrice de transition
size_t matrix_text_search(m_tran *p, FILE *text);

// Fonction de debugage pour visualiser la matrice de transition.
void matrix_debug(m_tran *p);

#endif