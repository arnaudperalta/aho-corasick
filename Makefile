PROGRAMS = genere-texte genere-mots ac-matrice ac-hachage
SRCDIR = src/

# Module genere-texte
GTDIR = $(SRCDIR)genere-texte/
GTOBJ = $(GTDIR)gt.o

# Module genere-mots
GMDIR = $(SRCDIR)genere-mots/
GMOBJ = $(GMDIR)gm.o

# Module aho-corasick matrice
ACDIR = $(SRCDIR)aho-corasick/
ACOBJ = $(ACDIR)aho-corasick.o
ACMOBJ = $(SRCDIR)utils.o $(ACDIR)acm.o
ACHOBJ = $(SRCDIR)utils.o $(ACDIR)ach.o

OBJECTS = $(GTOBJ) $(GMOBJ) $(ACMOBJ) $(ACHOBJ) $(ACOBJ)

CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wpedantic -I$(SRCDIR) -I$(GTDIR) -I$(GMDIR) -I$(ACDIR)

all: $(PROGRAMS)

genere-texte: $(GTOBJ)
	$(CC) $(GTOBJ) $(CFLAGS) -o genere-texte

genere-mots: $(GMOBJ)
	$(CC) $(GMOBJ) $(CFLAGS) -o genere-mots

ac-matrice: $(ACMOBJ)
	$(CC) $(CFLAGS) -c -o $(ACDIR)aho-corasick.o $(ACDIR)aho-corasick.c -D ACM
	$(CC) $(ACMOBJ) $(ACOBJ) $(CFLAGS) -o ac-matrice

ac-hachage: $(ACHOBJ)
	$(CC) $(CFLAGS) -c -o $(ACDIR)aho-corasick.o $(ACDIR)aho-corasick.c
	$(CC) $(ACHOBJ) $(ACOBJ) $(CFLAGS) -o ac-hachage

clean:
	@rm -rf $(OBJECTS) $(PROGRAMS)

acm.o: acm.c acm.h