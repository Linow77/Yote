#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structures

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

// Prototypes

void TireAuSortJoueur(Player joueurs[]);
void InitPlateau();
void AffichePlateauCLI();
void Init_joueur(Player *player);
void Init_joueurs(Player players[]);
void PlacerPion(Player *p);
void RecupCoordonneesCLI(Case *c);
void ChoisirPion(Player *p, Case *pion);
void DeplacerPion(Player *p);
Case *VerifMouvementsValides(Case depart, int *taille);
void AppliqueCoup(Case pion, Case dest, TypeContents type);
void SetCase(Case *c, int x, int y);
int VerifCaseVide(Case c);
int VerifPionsSurPlateau(TypeContents joueur);
int VerifDeplacementOrthogonal(Case c1, Case c2);
int MemeType(Case c, TypeContents type);
int EqlMove(Move m1, Move m2);
int EqlCase(Case c1, Case c2);
int VerifDansPlateau(Case c);
TypeContents Adversaire(TypeContents joueur);

//void test_mouv();

// Variable globale

TypeContents plateau[5][6];

// Main

int main()
{
    // Pour pouvoir tirer au sort un joueur (donc générer un nombre aléatoire)
    // Il faut initialiser la graine (une seule fois)
    srand(time(NULL));
    Player joueurs[2];

    InitPlateau();
    Init_joueurs(joueurs);

    // Test
    AffichePlateauCLI();
    TireAuSortJoueur(joueurs);

    PlacerPion(&(joueurs[0]));
    AffichePlateauCLI();

    PlacerPion(&(joueurs[1]));
    AffichePlateauCLI();

    //DeplacerPion(&(joueurs[0]));
    //AffichePlateauCLI();

    return 0;
}

// Définition des fonctions

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
    printf("Entrez les coordonnées de la case\n");
    printf("x: ");
    scanf(" %d", &c->x);
    printf("y: ");
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

    /*
     * test
    Case *mouv = NULL;
    int taille;
    mouv = VerifMouvementsValides(c, &taille);
    int i;
    for (i = 0; i < taille; i++)
        printf("%d %d\n", mouv[i].x, mouv[i].y);
    free(mouv);
    */
}

/* Le joueur choisit un pion du plateau */
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

// A renommer ?
// Dans AppliqueCoup on déplace aussi le pion...
void DeplacerPion(Player *p) {
    Case pion, dest;

    ChoisirPion(p, &pion);

    // TODO: ChoisirDestination() ?
    // {
    do {
        printf("Destination\n");
        RecupCoordonneesCLI(&dest);// TODO: à remplacer
        // TODO: Conditions à remplacer par autre chose:
        // on vérifie que la destination est dans le
        // tableau des mouvements possibles
    } while (!(VerifCaseVide(dest) && VerifDeplacementOrthogonal(pion, dest)));
    // }

    AppliqueCoup(pion, dest, p->JoueurT);
}

void AppliqueCoup(Case pion, Case dest, TypeContents type)
{
    plateau[pion.y][pion.x] = VIDE;
    plateau[dest.y][dest.x] = type;
}

// Renvoie les mouvements possible que peut faire un pion
// Ne pas oublier le free !
// A améliorer ?
Case *VerifMouvementsValides(Case depart, int *taille)
{
    int i = 0;
    TypeContents joueur;
    TypeContents advers;
    Case *mouv;
    Case c;

    joueur = plateau[depart.y][depart.x];
    advers = Adversaire(joueur);
    // le nombre de déplacements possible est au plus 4
    mouv = (Case *) malloc(sizeof(Case) * 4);

    // Horizontal
    // s'il y a un adversaire à côté du joueur,
    // le joueur peut sauter par-dessus le pion
    // sinon il se déplace à côté
    if (plateau[depart.y][depart.x - 1] == advers)
    {
        SetCase(&c, depart.x - 2, depart.y);
        if (VerifDansPlateau(c))
            if (VerifCaseVide(c)) mouv[i++] = c;
    }
    else
    {
        SetCase(&c, depart.x - 1, depart.y);
        if (VerifDansPlateau(c))
            if (VerifCaseVide(c)) mouv[i++] = c;
    }

    if (plateau[depart.y][depart.x + 1] == advers)
    {
        SetCase(&c, depart.x + 2, depart.y);
        if (VerifDansPlateau(c))
            if (VerifCaseVide(c)) mouv[i++] = c;
    }
    else
    {
        SetCase(&c, depart.x + 1, depart.y);
        if (VerifDansPlateau(c))
            if (VerifCaseVide(c)) mouv[i++] = c;
    }

    // Vertical
    if (plateau[depart.y + 1][depart.x] == advers)
    {
        SetCase(&c, depart.x, depart.y + 2);
        if (VerifDansPlateau(c))
            if (VerifCaseVide(c)) mouv[i++] = c;
    }
    else
    {
        SetCase(&c, depart.x, depart.y + 1);
        if (VerifDansPlateau(c))
            if (VerifCaseVide(c)) mouv[i++] = c;
    }

    if (plateau[depart.y - 1][depart.x] == advers)
    {
        SetCase(&c, depart.x, depart.y - 2);
        if (VerifDansPlateau(c))
            if (VerifCaseVide(c))
                mouv[i++] = c;
    }
    else
    {
        SetCase(&c, depart.x, depart.y - 1);
        if (VerifDansPlateau(c))
            if (VerifCaseVide(c)) mouv[i++] = c;
    }

    // on re alloue le tableau avec une nouvelle taille
    if (i != 4)
        mouv = (Case *) realloc(mouv, sizeof(Case) * i);

    // le tableau est alloué dynamiquement, on a
    // forcément besoin de sa taille
    *taille = i;

    return mouv;
}

// Vérifie qu'une coordonnée est bien dans le plateau
// >= 0 et < 5 (abscisse)
// >= 0 et < 6 (ordonnée)
int VerifDansPlateau(Case c)
{
    return c.x >= 0 && c.x < 5 && c.y >= 0 && c.y < 6;
}

void SetCase(Case *c, int x, int y)
{
    c->x = x;
    c->y = y;
}

// Renvoie le type de l'adversaire (DEMON ou HOMME)
TypeContents Adversaire(TypeContents joueur)
{
    if (joueur == DEMON) return HOMME;
    else return DEMON;
}

// Vérifie si un mouvement est égal à un autre
// Remplacé par VerifSurSesPas
int EqlMove(Move m1, Move m2)
{
    return EqlCase(m1.ancienne_position, m2.nouvelle_position) && EqlCase(m1.nouvelle_position, m2.ancienne_position);
}

// Vérifie qu'une case est égale à une autre
int EqlCase(Case c1, Case c2)
{
    return c1.x == c2.x && c1.y == c2.y;
}

// Tests

/*
void test_mouv()
{
    Case c1 = { 3, 2 };
    Case c2 = { 4, 2 };
    Case c3 = { 5, 2 };
    Move mouv  = (Move) { c1, c2 };
    Move mouv2 = (Move) { c2, c1 };
    Move mouv3 = (Move) { c3, c1 };

    if (EqlMove(mouv, mouv2))
        printf("meme mouvement\n");
    if (!EqlMove(mouv, mouv3))
        printf("pas Meme mouvement2\n");
}
*/


