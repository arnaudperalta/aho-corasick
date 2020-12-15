#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "../utils.h"
#include "acm.h"

#define ARG_COUNT      3

// On défini la matrice de transitions comme un tableau de pointeur.
// Chacun de ces tableau représente un état et chaque colonne une lettre.
struct m_tran {
	int **matrix; // matrice de transition
	int *end;     // tableau des états finaux
	size_t endCount; // nombre d'états finaux
	int nextNode; // Indice du prochain état a créé
};

m_tran *matrix_create(void) {
	m_tran *p = malloc(sizeof *p);
	if (p == NULL)
		return NULL;
	p->nextNode = 1;
	p->matrix = malloc(sizeof (int *));
	if (p->matrix == NULL)
		return NULL;
	// On alloue l'état 0 puis on l'insère dans la matrice de transitions
	int *node = calloc(MAX_ALPHA_SIZE, sizeof (int));
	if (node == NULL)
		return NULL;
	p->matrix[0] = node;
	p->endCount = 0;
	return p;
}

int matrix_insert(m_tran *p, const char *word) {
	int actualNode = 0;
	for (size_t i = 0; i < strlen(word); ++i) {
		char c = word[i];
		int rank = c - ALPHA_BEGIN;
		if (!p->matrix[actualNode][rank]) {
			// Nouvelle branche
			p->matrix = realloc(p->matrix, sizeof (int) * p->nextNode);
			p->matrix[p->nextNode] = malloc(MAX_ALPHA_SIZE * sizeof (int));
			// On initialise cette ligne avec des -1
			memset(p->matrix[p->nextNode], -1, MAX_ALPHA_SIZE * sizeof (int));
			actualNode = p->nextNode;
			p->nextNode++;
		} else {
			actualNode = p->matrix[actualNode][rank];
		}
		p->matrix[actualNode][rank] = p->nextNode;
	}
	p->endCount++;
	p->end = realloc(p->end, sizeof (int) * p->endCount);
	if (p->end == NULL)
		return -1;
	p->end[p->endCount - 1] = actualNode;
	return 0;
}

void matrix_organize(m_tran *p) {
	for (int i = 0; i < p->nextNode; ++i) {
		
	}
}

size_t matrix_text_search(m_tran *p, FILE *text) {

}