#ifndef affichage
#define affichage

//MACROCONSTANTES

/*Coordonnées des boutons*/ 
#define BOUTTONJOUERX1 94
#define BOUTTONJOUERX2 344
#define BOUTTONJOUERY1 502
#define BOUTTONJOUERY2 615

#define BOUTTON1V1X1 130
#define BOUTTON1V1X2 452
#define BOUTTON1V1Y1 476
#define BOUTTON1V1Y2 600

#define BOUTTON1VSIAX1 540
#define BOUTTON1VSIAX2 862
#define BOUTTON1VSIAY1 476
#define BOUTTON1VSIAY2 600

#define BOUTTONSCOREX1 382
#define BOUTTONSCOREX2 622
#define BOUTTONSCOREY1 502
#define BOUTTONSCOREY2 615

#define BOUTTONQUITTERX1 681
#define BOUTTONQUITTERX2 913
#define BOUTTONQUITTERY1 502
#define BOUTTONQUITTERY2 615

#define BOUTTONSIMPLEX1 127
#define BOUTTONSIMPLEX2 450
#define BOUTTONSIMPLEY1 430
#define BOUTTONSIMPLEY2 560

#define BOUTTONVARIANTEX1 540
#define BOUTTONVARIANTEX2 860
#define BOUTTONVARIANTEY1 430
#define BOUTTONVARIANTEY2 560

//STRUCTURES 

/** EVENEMENT **/
typedef struct
{
	char key[SDLK_LAST]; //clavier
	int mousex,mousey; //coordonnés de la souris
	int mousexrel,mouseyrel; //le vecteur déplacement souris
	char mousebuttons[8]; //boutons de la souris 
    char quit;
}Input;

/** IMAGE / POSITION **/
typedef struct
{
	SDL_Surface* image;
	SDL_Rect position;
}img;

/** LOAD IMAGES **/
typedef struct 
{
	// Création des surfaces
	SDL_Surface* pion_d;
	SDL_Surface* pion_h;
	SDL_Surface* case_v;
}Ressource ;

/** CASE **/
typedef struct
{
	int x;//ligne
	int y;//colone
}Case;

/** CLIC **/
typedef struct
{
	int x;
	int y;
}Point;

/** ContenuCase**/
typedef enum TypeContents {
    VIDE, HOMME, DEMON
} TypeContents;

/** JOUEUR **/
typedef struct Player {
    TypeContents JoueurT;
    int piece_cap;// nombre de pièces capturées
    int piece_reserve;// - dans la réserve
    int piece_plateau;// - sur le plateau
    // char nom[20];
} Player;

/** MOUVEMENT **/
typedef struct Move {
    Case ancienne_position;
    Case nouvelle_position;
} Move;

// Variable globale

TypeContents plateau[5][6];

//PROTOTYPES

void chargement(Ressource *sprite);
void UpdateEvents(Input* in);
void chargement_objets(img* fond,img* ecran);
void affiche_menu(img fond, img ecran);
Case PointToCase(Point clic);
Point CaseToPointhg(Case case1);
void AfficherPion(img *pion, Ressource sprite, Point hg, int joueur);
void InitPlateau();
void Init_joueurs(Player players[]);
void Init_joueur(Player *player);
void change_joueur(int *joueur);
int VerifDansPlateau(Point clic);
#endif
