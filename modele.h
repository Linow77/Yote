#ifndef MODELE_H
#define MODELE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#define TAILLE_MAX_NOM 10


typedef struct Case {
    int x;
    int y;
} Case;

typedef enum TypeContents {
    VIDE, HOMME, DEMON
} TypeContents;

// TODO: Mouvement précédent à rajouter ?
typedef struct Player {
    TypeContents JoueurT;
    int piece_cap;// nombre de pièces capturées
    int piece_reserve;// - dans la réserve
    int piece_plateau;// - sur le plateau
	unsigned int score;
    char *nom;
    // int score;
} Player;

typedef struct Move {
    Case ancienne_position;
    Case nouvelle_position;
} Move;


TypeContents plateau[5][6];

Case DetermineCaseASupprimer (Case case1, Case case2);
Case RecupCaseArriveeIA (Case caseDepart);
Case RecupCaseDeSelectionIA (Player joueur);
TypeContents Adversaire(TypeContents joueur);
TypeContents adv(TypeContents joueur);
int EqlCase(Case c1, Case c2);
int MemeType(Case c, TypeContents type);
int NbJoueurAdv(int joueurAct);
int VerifCaseVide(Case c);
int VerifCoupValide(Case caseDepart, Case caseArrivee, TypeContents type);
int VerifDeplacementOrthogonal(Case c1, Case c2);
int VerifMemeType(Case c, Player joueur);
int VerifMouvementsContraires(Move m1, Move m2);
int VerifPionsSurPlateau(Player joueur);
int a_encore_pieces_en_reserve(Player joueur);
int a_encore_pieces_sur_plateau(Player joueur);
int dans_le_plateau(Case c);
int joueur_adv(int joueur);
int pion_peut_manger(Case c, TypeContents joueur);
int pion_peut_se_deplacer(Case c);
int rand_a_b(int a, int b);
int tour_de_homme(Player joueurs[], int joueur);
void AppliqueCoup(Case pion, Case dest, TypeContents type);
void AppliqueCoupV2(Case pion, Case adversaire, Case dest, Player *joueurAct, Player *joueurAdv );
void AppliqueCoupV3(Case casePion, Player *joueurAct, Player *joueurAdv);
void ChangerContenuCase(Case c , Player *joueur);
void Changer_joueur(int *joueur);
void InitPlateau();
void Init_joueur(Player *player);
void Init_joueurs(Player players[]);
void ModifierNbPiece(Player *joueurAct, Player *joueurAdv );
void PlacerPion(Player *p);
void RecupCoordonneesCLI(Case *c);
void SetCase(Case *c, int x, int y);
void TireAuSortJoueur(Player joueurs[]);
void ia_pioche_pion(Case *caseSelection);
void set_case(Case *c, int x, int y);
char *entre_nom_dans_terminal();
//void entre_nom_dans_terminal(Player *joueur);
void joueurs_par_defaut(Player joueurs[]);
void print_player(Player p);
#endif

