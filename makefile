game: table_score.o affichage.o main.c
	gcc -Wall affichage.o table_score.o main.c -o game -D_REENTRANT -I/usr/include/SDL  -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_ttf -lSDL_image -g

table_score.o: table_score.c
	gcc -o table_score.o -c table_score.c -Wall


affichage.o: affichage.c
	gcc -o affichage.o -c affichage.c -Wall -D_REENTRANT -I/usr/include/SDL  -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_ttf -lSDL_image

