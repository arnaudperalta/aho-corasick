#ifndef UTILS__H
#define UTILS__H

// L'alphabet sera défini de '0' à 'z' sur la table ASCII
#define MAX_ALPHA_SIZE 75
#define ALPHA_BEGIN    '0'
#define ALPHA_END      'z'

typedef struct queue queue;

queue *queue_create(size_t maxNode);

void queue_push(queue *ptr, int value);

int queue_pop(queue *ptr);

int queue_count(queue *ptr);

#endif