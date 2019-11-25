#include <stdio.h>


typedef struct Case {
    int x;
    int y;
} Case;

typedef enum TypeContents {
    VIDE, HOMME, DEMON
} TypeContents;

/*
 * Provoque une erreur car HOMME est déjà défini dans TypeContents
typedef enum TypeJoueur {
    HOMME, DEMON
} TypeJoueur;
*/

typedef struct Player {
    TypeContents JoueurT;
    int piece_cap;
    int piece_reserve;
    int piece_plateau;
} Player;

typedef struct Move {
    Case ancienne_position;
    Case nouvelle_position;
} Move;

/*
typedef struct Img {
    SDL_Surface* img;
    SDL_Rect position;
} Img;

typedef struct Input {
    char key[SDLK_LAST];
    int mousey;
    int mousey;
} Input;
*/

int main()
{

    return 0;
}

