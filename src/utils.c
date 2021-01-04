#include <stdlib.h>
#include "utils.h"

// Strcuture de file utilisé pour le calcul des suppléants
struct queue {
	int *array;
	int size;
	int count;
	int front;
	int back;
};

queue *queue_create(size_t maxNode) {
	queue *ptr = malloc(sizeof *ptr);
	if (ptr == NULL)
		return NULL;
	ptr->array = malloc(sizeof (int) * maxNode);
	if (ptr->array == NULL)
		return NULL;
	ptr->size = (int) maxNode;
	ptr->count = 0;
	ptr->front = 0;
	ptr->back = -1;
	return ptr;
}

void queue_push(queue *ptr, int value) {
	if (ptr->back == ptr->size - 1)
		ptr->back = -1;
	ptr->array[++ptr->back] = value;
	ptr->count++;
}

int queue_pop(queue *ptr) {
	int res = ptr->array[ptr->front++];
	if (ptr->front == ptr->size)
		ptr->front = 0;
	ptr->count--;
	return res;
}

int queue_count(queue *ptr) {
	return ptr->count;
}
