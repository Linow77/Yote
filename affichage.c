#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include "affichage.h"


void chargement (Ressource *sprite)
{
	sprite->pion_d=SDL_LoadBMP("pion_demonv3.bmp");
	sprite->pion_h=SDL_LoadBMP("pion_hommev3.bmp");
	sprite->case_v=SDL_LoadBMP("cachev3.bmp");
	sprite->cache_info=SDL_LoadBMP("cache_info.bmp");
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

	/*Chargement Icône*/
	SDL_WM_SetIcon(SDL_LoadBMP("logo.bmp"), NULL);

	// Paramètres
	SDL_EnableKeyRepeat(10,10); // Touches appuyées

	// Chargement Ecran
	ecran->image = SDL_SetVideoMode(1000, 760, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	// Nom du jeu
	SDL_WM_SetCaption("YOTE", NULL);

	// Chargement Fond
	fond->position.x = 0;
	fond->position.y = 0;
	fond->image=SDL_LoadBMP("menu_principal.bmp");

	return;
}

void affiche_menu(img fond, img ecran)
{
	SDL_BlitSurface(fond.image, NULL, ecran.image, &fond.position);
	SDL_Flip(ecran.image);
}


/** Permet de vérifier si un clic appartient au plateau du jeu ou non  **/
int VerifDansPlateau(Point clic)
{
 return(145<clic.x && clic.x<855 && 150<clic.y && clic.y<740); //SUR LE PLATEAU
}

/** Afficher Pion **/
void AfficherPion(img *pion, Ressource sprite, Point hg, int joueur)
{
	if(joueur==0)
		pion->image=sprite.pion_d;
	else
		pion->image=sprite.pion_h;

	SDL_SetColorKey(pion->image,SDL_SRCCOLORKEY,SDL_MapRGB(pion->image->format,255, 0, 255));
	pion->position.x=hg.x;
	pion->position.y=hg.y;
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
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONQUITTERX1)&&(in.mousex<BOUTTONQUITTERX2)&&(in.mousey>BOUTTONQUITTERY1)&&(in.mousey<BOUTTONQUITTERY2);
}

/**  Permet de vérifier si l’utilisateur a cliqué sur le bouton jouer dans le premier menu  **/
int VerifMenu1(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONJOUERX1)&&(in.mousex<BOUTTONJOUERX2)&&(in.mousey>BOUTTONJOUERY1)&&(in.mousey<BOUTTONJOUERY2);
}

/**  Permet de vérifier si l’utilisateur clique sur le bouton 1 VS 1 **/
int Verif1Vs1(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTON1V1X1)&&(in.mousex<BOUTTON1V1X2)&&(in.mousey>BOUTTON1V1Y1)&&(in.mousey<BOUTTON1V1Y2);
}

/**  Permet de vérifier si l’utilisateur clique sur le bouton 1 VS IA **/
int Verif1VsIA(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTON1VSIAX1)&&(in.mousex<BOUTTON1VSIAX2)&&(in.mousey>BOUTTON1VSIAY1)&&(in.mousey<BOUTTON1VSIAY2);
}

/**  Permet de vérifier si l’utilisateur clique sur le bouton Mode simple **/
int VerifModeSimple(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONSIMPLEX1)&&(in.mousex<BOUTTONSIMPLEX2)&&(in.mousey>BOUTTONSIMPLEY1)&&(in.mousey<BOUTTONSIMPLEY2);
}

/**  Permet de vérifier si l’utilisateur clique sur le bouton Mode variante **/
int VerifModeVariante(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONVARIANTEX1)&&(in.mousex<BOUTTONVARIANTEX2)&&(in.mousey>BOUTTONVARIANTEY1)&&(in.mousey<BOUTTONVARIANTEY2);
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
	
	TTF_Init(); // Appel de la fct qui perlet d'écrire
	police = TTF_OpenFont("RuneicityDecorative001.ttf", 30); //on charge la police
	SDL_Color couleurNoire = {0, 0, 0}; 
	SDL_Surface *cache=NULL,*texte = NULL , *texte1 = NULL, *texte2 = NULL, *texte3 = NULL; //initialisation des surface de texte et d'effacement
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
	
	SDL_Flip(ecran.image);
	TTF_CloseFont(police);
    TTF_Quit();
    
    SDL_FreeSurface(cache);
	SDL_FreeSurface(texte);
	SDL_FreeSurface(texte1);
	SDL_FreeSurface(texte2);
	SDL_FreeSurface(texte3);
}


 //MAIN
