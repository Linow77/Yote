
#include "affichage.h"
void chargement (Ressource *sprite)
{
	sprite->pion_d=SDL_LoadBMP("pion_demonv3.bmp");
	sprite->pion_h=SDL_LoadBMP("pion_hommev3.bmp");
	sprite->case_v=SDL_LoadBMP("cachev3.bmp");
	sprite->cache_info=SDL_LoadBMP("cache_info.bmp");
	sprite->ecran_de_fin=SDL_LoadBMP("ecrandefin.bmp");
}


void rafraichir(SDL_Surface *s)
{
	SDL_Flip(s);
}


Case PointToCase(Point clic)
{
	Case case1;

	if(VerifDansPlateau(clic)) //SUR LE PLATEAU
	{
		case1.x=(clic.x-146)/116;
		case1.y=(clic.y-151)/116;

	}else{
		case1.x=-1; //EN DEHORS DU PLATEAU
		case1.y=-1;
	}

	return case1;
}

Point CaseToPointhg(Case case1)
{
	Point p;
	p.x=case1.x*120 +145;
	p.y=case1.y*120 +149;

	return p;
}


void UpdateEvents(Input* in)
{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
				switch (event.type)
				{
				case SDL_KEYDOWN:
						in->key[event.key.keysym.sym]=1;
						break;
				case SDL_KEYUP:
						in->key[event.key.keysym.sym]=0;
						break;
				case SDL_MOUSEMOTION:
						in->mousex=event.motion.x;
						in->mousey=event.motion.y;
						in->mousexrel=event.motion.xrel;
						in->mouseyrel=event.motion.yrel;
						break;
				case SDL_MOUSEBUTTONDOWN:
						in->mousebuttons[event.button.button]=1;
						break;
				case SDL_MOUSEBUTTONUP:
						in->mousebuttons[event.button.button]=0;
						break;
				case SDL_QUIT:
						in->quit = 1;
						break;
				default:
						break;
				}
		}
}

void chargement_objets(img* fond,img* ecran)
{
	//A METTRE AVANT LE SET ICONE
	SDL_Init(SDL_INIT_VIDEO);
	// Police
    TTF_Init();

	/*Chargement Icône*/
	SDL_WM_SetIcon(SDL_LoadBMP("logo.bmp"), NULL);

	// Paramètres
	SDL_EnableKeyRepeat(10,10); // Touches appuyées

	// Chargement Ecran
	ecran->image = SDL_SetVideoMode(1000, 760, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);


	// Nom du jeu
	titre_fenetre("YOTE");

	// Chargement Fond
	fond->position.x = 0;
	fond->position.y = 0;
	fond->image=SDL_LoadBMP("menu_principal.bmp");

	return;
}

void affiche_menu(img fond, img ecran)
{
	SDL_BlitSurface(fond.image, NULL, ecran.image, &fond.position);
	rafraichir(ecran.image);
}

/*
void affiche_scores(TTF_Font *police, img fond, TableScore *t)
{
	SDL_Color couleurNoire = {0, 0, 0};
    //SDL_Surface *ecran = NULL;
	//SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
	fond.image=SDL_LoadBMP("scores_bg.jpg");
	TTF_RenderText_Blended(police, "Salut les Zér0s !", couleurNoire);
}
*/

/** Permet de vérifier si un clic appartient au plateau du jeu ou non  **/
int VerifDansPlateau(Point clic)
{
 return(145<clic.x && clic.x<855 && 150<clic.y && clic.y<740); //SUR LE PLATEAU
}

/** Afficher Pion **/
void AfficherPion(img ecran,img *pion, Ressource sprite, Point hg, int joueur)
{
	if(joueur==0)
		pion->image=sprite.pion_d;
	else
		pion->image=sprite.pion_h;

	SDL_SetColorKey(pion->image,SDL_SRCCOLORKEY,SDL_MapRGB(pion->image->format,255, 0, 255));
	pion->position.x=hg.x;
	pion->position.y=hg.y;
	SDL_BlitSurface(pion->image, NULL, ecran.image, &pion->position);
}

/** Supprimer Pion **/
void SupprimerPion(img *caseVide, Ressource sprite, Point hg, int joueur)
{
	caseVide->image=sprite.case_v;
	caseVide->position.x=hg.x;
	caseVide->position.y=hg.y;
}

