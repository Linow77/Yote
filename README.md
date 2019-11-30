## TODO

- conditions de victoire
- gestion des modes (avec ou sans variante)
- match nul
- boucle de jeu
- capture d'un pion + capture d'un 2è pion
- ia

##	UTILISER LE MAKEFILE
```
jeu: main.c // METTRE LES FICHIERS.C
	gcc -Wall main.c -o game -D_REENTRANT -I/usr/include/SDL  -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_image
	// SUR LA DEUXIÈME LIGNE METTRE TOUS LES FICHIERS.C ET .H AVANT LE -o game
```
Pour compiler le jeu écriver la commande: make
