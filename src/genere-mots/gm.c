#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include "../utils.h"

#define ARG_COUNT 5

// Ce programme génère des mots aléatoire selon quatre paramètres :
//	- Le nombre de mots à générer.
//	- La longueur minimal d'un mot généré.
//	- La longueur maximal d'un mot généré.
//	- La taille de l'alphabet

int main(int argc, char **argv) {
	if (argc != ARG_COUNT) {
		fprintf(stderr, "Invalid arguments.");
		return EXIT_FAILURE;
	}

	int wordCount = atoi(argv[1]);
	int minLength = atoi(argv[2]);
	int maxLength = atoi(argv[3]);
	int alphaSize = atoi(argv[4]);

	if (wordCount <= 0) {
		fprintf(stderr, "Invalid alphabet size.");
		return EXIT_FAILURE;
	}
	if (minLength <= 0) {
		fprintf(stderr, "Invalid minimum word length.");
		return EXIT_FAILURE;
	}
	if (maxLength <= 0) {
		fprintf(stderr, "Invalid maximum word length.");
		return EXIT_FAILURE;
	}
	if (alphaSize <= 0 || alphaSize > MAX_ALPHA_SIZE) {
		fprintf(stderr, "Invalid alphabet size.");
		return EXIT_FAILURE;
	}

	// Pour ne pas avoir la même seed à chaque exécution.
	srand((unsigned int) time(NULL));

	for (int i = 0; i < wordCount; ++i) {
		int wordLength = (rand() % (maxLength - minLength)) + minLength;
		for (int j = 0; j < wordLength; ++j) {
			int r = rand() % alphaSize;
			putchar('0' + r);
		}
		putchar('\n');
	}
}