/** Permet d’initialiser les cases du plateau à VIDE **/
void InitPlateau()
{
	int i, j;

	for (i = 0; i != 6; i++) {
		for (j = 0; j != 5; j++) {
			plateau[i][j] = VIDE;
		}
	}
}

/** Initialiser Les joueurs **/
void Init_joueurs(Player players[])
{
	Init_joueur(&(players[0]));
	Init_joueur(&(players[1]));
}

/** Permet d’initialiser un joueur **/
void Init_joueur(Player *player)
{
	*player = (Player) { VIDE, 0, 12, 0 };
}

/** Permet de faire un tirage au sort du premier joueur **/
void TireAuSortJoueur(Player joueurs[])
{
	if (rand() % 2) {
		joueurs[0].JoueurT = HOMME;
		joueurs[1].JoueurT = DEMON;
	}
	else {
		joueurs[0].JoueurT = DEMON;
		joueurs[1].JoueurT = HOMME;
	}
}
/** Changement du joueur courant **/
void Changer_joueur(int *joueur)
{
	if(*joueur == 0)
		*joueur = 1;
	else
		*joueur = 0;
}


/** Permet de vérifier si l’utilisateur a cliqué sur le bouton quitter dans le premier menu **/
int VerifQuitter(Input in)
{
	return VerifClicDansSurface(in, BOUTTONQUITTERX1, BOUTTONQUITTERY1, BOUTTONQUITTERX2, BOUTTONQUITTERY2);
}

/**  Permet de vérifier si l’utilisateur a cliqué sur le bouton jouer dans le premier menu  **/
int VerifMenu1(Input in)
{
	return VerifClicDansSurface(in, BOUTTONJOUERX1, BOUTTONJOUERY1, BOUTTONJOUERX2, BOUTTONJOUERY2);
}

/**  Permet de vérifier si l’utilisateur clique sur le bouton 1 VS 1 **/
int Verif1Vs1(Input in)
{
	return VerifClicDansSurface(in, BOUTTON1V1X1, BOUTTON1V1Y1, BOUTTON1V1X2, BOUTTON1V1Y2);
}

/**  Permet de vérifier si l’utilisateur clique sur le bouton 1 VS IA **/
int Verif1VsIA(Input in)
{
	return VerifClicDansSurface(in, BOUTTON1VSIAX1, BOUTTON1VSIAY1, BOUTTON1VSIAX2, BOUTTON1VSIAY2);
}

/**  Permet de vérifier si l’utilisateur clique sur le bouton Mode simple **/
int VerifModeSimple(Input in)
{
	return VerifClicDansSurface(in, BOUTTONSIMPLEX1, BOUTTONSIMPLEY1, BOUTTONSIMPLEX2, BOUTTONSIMPLEY2);
}

/**  Permet de vérifier si l’utilisateur clique sur le bouton Mode variante **/
int VerifModeVariante(Input in)
{
	return VerifClicDansSurface(in, BOUTTONVARIANTEX1, BOUTTONVARIANTEY1, BOUTTONVARIANTEX2, BOUTTONVARIANTEY2);
}

int VerifMenuScores(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT] && in.mousex > BOUTON_SCORES_X1 &&
		   in.mousex < BOUTON_SCORES_X2 && in.mousey > BOUTON_SCORES_Y1 &&
		   in.mousey < BOUTON_SCORES_Y2;
}

/** Permet de changer les valeurs des cases du tableau lors d’un mouvement sans manger de pion **/
void AppliqueCoup(Case pion, Case dest, TypeContents type)
{
	plateau[pion.x][pion.y] = VIDE;
	plateau[dest.x][dest.y] = type;
}

/** Permet de changer les valeurs des pions capturés et celles sur le plateau **/
void ModifierNbPiece(Player *joueurAct, Player *joueurAdv )
{
	joueurAct->piece_cap ++;
	joueurAdv->piece_plateau --;
}

