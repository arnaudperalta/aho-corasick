PROGRAMS = genere-texte genere-mots ac-matrice ac-hachage


# Module genere-texte
GTDIR = src/genere-texte/
GTOBJ = $(GTDIR)gt.o

# Module genere-mots
GMDIR = src/genere-mots/
GMOBJ = $(GMDIR)gm.o

# Module aho-corasick matrice
ACDIR = src/aho-corasick/
ACOBJ = $(ACDIR)aho-corasick.o
ACMOBJ = $(ACDIR)acm.o
ACHOBJ = $(ACDIR)ach.o

OBJECTS = $(GTOBJ) $(GMOBJ) $(ACMOBJ) $(ACHOBJ) $(ACOBJ)

CC = gcc
CFLAGS = -std=c11 -Wall -Wconversion -Werror -Wextra -Wpedantic -Isrc/ -I$(GTDIR) -I$(GMDIR) -I$(ACDIR)

all: $(PROGRAMS)

genere-texte: $(GTOBJ)
	$(CC) $(GTOBJ) $(CFLAGS) -o genere-texte

genere-mots: $(GMOBJ)
	$(CC) $(GMOBJ) $(CFLAGS) -o genere-mots

ac-matrice: $(ACMOBJ)
	$(CC) $(CFLAGS) -c -o $(ACDIR)aho-corasick.o $(ACDIR)aho-corasick.c
	$(CC) $(ACMOBJ) $(ACOBJ) $(CFLAGS) -o ac-matrice

ac-hachage: $(ACHOBJ)
	$(CC) $(CFLAGS) -c -o $(ACDIR)aho-corasick.o $(ACDIR)aho-corasick.c -D ACM 0
	$(CC) $(ACHOBJ) $(ACOBJ) $(CFLAGS) -o ac-hachage

clean:
	@rm -rf $(OBJECTS) $(PROGRAMS)

acm.o: acm.c acm.h