#ifndef ACH__H
#define ACH__H

#include <stdlib.h>

typedef struct hashtable hashtable;

hashtable *hashtable_create(size_t maxNode);

int hashtable_insert(hashtable *p, const char *word);

int hashtable_organize(hashtable *p) ;

size_t hashtable_text_search(hashtable *p, FILE *text);

void hashtable_debug(hashtable *p);

#endif