/** Permet de changer le contenu des cases du plateau et les valeurs des pions capturés et ceux sur le plateau lorsqu'on mange un pion	**/
void AppliqueCoupV2(Case pion, Case adversaire, Case dest, Player *joueurAct, Player *joueurAdv )
{
	AppliqueCoup(pion, dest, joueurAct->JoueurT);
	plateau[adversaire.x][adversaire.y] = VIDE;
	ModifierNbPiece(joueurAct,joueurAdv);

}
/**Permet de changer le contenu des cases du plateau et les valeurs des pions capturés et ceux sur le plateau lorsqu'on choisir le 2è pion à prendre **/
void AppliqueCoupV3(Case casePion, Player *joueurAct, Player *joueurAdv)
{
	plateau[casePion.x][casePion.y] = VIDE;
	ModifierNbPiece(joueurAct,joueurAdv);
}

/** Permet de changer le contenu du case lorsque l’on place un pion sur le plateau **/
void ChangerContenuCase(Case c , Player *joueur)
{
	plateau[c.x][c.y] = joueur->JoueurT;
	joueur->piece_plateau ++;
	joueur-> piece_reserve --;
}

/** Vérifie qu’un joueur a encore des pions sur le plateau **/
int VerifPionsSurPlateau(Player joueur)
{
	return joueur.piece_plateau > 0;
}
 /** Vérifie qu’une case du plateau est vide **/
int VerifCaseVide(Case c)
{
	return plateau[c.x][c.y] == VIDE;
}
/** Vérifie que la case contient un pion du joueur **/
 int VerifMemeType(Case c, Player joueur)
{
	return plateau[c.x][c.y] == joueur.JoueurT;
}

/** Vérifie que la joueur se déplace Orthogonalement et d'une seule case **/
int VerifDeplacementOrthogonal(Case c1, Case c2)
{
	if ( c2.x == c1.x )
	{
		return (c2.y == c1.y + 1) || (c2.y == c1.y - 1);
	}
	else if ( c2.y == c1.y )
	{
		return (c2.x == c1.x + 1) || (c2.x == c1.x - 1);
	}
	else return 0;
}
 /** Permet de vérifier que le joueur va manger un pion adversaire **/
 int VerifCoupValide(Case caseDepart, Case caseArrivee, TypeContents type)
{
	//mouvement horizontal
	if(caseDepart.x == caseArrivee.x) {
		if(plateau[caseArrivee.x][caseArrivee.y - 1] != VIDE && plateau[caseArrivee.x][caseArrivee.y - 1] != type) {
			return 1;
		}

		if(plateau[caseArrivee.x][caseArrivee.y + 1] != VIDE && plateau[caseArrivee.x][caseArrivee.y + 1] != type) {
			return 1;
		}
	}

	// mouvement vertical **/
	if(caseDepart.y == caseArrivee.y) {
		if(plateau[caseArrivee.x -1][caseArrivee.y] != VIDE && plateau[caseArrivee.x -1][caseArrivee.y] != type) {
			return 1;
		}
		if(plateau[caseArrivee.x +1][caseArrivee.y] != VIDE && plateau[caseArrivee.x +1][caseArrivee.y] != type) {
			return 1;
		}
	}
	return 0 ;
}

/** Permet de déterminer le numéro du joueur adversaire **/
int NbJoueurAdv(int joueurAct)
{
	if(joueurAct == 0)
		return 1;
	else
		return 0;
}

/** Permet de déterminer la case à supprimer en fonction de la case de départ et de la case d'arrivée **/
Case DetermineCaseASupprimer (Case case1, Case case2)
{
	Case caseASupprimer;

	if(case1.x > case2.x) {
		caseASupprimer.x = case1.x - 1;
		caseASupprimer.y = case1.y;

	} else if (case1.x < case2.x){
		caseASupprimer.x = case1.x + 1;
		caseASupprimer.y = case1.y;

	} else if(case1.y > case2.y) {
		caseASupprimer.x = case1.x;
		caseASupprimer.y = case1.y - 1;

	} else if (case1.y < case2.y) {
		caseASupprimer.x = case1.x;
		caseASupprimer.y = case1.y + 1;
	}

	return caseASupprimer;
}

