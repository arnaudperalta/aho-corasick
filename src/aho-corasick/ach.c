#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../utils.h"
#include "ach.h"

// Il existe une liste par noeud, chaque maillon représentera
// une destination selon la prochaine lettre du texte
typedef struct list {
	int targetNode;  // Cible de la transition
	int value;       // Valeur associé à la transition
	list *next;      // Maillon suivant de la liste
} list;

struct hashtable {
	list **array;   // Tableau contenant les listes pour chaque transition
	int *suppl;     // Tableau des suppléants
	int *end;       // Tableau des états finaux
	int nextNode;   // Indice du prochain état à créé
	size_t maxNode; // Nombre maximal du nombre d'états
};

// Fonction de hachage qui prend en paramètre le
size_t hashfun(size_t elem, int i, int c) {
  	return (size_t) (37 * c + i) % elem;
}

hashtable *hashtable_create(size_t maxNode) {
	// Allocation de maxNode listes
	list **array = malloc(sizeof (list *) * maxNode);
	if (array == NULL)
		return NULL;
	
	hashtable *ptr = malloc(sizeof *ptr);
	if (ptr == NULL)
		return NULL;
	ptr->maxNode = maxNode;
	ptr->nextNode = 1;
	ptr->array = array;

	ptr->suppl = malloc(maxNode * sizeof (int));
	if (ptr->suppl == NULL)
		return NULL;
	for (size_t i = 0; i < maxNode; i++) {
		ptr->suppl[i] = -1;
	}

	ptr->end = calloc(maxNode, sizeof (int));
	if (ptr->end == NULL)
		return NULL;
	
	return ptr;
}

int hashtable_insert(hashtable *h, const char *word) {
	int actualNode = 0;
	for (int i = 0; i < (int) strlen(word); i++) {
		int c = word[i] - ALPHA_BEGIN;
		size_t hash = hashfun(h->maxNode, actualNode, c);
		// Si la fonction de hachage nous renvoie un index sans liste
		if (h->array[hash] == NULL) {
			list *ptr = malloc(sizeof *ptr);
			if (ptr == NULL)
				return -1;
			ptr->targetNode = h->nextNode;
			ptr->value = c;
			ptr->next = NULL;
			h->array[hash] = ptr;
			actualNode = h->nextNode;
			h->nextNode++;
		} else {
			list *ptr = h->array[hash];
			while (ptr->value != c) {
				// La lettre n'est pas dans la liste actuelle,
				// on ajoute un maillon
				if (ptr->next == NULL) {
					list *cell = malloc(sizeof *cell);
					if (cell == NULL)
						return -1;
					cell->targetNode = h->nextNode;
					cell->value = c;
					cell->next = NULL;
					ptr->next = cell;
				}
				ptr = ptr->next;
			}
			actualNode = ptr->targetNode;
		}
	}
	h->end[actualNode] = 1;
	return 0;
}

int hashtable_organize(hashtable *h) {
	queue *q = queue_create(h->maxNode);
	if (q == NULL)
		return -1;
	
	for (int i = 0; i < MAX_ALPHA_SIZE; ++i) {
		size_t hash = hashfun(h->maxNode, 0, i);
		if (h->array[hash]) {

		}
	}
}

// a corriger car faut recup la valeur dans les lists
size_t hashtable_text_search(hashtable *h, FILE *text) {
	size_t wordCount = 0;
	int actualNode = 0;
	int c;
	while ((c = fgetc(text)) != EOF) {
		if (c < ALPHA_BEGIN || c > ALPHA_END)
			continue;
		c = c - ALPHA_BEGIN;
		size_t hash = hashfun(h->maxNode, actualNode, c);
		while (h->array[hash] == -1) {
			actualNode = h->suppl[actualNode];
			hash = hashfun(h->maxNode, actualNode, c);
		}
		actualNode = h->array[hash];
		// On vérifie si une occurence d'un mot a été trouvée.
		if (h->end[actualNode] == 1)
			wordCount++;
	}
	return wordCount;
}

void hashtable_debug(hashtable *p) {

}