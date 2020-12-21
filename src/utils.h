#ifndef UTILS__H
#define UTILS__H

// L'alphabet sera défini de '0' à 'z' sur la table ASCII
#define MAX_ALPHA_SIZE 75
#define ALPHA_BEGIN    '0'
#define ALPHA_END      'z'

// Définition de la structure de file utilisé pour la construction
// de la fonction suppléante.
typedef struct queue queue;

// Fonction de création de la structure de file
queue *queue_create(size_t maxNode);

// Fonction d'insertion d'entier dans la file
void queue_push(queue *ptr, int value);

// Fonction de récuperation d'entier dans la file
int queue_pop(queue *ptr);

// Fonction de récuperation de la taille de la file
int queue_count(queue *ptr);

#endif