void infoPartie(img ecran, Player joueurs[],Ressource sprite)
{
	char pionM1[2] = "";  /*Tableau de char suffisamment grand pour contenir le nombre de pions mangés du J1*/
	char pionM2[2] = "";  /*Tableau de char suffisamment grand pour contenir le nombre de pions mangés du J2*/
	char pionR1[2] = "";  /*Tableau de char suffisamment grand pour contenir le nombre de pions restants du J1*/
	char pionR2[2] = "";  /*Tableau de char suffisamment grand pour contenir le nombre de pions restants du J2*/

	TTF_Font *police = NULL; //initialisation de la police

	TTF_Init(); // Appel de la fct qui permet d'écrire
	police = TTF_OpenFont("RuneicityDecorative001.ttf", 30); //on charge la police
	SDL_Color couleurNoire = {0, 0, 0};
	SDL_Surface *texte = NULL , *texte1 = NULL, *texte2 = NULL, *texte3 = NULL; //initialisation des surface de texte et d'effacement
	SDL_Rect position,position1,position2,position3; //initialisation des positions des surfaces

	sprintf(pionR1, "%d", joueurs[1].piece_reserve); //on transforme "piece_reserve" en char et on le met dans le tab de char pionR1 car TTF_RenderText_Blended affiche des char
	sprintf(pionM1, "%d", joueurs[1].piece_cap);
	sprintf(pionM2, "%d", joueurs[0].piece_cap);
	sprintf(pionR2, "%d", joueurs[0].piece_reserve);

	texte = TTF_RenderText_Blended(police,pionM1, couleurNoire); //on charge le texte avec la couleur et la police
	texte1 = TTF_RenderText_Blended(police,pionM2, couleurNoire);
	texte2 = TTF_RenderText_Blended(police,pionR1, couleurNoire);
	texte3 = TTF_RenderText_Blended(police,pionR2, couleurNoire);

	position.x = 195;	position1.x = 780;	position2.x = 315;	position3.x = 640;
	position.y = 20;	position1.y = 20;	position2.y = 65;	position3.y = 65;

	SDL_BlitSurface(sprite.cache_info, NULL, ecran.image, &position); // efface le texte potentielment précedement
	SDL_BlitSurface(sprite.cache_info, NULL, ecran.image, &position1);
	SDL_BlitSurface(sprite.cache_info, NULL, ecran.image, &position2);
	SDL_BlitSurface(sprite.cache_info, NULL, ecran.image, &position3);

	SDL_BlitSurface(texte, NULL, ecran.image, &position2); //on écrit le nouveau texte
	SDL_BlitSurface(texte1, NULL, ecran.image, &position3);
	SDL_BlitSurface(texte2, NULL, ecran.image, &position);
	SDL_BlitSurface(texte3, NULL, ecran.image, &position1);

	position.x=position.x+35;

	SDL_BlitSurface(sprite.cache_info, NULL, ecran.image, &position);

	rafraichir(ecran.image);
	TTF_CloseFont(police);
    TTF_Quit();

	SDL_FreeSurface(texte);
	SDL_FreeSurface(texte1);
	SDL_FreeSurface(texte2);
	SDL_FreeSurface(texte3);
}

