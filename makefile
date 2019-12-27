game: table_score.o affichage.o main.c
	gcc -Wall affichage.o table_score.o main.c -o game -D_REENTRANT -I/usr/include/SDL  -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_ttf -lSDL_image

table_score.o: table_score.c
	echo table_score.c
	gcc -o table_score.o -c table_score.c -W -Wall


affichage.o: affichage.c
	echo affichage.c
	gcc -o affichage.o -c affichage.c -W -Wall -D_REENTRANT -I/usr/include/SDL  -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_ttf -lSDL_image

