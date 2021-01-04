#ifndef ACH__H
#define ACH__H

#include <stdlib.h>

// Définition de la structure de la table de hachage modélisant
// le dictionnaire de l'algorithme Aho-Corasick
typedef struct hashtable hashtable;

// Fonction de création de la structure de table de hachage
hashtable *hashtable_create(size_t maxNode);

// Fonction d'insetion de mot dans la table de hachage.
int hashtable_insert(hashtable *p, const char *word);

// Procédure de construction de la fonction suppléante.
int hashtable_organize(hashtable *p) ;

// Fonction de recherche dans un texte via le dictionnaire construit
// dans la table de hachage
size_t hashtable_text_search(hashtable *p, FILE *text);

// Fonction de debugage pour visaliser la table de hachage.
void hashtable_debug(hashtable *p);

#endif
