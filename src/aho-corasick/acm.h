#ifndef ACM__H
#define ACM__H

#include <stdlib.h>

typedef struct m_tran m_tran;

m_tran *matrix_create(size_t maxNode);

int matrix_insert(m_tran *p, const char *word);

int matrix_organize(m_tran *p) ;

size_t matrix_text_search(m_tran *p, FILE *text);

void matrix_debug(m_tran *p);

#endif