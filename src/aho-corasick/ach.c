#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../utils.h"
#include "ach.h"

// Il existe une liste par noeud, chaque maillon représentera
// une destination selon la prochaine lettre du texte
typedef struct list list;

struct list {
	int startNode;   // Départ de la transition
	int targetNode;  // Cible de la transition
	int value;       // Valeur associé à la transition
	list *next;      // Maillon suivant de la liste
};

struct hashtable {
	list **array;   // Tableau contenant les listes pour chaque transition
	int *suppl;     // Tableau des suppléants
	int *end;       // Tableau des états finaux
	int nextNode;   // Indice du prochain état à créé
	size_t maxNode; // Nombre maximal du nombre d'états
};

// Insertion en fin de liste d'un élément
list *list_create(int startNode, int targetNode, int value) {
	list *list = malloc(sizeof *list);
	if (list == NULL)
		return NULL;
	list->startNode = startNode;
	list->targetNode = targetNode;
	list->value = value;
	list->next = NULL;

	return list;
}

int list_insert(list *ptr, int startNode, int targetNode, int value) {
	if (ptr == NULL)
		return -1;

	while (ptr->next != NULL)
		ptr = ptr->next;
	list *cell = malloc(sizeof *cell);
	if (cell == NULL)
		return -1;
	cell->startNode = startNode;
	cell->targetNode = targetNode;
	cell->value = value;
	cell->next = NULL;

	ptr->next = cell;
	return 0;
}

int list_search_target(list *ptr, int startNode, int c) {
	while (ptr != NULL) {
		if (c == ptr->value && startNode == ptr->startNode)
			return ptr->targetNode;
		ptr = ptr->next;
	}
	return -1;
}

// Fonction de hachage qui prend en paramètre l'état
// actuel et la lettre voulu
size_t hashfun(size_t elem, int i, int c) {
  	return (size_t) (37 * c + i) % elem;
}

hashtable *hashtable_create(size_t maxNode) {	
	hashtable *ptr = malloc(sizeof (hashtable));
	if (ptr == NULL)
		return NULL;
	ptr->maxNode = maxNode;
	ptr->nextNode = 1;
	ptr->array = calloc(maxNode, sizeof (list *));
	if (ptr->array == NULL)
		return NULL;

	ptr->suppl = malloc(maxNode * sizeof (int));
	if (ptr->suppl == NULL)
		return NULL;
	for (size_t i = 0; i < maxNode; i++) {
		ptr->suppl[i] = -1;
	}

	ptr->end = calloc(maxNode, sizeof (int));
	if (ptr->end == NULL)
		return NULL;
	
	// On créé les liaisons de bases (l'état 0 qui boucle sur lui même)
	for (int i = 0; i < MAX_ALPHA_SIZE; ++i) {
		size_t hash = hashfun(ptr->maxNode, 0, i);
		if (ptr->array[hash] == NULL)
			ptr->array[hash] = list_create(0, 0, i);
		else
			list_insert(ptr->array[hash], 0, 0, i);
	}

	return ptr;
}

int hashtable_insert(hashtable *h, const char *word) {
	int actualNode = 0;
	for (int i = 0; i < (int) strlen(word); i++) {
		int c = word[i] - ALPHA_BEGIN;
		size_t hash = hashfun(h->maxNode, actualNode, c);
		// Si la fonction de hachage nous renvoie un index sans liste
		if (h->array[hash] == NULL) {
			h->array[hash] = list_create(actualNode, h->nextNode, c);
			actualNode = h->nextNode;
			h->nextNode++;
		} else {
			list *ptr = h->array[hash];
			while (ptr->value != c) {
				// La lettre n'est pas dans la liste actuelle,
				// on ajoute un maillon
				if (ptr->next == NULL) {
					list_insert(ptr, actualNode, h->nextNode, c);
				}
				ptr = ptr->next;
			}
			// On a trouvé la cellule avec la bonne lettre, mais on vérifie
			// si ce n'est pas une cellule qui bouclé sur l'état initial.
			if (ptr->startNode == 0 && ptr->targetNode == 0) {
				ptr->targetNode = h->nextNode;
			}
			actualNode = ptr->targetNode;
			h->nextNode++;
		}
	}
	h->end[actualNode] = 1;
	return 0;
}

int hashtable_get(hashtable *h, int startNode, int value) {
	return list_search_target(h->array[hashfun(h->maxNode, startNode, value)], startNode, value);
}

int hashtable_organize(hashtable *h) {
	queue *q = queue_create(h->maxNode);
	if (q == NULL)
		return -1;
	
	for (int i = 0; i < MAX_ALPHA_SIZE; ++i) {
		if (hashtable_get(h, 0, i) != -1 && hashtable_get(h, 0, i) != 0) {
			h->suppl[hashtable_get(h, 0, i)] = 0;
			queue_push(q, hashtable_get(h, 0, i));
		}
	}
	while (queue_count(q)) {
		int node = queue_pop(q);
		for (int i = 0; i < MAX_ALPHA_SIZE; ++i) {
			if (hashtable_get(h, node, i) != -1) {
				int suppl = h->suppl[node];
				while (hashtable_get(h, suppl, i) == -1) {
					suppl = h->suppl[suppl]; // PROBLEME : on a -1 dans suppl, donc un mauvais read
				}
				suppl = hashtable_get(h, suppl, i);
				h->suppl[hashtable_get(h, node, i)] = suppl;
				queue_push(q, hashtable_get(h, node, i));
			}
		}
	}
	return 0;
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
		while (hashtable_get(h, actualNode, c) == -1) {
			actualNode = h->suppl[actualNode];
		}
		actualNode = hashtable_get(h, actualNode, c);
		// On vérifie si une occurence d'un mot a été trouvée.
		if (h->end[actualNode] == 1)
			wordCount++;
	}
	return wordCount;
}

void hashtable_debug(hashtable *h) {
	printf("maxNode : %zu\n", h->maxNode);
	printf("tableau end :\n");
	for (size_t i = 0; i < h->maxNode; i++) {
		printf("%d ", h->end[i]);
	}
	printf("tableau suppl :\n");
	for (size_t i = 0; i < h->maxNode; i++) {
		printf("%d ", h->suppl[i]);
	}
	printf("\n");
	for (size_t i = 0; i < h->maxNode; ++i) {
		list *ptr = h->array[i];
		while (ptr != NULL) {
			if (ptr->startNode == 0)
				printf("start : %d target : %d value : %d         \n", ptr->startNode, ptr->targetNode, ptr->value);
			ptr = ptr->next;
		}
	}
}
