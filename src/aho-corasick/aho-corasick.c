#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "../utils.h"
#include "acm.h"
#include "ach.h"

#define ARG_COUNT 3

// Ce programme implémente l'algorithme d'aho-corasick à l'aide d'une matrice
// de transitions ou d'une table de hachage  On y donne deux arguments :
//	- Un fichier contenant les mots à rechercher.
//	- Un fichier contenant le texte sur lequel les recherches seront réalisées.
int main(int argc, char **argv) {
	if (argc != ARG_COUNT) {
		fprintf(stderr, "Invalid arguments.");
		return EXIT_FAILURE;
	}

	FILE *words_file = fopen(argv[1], "r");
	FILE *text_file = fopen(argv[2], "r");

	if (words_file == NULL || text_file == NULL) {
		fprintf(stderr, "Invalid files.");
		return EXIT_FAILURE;
	}

	// On calcule la longueur maximal d'un mot et le nombre d'état maximum possible
	int c;
	size_t maxNode = 0;
	size_t maxLength = 0;
	size_t length = 0;
	while ((c = fgetc(words_file)) != EOF) {
		if (c == '\n') {
			if (length > maxLength)
				maxLength = length;
			length = 0;
		}
		length++;
		maxNode++;
	}
	maxLength++; // Caractère de fin de chaîne.
	maxNode++;   // On ajoute l'état initial

	#ifdef ACM
		// Création de la structure de la matrice de transitions
		m_tran *matrix = matrix_create(maxNode);
		if (matrix == NULL)
			return EXIT_FAILURE;
	#else
		if (maxNode < MAX_ALPHA_SIZE + 1)
			maxNode = MAX_ALPHA_SIZE + 1;
		hashtable *h_table = hashtable_create(maxNode);
		if (h_table == NULL)
			return EXIT_FAILURE;
	#endif

	// On extrait les mots du fichier puis on les insère dans la matrice
	fseek(words_file, SEEK_SET, 0);
	char word[maxLength];
	while (fgets(word, (int) maxLength, words_file) != NULL) {
		if (word[0] == '\n')
			continue;
		// On retire le caractère de retour à la ligne s'il existe
		if (word[strlen(word) - 1] == '\n')
			word[strlen(word) - 1] = '\0';
		#ifdef ACM
			if (matrix_insert(matrix, word))
				return EXIT_FAILURE;
		#else
			if (hashtable_insert(h_table, word))
				return EXIT_FAILURE;
		#endif
	}
	// Construction des suppléants
	fseek(words_file, SEEK_SET, 0);
	size_t res;
	#ifdef ACM
		matrix_organize(matrix);
		res = matrix_text_search(matrix, text_file);
	#else
		hashtable_organize(h_table);
		res = hashtable_text_search(h_table, text_file);
	#endif

	printf("%zu\n", res);
	return EXIT_SUCCESS;
}
