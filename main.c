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
    int piece_cap;// nombre de pièces capturées
    int piece_reserve;// - dans la réserve
    int piece_plateau;// - sur le plateau
    // char nom[20];
} Player;

typedef struct Move {
    Case ancienne_position;
    Case nouvelle_position;
} Move;

void TireAuSortJoueur(Player joueurs[]);
void InitPlateau();
int VerifCaseVide(Case c);
int VerifPionsSurPlateau(TypeContents joueur);
int VerifDeplacementOrthogonal(Case c1, Case c2);
void AffichePlateauCLI();
void Init_joueur(Player *player);
void Init_joueurs(Player players[]);
void PlacerPion(Player *p);
void RecupCoordonneesCLI(Case *c);
void ChoisirPion(Player *p, Case *pion);
void DeplacerPion(Player *p);
int MemeType(Case c, TypeContents type);

TypeContents plateau[5][6];

int main()
{
    // Pour pouvoir tirer au sort un joueur (donc générer un nombre aléatoire)
    // Il faut initialiser la graine (une seule fois)
    srand(time(NULL));
    Player joueurs[2];

    InitPlateau();
    Init_joueurs(joueurs);
    AffichePlateauCLI();
    TireAuSortJoueur(joueurs);
    PlacerPion(&(joueurs[0]));
    AffichePlateauCLI();
    PlacerPion(&(joueurs[1]));
    AffichePlateauCLI();
    DeplacerPion(&(joueurs[1]));
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

// Temporaire
void RecupCoordonneesCLI(Case *c) {
    printf("x,y\n");
    scanf(" %d", &c->x);
    scanf(" %d", &c->y);
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
void TireAuSortJoueur(Player joueurs[]) {
    if (rand() % 2) {
        joueurs[0].JoueurT = HOMME;
        joueurs[1].JoueurT = DEMON;
    }
    else {
        joueurs[0].JoueurT = DEMON;
        joueurs[1].JoueurT = HOMME;
    }
}

void Init_joueur(Player *player) {
    *player = (Player) { HOMME, 0, 12, 0 };
}

void Init_joueurs(Player players[]) {
    Init_joueur(&(players[0]));
    Init_joueur(&(players[1]));
}

/* Placement d'un pion de la réserve
 * On suppose que la réserve n'est pas vide */
void PlacerPion(Player *p) {
    Case c;

    do {
        RecupCoordonneesCLI(&c);// TODO: à remplacer
    } while (!VerifCaseVide(c));

    plateau[c.y][c.x] = p->JoueurT;
    p->piece_reserve--;
    p->piece_plateau++;
}

void ChoisirPion(Player *p, Case *pion) {
    Case c;

    do {
        printf("Choisir pion\n");
        RecupCoordonneesCLI(&c);// TODO: à remplacer
        // on vérifie que le pion sélectionné est bien à soi
    } while (!MemeType(c, p->JoueurT));

    *pion = c;
}

int MemeType(Case c, TypeContents type) {
    return plateau[c.y][c.x] == type;
}

void DeplacerPion(Player *p) {
    Case pion, dest;

    ChoisirPion(p, &pion);

    do {
        printf("Destination\n");
        RecupCoordonneesCLI(&dest);// TODO: à remplacer
        // on vérifie que le pion sélectionné est bien sur une case
        // vide et que le déplacement est orthogonal
    } while (!(VerifCaseVide(dest) && VerifDeplacementOrthogonal(pion, dest)));

    plateau[pion.y][pion.x] = VIDE;
    plateau[dest.y][dest.x] = p->JoueurT;
}
