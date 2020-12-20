#!/bin/bash
mkdir txt
make
echo "Texts generation."
./genere-texte 5000000 2 > txt/texte2.txt
./genere-texte 5000000 4 > txt/texte4.txt
./genere-texte 5000000 20 > txt/texte20.txt
./genere-texte 5000000 70 > txt/texte70.txt

# Alphabet de 2
echo "Words sets generation."
sleep 1 # La seed est gérer sur la fonction time donc on attend 1 seconde pour ne pas avoir la meme seed que dans la génération du texte
./genere-mots 100 5 15 2 > txt/mots2-1.txt
./genere-mots 100 15 30 2 > txt/mots2-2.txt
./genere-mots 100 30 60 2 > txt/mots2-3.txt

# Alphabet de 4
./genere-mots 100 5 15 4 > txt/mots4-1.txt
./genere-mots 100 15 30 4 > txt/mots4-2.txt
./genere-mots 100 30 60 4 > txt/mots4-3.txt

# Alphabet de 20
./genere-mots 100 5 15 20 > txt/mots20-1.txt
./genere-mots 100 15 30 20 > txt/mots20-2.txt
./genere-mots 100 30 60 20 > txt/mots20-3.txt

# Alphabet de 70
./genere-mots 100 5 15 70 > txt/mots70-1.txt
./genere-mots 100 15 30 70 > txt/mots70-2.txt
./genere-mots 100 30 60 70 > txt/mots70-3.txt

echo "Aho-Corasick algorithm execution."
# Recherche dans texte d'alphabet 2
echo "Words sets 1 (5-15), Alphabet size : 2"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots2-1.txt txt/texte2.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots2-1.txt txt/texte2.txt
echo ""

echo "Words sets 2 (15-30), Alphabet size : 2"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots2-2.txt txt/texte2.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots2-2.txt txt/texte2.txt
echo ""

echo "Words sets 3 (30-60), Alphabet size : 2"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots2-3.txt txt/texte2.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots2-3.txt txt/texte2.txt
echo ""

# Recherche dans texte d'alphabet 4
echo "Words sets 1 (5-15), Alphabet size : 4"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots4-1.txt txt/texte4.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots4-1.txt txt/texte4.txt
echo ""

echo "Words sets 2 (15-30), Alphabet size : 4"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots4-2.txt txt/texte4.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots4-2.txt txt/texte4.txt
echo ""

echo "Words sets 3 (30-60), Alphabet size : 4"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots4-3.txt txt/texte4.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots4-3.txt txt/texte4.txt
echo ""

# Recherche dans texte d'alphabet 20
echo "Words sets 1 (5-15), Alphabet size : 20"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots20-1.txt txt/texte20.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots20-1.txt txt/texte20.txt
echo ""

echo "Words sets 2 (15-30), Alphabet size : 20"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots20-2.txt txt/texte20.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots20-2.txt txt/texte20.txt
echo ""

echo "Words sets 3 (30-60), Alphabet size : 20"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots20-3.txt txt/texte20.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots20-3.txt txt/texte20.txt
echo ""

# Recherche dans texte d'alphabet 70
echo "Words sets 1 (5-15), Alphabet size : 70"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots70-1.txt txt/texte70.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots70-1.txt txt/texte70.txt
echo ""

echo "Words sets 2 (15-30), Alphabet size : 70"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots70-2.txt txt/texte70.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots70-2.txt txt/texte70.txt
echo ""

echo "Words sets 3 (30-60), Alphabet size : 70"
echo ""
echo "Matrix"
time -f "%E" ./ac-matrice txt/mots70-3.txt txt/texte70.txt
echo ""
echo "Hashtable"
time -f "%E" ./ac-hachage txt/mots70-3.txt txt/texte70.txt
echo ""

rm -r txt