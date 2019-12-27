## TODO

- le programme ne s'arrête pas quand on clique sur "Quitter" dans le menu
- conditions de victoire
- gestion des modes (avec ou sans variante)
- match nul
- boucle de jeu
- capture d'un pion + capture d'un 2è pion
- ia

## Done

- écriture et lecture des scores
- les mouvements possibles d'un pion
- placer un pion (de la réserve)
- choisir un pion (pour ensuite le déplacer)
- déplacer un pion
- le premier joueur qui joue est tiré au sort

##	UTILISER LE MAKEFILE
```
jeu: main.c // METTRE LES FICHIERS.C
	gcc -Wall main.c -o game -D_REENTRANT -I/usr/include/SDL  -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_image
	// SUR LA DEUXIÈME LIGNE METTRE TOUS LES FICHIERS.C ET .H AVANT LE -o game
```
Pour compiler le jeu écrivez la commande: make