int main(int argc, char *argv[])
{
	int tour= 0, joueur=0, estPremierClic=1, estCoupValide = 0, aMangerAdversaire = 0, JoueurAd;
	Point clic, hg1,hg2, hgDelete;
	Case case1, case2;
	Player joueurs[2];
	img fond,ecran,pion, case_vide;
	Input in; //VARIABLE GESTION EVENEMENT
	Ressource sprite;

	/** INITIALISATION DU PLATEAU **/
	InitPlateau();
	/** INITIALISATION DES JOUEURS **/
	Init_joueurs(joueurs);
	/** tiré au sort du joueur **/
	TireAuSortJoueur(joueurs);
	/** CHARGEMENT DES IMAGES **/
	chargement(&sprite);
	

	//CHARGEMENT DES IMAGES & POSITIONS DES OBJETS
	chargement_objets(&fond, &ecran);

	//GESTION DES EVENEMENTS :
	memset(&in,0,sizeof(in));

	//On affiche le menu si la partie n'a pas commencée MENU 0
	affiche_menu(fond,ecran);


	while((!in.key[SDLK_ESCAPE]) && (!in.quit)) //TANT QUE L'UTILISATEUR N'A PAS QUITTÉ
	{
		UpdateEvents(&in);

		//SI ON CLIC SUR UN BOUTON DU MENU

		//SI ON CLIC SUR JOUER MENU 1
		if (VerifMenu1(in)&&(tour==0))
		{
			tour=1;
			fond.image=SDL_LoadBMP("ChoixAdv.bmp");
			affiche_menu(fond,ecran);

			//On remet le compteur de clic à 0 pour pouvoir récuperer d'autres clic
			in.mousebuttons[SDL_BUTTON_LEFT]=0;
		}

		//1 VS 1
		if (Verif1Vs1(in)&&(tour==1))
		{
			tour=2;
			fond.image=SDL_LoadBMP("menuChoix.bmp");
			affiche_menu(fond,ecran);

			in.mousebuttons[SDL_BUTTON_LEFT]=0;
		}
		//1 VS IA
		if (Verif1VsIA(in)&&(tour==1))
		{
			tour=2;
			fond.image=SDL_LoadBMP("menuChoix.bmp");
			affiche_menu(fond,ecran);
			in.mousebuttons[SDL_BUTTON_LEFT]=0;
		}

		//si on choisit le mode simple
		if (VerifModeSimple(in)&&(tour==2))
		{
			tour=3;
			fond.image=SDL_LoadBMP("table.bmp");
			affiche_menu(fond,ecran);
			infoPartie(ecran, joueurs,sprite);
			in.mousebuttons[SDL_BUTTON_LEFT]=0;
		}

		//si on choisit le mode variante
		if (VerifModeVariante(in)&&(tour==2))
		{
			tour=3;
			fond.image=SDL_LoadBMP("table.bmp");
			affiche_menu(fond,ecran);
			infoPartie(ecran, joueurs,sprite);
			in.mousebuttons[SDL_BUTTON_LEFT]=0;
			
		}

		//SI ON CLIC SUR SCORE
		/* a venir */
		// si on est dans le mode jeux simple et il existe des pions pour les deux joueurs sur le plateau
		if(tour==3 && ( VerifPionsSurPlateau(joueurs[0]) || VerifPionsSurPlateau(joueurs[1]) || estPremierClic))
		{	
			
			estCoupValide = 0;
			//si l'utilisateur a cliqué sur le button gauche de la souris
			if(in.mousebuttons[SDL_BUTTON_LEFT])
			{
				in.mousebuttons[SDL_BUTTON_LEFT]=0;
				estPremierClic=0;
				clic.x=in.mousex;
				clic.y=in.mousey;

				case1=PointToCase(clic);
				// si cette case est dans le plateau
				if(case1.x!=-1 && case1.y!=-1)

				{
					//si la case est vide
					if(VerifCaseVide(case1))
					{
						estCoupValide = 1;
						hg1=CaseToPointhg(case1);
						AfficherPion(&pion, sprite, hg1, joueur);

						ChangerContenuCase(case1, &joueurs[joueur]);

						infoPartie(ecran, joueurs,sprite);
						SDL_BlitSurface(pion.image, NULL, ecran.image, &pion.position);
						SDL_Flip(ecran.image);
					}
					//si la case de départ dipose un pion qui appartient au joueur
					else if(VerifMemeType(case1, joueurs[joueur]))
					{
						in.mousebuttons[SDL_BUTTON_LEFT]=0;

						//si l'utilisateur a cliqué sur le button gauche de la souris
						UpdateEvents(&in);
						do {
							estCoupValide = 0;
							UpdateEvents(&in);

							if (in.mousebuttons[SDL_BUTTON_LEFT])
							{

								clic.x=in.mousex;
								clic.y=in.mousey;

								case2=PointToCase(clic);

								//si la case destination est dans le plateau
								if(case2.x!=-1 && case2.y!=-1)
								{
									in.mousebuttons[SDL_BUTTON_LEFT]=0;

									if(VerifCaseVide(case2) && (VerifDeplacementOrthogonal(case1,case2)
										|| VerifCoupValide(case1, case2, joueurs[joueur].JoueurT)))
									{

										// DANS LE CAS OU LE JOUEUR VEUT MANGER LE PION DE L'ADVERSAIRE
										if(VerifCoupValide(case1, case2, joueurs[joueur].JoueurT))
										{
											aMangerAdversaire = 1;
											Case caseASupprimer = DetermineCaseASupprimer(case1, case2);
											hgDelete=CaseToPointhg(caseASupprimer);

											JoueurAd=NbJoueurAdv(joueur);
											AppliqueCoupV2(case1, caseASupprimer, case2, &joueurs[joueur], &joueurs[JoueurAd] );

											// ON CHANGE LE JOUEUR POUR SUPPRIMER LE PION DE LADVERSAIRE
											Changer_joueur(&joueur);
											SupprimerPion(&case_vide,sprite, hgDelete, joueur);
											// ON REVIENT SUR LE JOUEUR INITIAL
											Changer_joueur(&joueur);

											infoPartie(ecran, joueurs,sprite);
											SDL_BlitSurface(pion.image, NULL, ecran.image, &pion.position);
											SDL_BlitSurface(case_vide.image, NULL, ecran.image, &case_vide.position);
											SDL_Flip(ecran.image);
										}
										else
										{
											AppliqueCoup(case1, case2, joueurs[joueur].JoueurT);
										}

										//Afin d'eviter la redondance du coup ce code va etre appliquer dans le cas ou on
										//manger adversaire ou dans le cas ou on va faire juste un mouvement orthogonal
										// c'est pour ca il est mis ici donc il sera appliquer qq soit le type de mouvement

										estCoupValide = 1;

										hg1=CaseToPointhg(case1);
										hg2=CaseToPointhg(case2);

										infoPartie(ecran, joueurs,sprite);
										AfficherPion(&pion, sprite, hg2, joueur);
										SupprimerPion(&case_vide,sprite, hg1, joueur);
										SDL_BlitSurface(pion.image, NULL, ecran.image, &pion.position);
										SDL_BlitSurface(case_vide.image, NULL, ecran.image, &case_vide.position);
										SDL_Flip(ecran.image);

										// prendre deuxieme pion aux choix apres avoir manger le pion de ladversaire
										if(aMangerAdversaire) 
										{
											in.mousebuttons[SDL_BUTTON_LEFT]=0;

											estCoupValide = 0;
											do {
												UpdateEvents(&in);

												if (in.mousebuttons[SDL_BUTTON_LEFT])
												{
													clic.x=in.mousex;
													clic.y=in.mousey;
													// nouvelle case a manger de l'adversaire que l'on stocke dans case 2
													case1=PointToCase(clic);
													in.mousebuttons[SDL_BUTTON_LEFT]=0;

													// on vérifie qu'il s'agit d'une case de l'adversaire
													// et qu'elle n'est pas vide
													if(plateau[case1.x][case1.y] != VIDE
														&& plateau[case1.x][case1.y] != joueurs[joueur].JoueurT) {
														estCoupValide = 1;
														hgDelete=CaseToPointhg(case1);

														JoueurAd=NbJoueurAdv(joueur);
														AppliqueCoupV3(case1, &joueurs[joueur], &joueurs[JoueurAd]);

														// ON CHANGE LE JOUEUR POUR SUPPRIMER LE NOUVEAU PION DE L'ADVERSAIRE
														Changer_joueur(&joueur);
														SupprimerPion(&case_vide,sprite, hgDelete, joueur);
														// ON REVIENT SUR LE JOUEUR INITIAL
														Changer_joueur(&joueur);

														infoPartie(ecran, joueurs,sprite);
														SDL_BlitSurface(pion.image, NULL, ecran.image, &pion.position);
														SDL_BlitSurface(case_vide.image, NULL, ecran.image, &case_vide.position);
														SDL_Flip(ecran.image);
													} 
												}

											} while(!estCoupValide && (!in.key[SDLK_ESCAPE]) && (!in.quit));

										}
									}
								}
							}
						}while(!estCoupValide && (!in.key[SDLK_ESCAPE]) && (!in.quit));
					}
				}

				if(estCoupValide)
				{
					Changer_joueur(&joueur);
				}

			}
		}

		//SI ON CLIC SUR QUITTER
		if (VerifQuitter(in) &&(tour==0))
		{		
			//SDL_FreeSurface(text);
			SDL_Quit();
			
		}
	}
	return EXIT_SUCCESS;
}