#ifndef ACM__H
#define ACM__H

#include <stdlib.h>

typedef struct m_tran m_tran;

m_tran *matrix_create(void);

int matrix_insert(m_tran *p, const char *word);

// Pour chaque état on ajoute une liaison au préfixe le plus grand.
void matrix_organize(m_tran *p);

size_t matrix_text_search(m_tran *p, FILE *text);

#endif