## TODO

- conditions de victoire
- match nul
- boucle de jeu
- capture d'un pion
- vérifier que le joueur ne fasse le même déplacement qu'au tour précédent

##	UTILISER LE MAKEFILE
```
jeu: main.c // METTRE LES FICHIERS.C
	gcc -Wall main.c -o game -D_REENTRANT -I/usr/include/SDL  -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_image
	// SUR LA DEUXIÈME LIGNE METTRE TOUS LES FICHIERS.C ET .H AVANT LE -o game
```
Pour compiler le jeu écriver la commande: make
