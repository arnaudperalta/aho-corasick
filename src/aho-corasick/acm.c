#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "../utils.h"
#include "acm.h"

#define ARG_COUNT      3

// On défini la matrice de transitions comme un tableau de pointeur.
// Chacun de ces tableau représente un état et chaque colonne une lettre.
struct m_tran {
	int **matrix; // matrice de transition
	int *suppl;   // tableau des suppléants
	int *end;    // tableau des états finaux
	int nextNode; // Indice du prochain état a créé
	size_t maxNode;
};

// Strcuture de file utilisé pour le calcul des suppléants
typedef struct queue {
	int *array;
	int size;
	int count;
	int front;
	int back;
} queue;

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

m_tran *matrix_create(size_t maxNode) {
	m_tran *p = malloc(sizeof *p);
	if (p == NULL)
		return NULL;
	p->nextNode = 1;
	p->maxNode = maxNode;
	p->matrix = malloc(sizeof (int *) * maxNode);
	if (p->matrix == NULL)
		return NULL;
	// On alloue l'état 0 puis on l'insère dans la matrice de transitions
	// On laisse 0 car toutes les lettres boucle sur l'état 0 de base
	int *node = calloc(MAX_ALPHA_SIZE, sizeof (int));
	if (node == NULL)
		return NULL;
	p->matrix[0] = node;
	for (size_t i = 1; i < maxNode; i++) {
		int *node = malloc(sizeof (int) * MAX_ALPHA_SIZE);
		if (node == NULL)
			return NULL;
		
		for (int j = 0; j < MAX_ALPHA_SIZE; j++) {
			node[j] = -1;
		}
		p->matrix[i] = node;
	}

	p->suppl = malloc(maxNode * sizeof (int));
	if (p->suppl == NULL)
		return NULL;
	for (size_t i = 0; i < maxNode; i++) {
		p->suppl[i] = -1;
	}

	p->end = calloc(maxNode, sizeof (int));
	if (p->end == NULL)
		return NULL;

	return p;
}

int matrix_insert(m_tran *p, const char *word) {
	int actualNode = 0;
	for (size_t i = 0; i < strlen(word); ++i) {
		char c = word[i];
		int rank = c - ALPHA_BEGIN;
		// La liaison n'existe pas, on écrit dans la matrice
		if (p->matrix[actualNode][rank] == -1 
				|| (actualNode == 0 && p->matrix[actualNode][rank] == 0)) {
			p->matrix[actualNode][rank] = p->nextNode;
			actualNode = p->nextNode;
			p->nextNode++;
		// La liaison existe déja, on poursuit
		} else {
			actualNode = p->matrix[actualNode][rank];
		}
	}
	p->end[actualNode] = 1;
	return 0;
}

int matrix_organize(m_tran *p) {
	queue *q = queue_create(p->maxNode);
	if (q == NULL)
		return -1;
	// Cas différent pour la première ligne de la matrice
	// car elle possèdes des 0 pour toutes les lettres
	for (int i = 0; i < MAX_ALPHA_SIZE; ++i) {
		if (p->matrix[0][i] != -1 && p->matrix[0][i] != 0) {
			p->suppl[p->matrix[0][i]] = 0;
			queue_push(q, p->matrix[0][i]);
		}
	}
	while (queue_count(q)) {
		int node = queue_pop(q);
		for (int i = 0; i < MAX_ALPHA_SIZE; ++i) {
			if (p->matrix[node][i] != -1) {
				int suppl = p->suppl[node];
				while (p->matrix[suppl][i] == -1) {
					suppl = p->suppl[suppl];
				}
				suppl = p->matrix[suppl][i];
				p->suppl[p->matrix[node][i]] = suppl;
				queue_push(q, p->matrix[node][i]);
			}
		}
	}
	return 0;
}

size_t matrix_text_search(m_tran *p, FILE *text) {
	size_t wordCount = 0;
	int actualNode = 0;
	int c;
	while ((c = fgetc(text)) != EOF) {
		if (c < ALPHA_BEGIN || c > ALPHA_END)
			continue;
		int rank = c - ALPHA_BEGIN;
		// Tant que le noeud actuel ne possède pas de suite compatible
		// On remonte par les suffixes propres
		while (p->matrix[actualNode][rank] == -1) {
			actualNode = p->suppl[actualNode];
		}
		actualNode = p->matrix[actualNode][rank];
		// On vérifie si une occurence n'a pas été trouvée
		if (p->end[actualNode] == 1) {
			wordCount++;
		}
	}
	return wordCount;
}

void matrix_debug(m_tran *p) {
	for (size_t i = 0; i < p->maxNode; ++i) {
		for (size_t j = 0; j < MAX_ALPHA_SIZE; ++j) {
			printf("%d ", p->matrix[i][j]);
		}
		printf("\n");
	}
}