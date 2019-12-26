jeu: affichage.c affichage.h
	gcc -Wall affichage.c table_score.c -o game -D_REENTRANT -I/usr/include/SDL  -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_ttf -lSDL_image
