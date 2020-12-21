#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../utils.h"

#define ARG_COUNT      3

// Ce programme génère un texte aléatoire selon deux paramètres :
//	- La taille du texte
//	- La taille de l'alphabet

int main(int argc, char **argv) {
	if (argc != ARG_COUNT) {
		fprintf(stderr, "Invalid arguments.");
		return EXIT_FAILURE;
	}

	int alphaSize = atoi(argv[2]);
	int textSize = atoi(argv[1]);

	if (textSize <= 0) {
		fprintf(stderr, "Invalid text size.");
		return EXIT_FAILURE;
	}
	if (alphaSize <= 0 || alphaSize > MAX_ALPHA_SIZE) {
		fprintf(stderr, "Invalid alphabet size.");
		return EXIT_FAILURE;
	}

	// Pour ne pas avoir la même seed à chaque exécution.
	srand((unsigned int) time(NULL));

	for (int i = 0; i < textSize; ++i) {
		int r = rand() % alphaSize;
		putchar('0' + r);
	}

	return EXIT_SUCCESS;
}
