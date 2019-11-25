jeu: main.c
	gcc -Wall main.c -o game -D_REENTRANT -I/usr/include/SDL  -L/usr/lib/x86_64-linux-gnu -lSDL -lSDL_image