void afficheFinJeu(img ecran, Ressource sprite, Player gagnant) // IL FAUT RÉCUPÉRER LES SCORES DES JOUEURS
{
	// a enlever
	int score_joueur1=5, score_joueur2=0;
	char pseudo_joueur1[10] = "Anastasii"; //LE PSEUDO EST DE 9 CARACTERE MAXIMUM
	char pseudo_joueur2[10] = "Carla";
	// a enlever

	/** AFFICHAGE DU FOND **/
	SDL_Rect position;
	position.x = 100;
	position.y = 200;

	SDL_BlitSurface(sprite.ecran_de_fin, NULL, ecran.image, &position);


	/** 	AFFICHAGE DES PIONS 	**/
	img pion;
	Point position_pion;
	position_pion.x = 220;
	position_pion.y = 350;

	if (gagnant.JoueurT == HOMME)
	{
		//affichage pion homme
		AfficherPion(ecran,&pion, sprite, position_pion, 1);

		position_pion.x = position_pion.x + 450;
		//affichage pion démon
		AfficherPion(ecran,&pion, sprite, position_pion, 0);


	}else{
		//affichage pion démon
		AfficherPion(ecran,&pion, sprite, position_pion, 0);

		position_pion.x = position_pion.x + 450;
		//affichage pion homme
		AfficherPion(ecran,&pion, sprite, position_pion, 1);

	}

	/** 	AFFICHAGES DU TABLEAU DE FIN 	**/
	char victoire[9] = "victoire";
	char defaite[8] = "defaite";
	char pseudo_vainqueur[10] = "";
	char pseudo_perdant[10] = "";
	char score_vainqueur[2] = "";
	char score_perdant[2] = "";




	TTF_Font *police = NULL; //initialisation de la police

	TTF_Init(); // Appel de la fct qui perlet d'écrire

	police = TTF_OpenFont("RuneicityDecorative001.ttf", 62); //on charge la police

	SDL_Color couleurBordeau = {139, 3, 3};
	SDL_Color couleurNoire = {0, 0, 0};
	SDL_Surface *textevictoire = NULL , *textedefaite = NULL, *pseudovainqueur = NULL, *pseudoperdant = NULL, *scorevainqueur = NULL, *scoreperdant = NULL; //initialisation des surface de texte et d'effacement
	SDL_Rect position1,position2,position3, position4, position5, position6; //initialisation des positions des surfaces

	sprintf(score_vainqueur, "%d", score_joueur1);
	sprintf(score_perdant, "%d", score_joueur2);
	sprintf(pseudo_vainqueur, "%s", pseudo_joueur1);
	sprintf(pseudo_perdant, "%s", pseudo_joueur2);


	TTF_SetFontStyle(police, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);
	textevictoire = TTF_RenderText_Blended(police,victoire, couleurBordeau); //on charge le texte avec la couleur et la police
	textedefaite = TTF_RenderText_Blended(police,defaite, couleurNoire);

	police = TTF_OpenFont("RuneicityDecorative001.ttf", 40); //on charge la police
	TTF_SetFontStyle(police, TTF_STYLE_NORMAL);
	pseudovainqueur = TTF_RenderText_Blended(police,pseudo_vainqueur, couleurBordeau);
	pseudoperdant = TTF_RenderText_Blended(police,pseudo_perdant, couleurNoire);
	scorevainqueur = TTF_RenderText_Blended(police,score_vainqueur, couleurBordeau);
	scoreperdant = TTF_RenderText_Blended(police,score_perdant, couleurNoire);

	position1.x = 150;	position2.x = 600;	position3.x = 150;	position4.x = 600; position5.x = 400;	position6.x = 850;
	position1.y = 250;	position2.y = 250;	position3.y = 520;	position4.y = 520; position5.y = 520;	position6.y = 520;


	SDL_BlitSurface(textevictoire, NULL, ecran.image, &position1); //on écrit le nouveau texte
	SDL_BlitSurface(textedefaite, NULL, ecran.image, &position2);
	SDL_BlitSurface(pseudovainqueur, NULL, ecran.image, &position3);
	SDL_BlitSurface(pseudoperdant, NULL, ecran.image, &position4);
	SDL_BlitSurface(scorevainqueur, NULL, ecran.image, &position5);
	SDL_BlitSurface(scoreperdant, NULL, ecran.image, &position6);

	rafraichir(ecran.image);
	TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(textevictoire);
	SDL_FreeSurface(textedefaite);
	SDL_FreeSurface(pseudovainqueur);
	SDL_FreeSurface(pseudoperdant);
	SDL_FreeSurface(scorevainqueur);
	SDL_FreeSurface(scoreperdant);
}


/* Vérifie qu'un clic est contenu dans une zone entre 2 coordonnées :
 * (x_hg, y_hg) et (x_bd, y_db) => (haut gauche) et (bas droite) */
int VerifClicDansSurface(Input i, int x_hg, int y_hg, int x_bd, int y_db)
{
	return i.mousebuttons[SDL_BUTTON_LEFT] && i.mousex > x_hg &&
		   i.mousex < x_bd && i.mousey > y_hg && i.mousey < y_db;
}

void affiche_coordonnees_clic(Input in)
{
	if (in.mousebuttons[SDL_BUTTON_LEFT])
		printf("x : %d; y : %d\n", in.mousex, in.mousey);
}

void titre_fenetre(char *titre)
{
	SDL_WM_SetCaption(titre, NULL);
}

