#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include "affichage.h"


void chargement (Ressource *sprite)
{
	sprite->pion_d=SDL_LoadBMP("pion_demon.bmp");
	sprite->pion_h=SDL_LoadBMP("pion_homme.bmp");
	sprite->case_v=SDL_LoadBMP("cache.bmp");
}


Case PointToCase(Point clic)
{
	Case case1;

	if(VerifDansPlateau(clic)) //SUR LE PLATEAU
	{
		case1.y=(clic.x-146)/116;
		case1.x=(clic.y-151)/116;

	}else{
		case1.x=-1; //EN DEHORS DU PLATEAU
		case1.y=-1;
	}

	return case1;
}

Point CaseToPointhg(Case case1)
{
	Point p;
	p.y=case1.x*120 +146;
	p.x=case1.y*120 +151;

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


/** Verif clic est dan le tableau **/
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

/** Initialiser les cases du plateau à VIDE **/
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

/** Initialiser joueur **/
void Init_joueur(Player *player) 
{
	*player = (Player) { VIDE, 0, 12, 0 };
}

/** Au début du jeu le 1er joueur qui va jouer est tiré au sort **/
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
/** Changer tour du joueur**/
void Changer_joueur(int *joueur)
{
	if(*joueur == 0)
		*joueur = 1;
	else
		*joueur = 0;
}
/** Verifer si on clic sur Quiter **/
int VerifQuitter(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONQUITTERX1)&&(in.mousex<BOUTTONQUITTERX2)&&(in.mousey>BOUTTONQUITTERY1)&&(in.mousey<BOUTTONQUITTERY2);
}

/**  Verifer si on clic sur MENU 1 **/
int VerifMenu1(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONJOUERX1)&&(in.mousex<BOUTTONJOUERX2)&&(in.mousey>BOUTTONJOUERY1)&&(in.mousey<BOUTTONJOUERY2);
}

/**  Verifer si on clic sur 1Vs1 **/
int Verif1Vs1(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTON1V1X1)&&(in.mousex<BOUTTON1V1X2)&&(in.mousey>BOUTTON1V1Y1)&&(in.mousey<BOUTTON1V1Y2);
}

/**  Verifer si on clic sur 1VsIA **/
int Verif1VsIA(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTON1VSIAX1)&&(in.mousex<BOUTTON1VSIAX2)&&(in.mousey>BOUTTON1VSIAY1)&&(in.mousey<BOUTTON1VSIAY2);
}

/**  Verifer si on choisit le mode simple **/
int VerifModeSimple(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONSIMPLEX1)&&(in.mousex<BOUTTONSIMPLEX2)&&(in.mousey>BOUTTONSIMPLEY1)&&(in.mousey<BOUTTONSIMPLEY2);
}

/**  Verifer si on choisit le mode Variante **/
int VerifModeVariante(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONVARIANTEX1)&&(in.mousex<BOUTTONVARIANTEX2)&&(in.mousey>BOUTTONVARIANTEY1)&&(in.mousey<BOUTTONVARIANTEY2);
}

/** Changer les valeur des cases du tableau lors du mouvements simple sans manger de pion**/
void AppliqueCoup(Case pion, Case dest, TypeContents type)
{
	plateau[pion.x][pion.y] = VIDE;
	plateau[dest.x][dest.y] = type;
}
/** changer les valeurs des pions capté et celles sur le plateau **/
void ModifierNbPiece(Player *joueurAct, Player *joueurAdv )
{
	joueurAct->piece_cap ++;
	joueurAdv->piece_plateau --;
}

/** Changer le contenu des cases du plateau et les valeurs des pions capté et celles sur le plateau
					lorsque on mange un pion								**/
void AppliqueCoupV2(Case pion, Case adversaire, Case dest, Player *joueurAct, Player *joueurAdv )
{
	AppliqueCoup(pion, dest, joueurAct->JoueurT);
	plateau[adversaire.x][adversaire.y] = VIDE;
	ModifierNbPiece(joueurAct,joueurAdv);

}
/**Changer le contenu des cases du plateau et les valeurs des pions capté et celles sur le plateau
					lorsque on choisir le 2eme pion apprendre		 **/
void AppliqueCoupV3(Case casePion, Player *joueurAct, Player *joueurAdv)
{
	plateau[casePion.x][casePion.y] = VIDE;
	ModifierNbPiece(joueurAct,joueurAdv);
}

/** Changer le contenu du case lorsque on place une pion sur le plateau **/
void ChangerContenuCase(Case c , Player *joueur)
{
	plateau[c.x][c.y] = joueur->JoueurT;
	joueur->piece_plateau ++;
	joueur-> piece_reserve --;
}

/** On vérifie que le joueur a des pions sur le plateau **/
int VerifPionsSurPlateau(Player joueur)
{
	return joueur.piece_plateau > 0;
}
 /** Vérifier que la case est vide	**/
int VerifCaseVide(Case c)
{
	return plateau[c.x][c.y] == VIDE;
}
/** Verifer si le pion dans cette case appartient au joueur **/
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
 /** Vérifier que le joueur va manger sur un pion adversaire **/
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

/** Derminer le numéro du joeur addversaire **/
int NbJoueurAdv(int joueurAct)
{
	if(joueurAct == 0)
		return 1;
	else
		return 0;
}

/** Determine la case a supprimer en fonction de la case de depart et de la case d'arrivee**/
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
			in.mousebuttons[SDL_BUTTON_LEFT]=0;
		}

		//si on choisit le mode variante
		if (VerifModeVariante(in)&&(tour==2))
		{
			tour=3;
			fond.image=SDL_LoadBMP("table.bmp");
			affiche_menu(fond,ecran);
			in.mousebuttons[SDL_BUTTON_LEFT]=0;
			
			
		}

		//SI ON CLIC SUR SCORE
		/* a venir */
		
		
		// si on est dans le mode jeux simple et il esxite des pions pour les deux jouers sur le plateau
		if(tour==3 && ( VerifPionsSurPlateau(joueurs[0]) || VerifPionsSurPlateau(joueurs[1]) || estPremierClic))
		{			
			estCoupValide = 0;
			//si l'utilisateur a cliqué sur le button droit de la souris
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

										// DANS LE CAS OU LE JOUEUR VEUT MANGER LE PION DE LADVERSAIRE
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

											SDL_BlitSurface(pion.image, NULL, ecran.image, &pion.position);
											SDL_BlitSurface(case_vide.image, NULL, ecran.image, &case_vide.position);
											SDL_Flip(ecran.image);
										}
										else
										{
											AppliqueCoup(case1, case2, joueurs[joueur].JoueurT);
										}

										//Afin d'eviter la redence du coup ce code va etre appliquer dans le cas ou on
										//manger adversaire ou dans le cas ou on va faire juste un mouvement orthogonal
										// c'est pour ca il est mis ici donc il sera appliquer qq soit le type de mouvement

										estCoupValide = 1;

										hg1=CaseToPointhg(case1);
										hg2=CaseToPointhg(case2);

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

														// ON CHANGE LE JOUEUR POUR SUPPRIMER LE NOUVEAU PION DE LADVERSAIRE
														Changer_joueur(&joueur);
														SupprimerPion(&case_vide,sprite, hgDelete, joueur);
														// ON REVIENT SUR LE JOUEUR INITIAL
														Changer_joueur(&joueur);

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
			SDL_Quit();		
		}
	}
	return EXIT_SUCCESS;
}
