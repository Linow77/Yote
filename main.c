#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

void TireAuSortJoueur(TypeContents *joueur);
void InitPlateau();
int VerifCaseVide(Case c);
int VerifPionsSurPlateau(TypeContents joueur);
int VerifDeplacementOrthogonal(Case c1, Case c2);
void AffichePlateauCLI();

TypeContents plateau[5][6];

int main()
{
    // Pour pouvoir tirer au sort un joueur (donc générer un nombre aléatoire)
    // Il faut initialiser la graine (une seule fois)
    srand(time(NULL));
    Player joueurs[2];
    InitPlateau();
    AffichePlateauCLI();



    return 0;
}


// Temporaire
void AffichePlateauCLI() {
    int i, j, z;

    for (z = 0; z != 5; z++) {
        printf("--");
    }
    printf("-\n");
    for (i = 0; i != 6; i++) {
        for (j = 0; j != 5; j++) {
            switch (plateau[i][j]) {
                case VIDE:
                    printf("| ");
                    break;
                case HOMME:
                    printf("|H");
                    break;
                case DEMON:
                    printf("|D");
                    break;
                default:
                    printf("|x");
            }
        }
        printf("|\n");
        for (z = 0; z != 5; z++) {
            printf("--");
        }
        printf("-\n");
    }
}

/* Initialise les cases du plateau à VIDE */
void InitPlateau() {
    int i, j;

    for (i = 0; i != 6; i++) {
        for (j = 0; j != 5; j++) {
            plateau[i][j] = VIDE;
        }
    }
}

int VerifCaseVide(Case c) {
    return plateau[c.y][c.x] == VIDE;
}

/* Vérifie que la joueur se déplace bien de haut en bas ou de bas
 * à gauche */
int VerifDeplacementOrthogonal(Case c1, Case c2) {
    return (c1.x == c2.x && c1.y != c2.y) ||
           (c1.x != c2.x && c1.y == c2.y);
}

/* On vérifie que le joueur a des pions sur le plateau */
int VerifPionsSurPlateau(TypeContents joueur) {
    int i, j;

    for (i = 0; i != 6; i++) {
        for (j = 0; j != 5; j++) {
            if (plateau[i][j] == joueur)
                return 0;// 0 == vrai
        }
    }

    return 1;
}

/* Au début du jeu le 1er joueur est tiré au sort */
void TireAuSortJoueur(TypeContents *joueur) {
    if (rand() % 2)
        *joueur = HOMME;
    else
        *joueur = DEMON;
}

