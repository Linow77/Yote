## Compiler et exécuter le jeu

```
make
```
```
./game
```


## TODO

- enlever les fonctions inutilisées
- fuites mémoires
- fichier controleur.c .h
- gestion des scores dans le main
- match nul
- simplifier le code
- partie contrôleur

## Done

- conditions de victoire
- boucle de jeu
- capture d'un pion + capture d'un 2è pion
- ia
- écriture et lecture des scores
- gestion des modes (avec ou sans variante)
- les mouvements possibles d'un pion
- placer un pion (de la réserve)
- choisir un pion (pour ensuite le déplacer)
- déplacer un pion
- le premier joueur qui joue est tiré au sort

## UTILISER LE MAKEFILE
```
jeu: main.c // METTRE LES FICHIERS.C
	gcc -Wall main.c -o game -D_REENTRANT -I/usr/include/SDL  -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_image
	// SUR LA DEUXIÈME LIGNE METTRE TOUS LES FICHIERS.C ET .H AVANT LE -o game
```
