
#include "affichage.h"



void chargement (Ressource *sprite)
{
	sprite->pion_d=SDL_LoadBMP("pion_demonv3.bmp");
	sprite->pion_h=SDL_LoadBMP("pion_hommev3.bmp");
	sprite->case_v=SDL_LoadBMP("cachev3.bmp");
	sprite->cache_info=SDL_LoadBMP("cache_info.bmp");
	sprite->ecran_de_fin=SDL_LoadBMP("ecrandefin.bmp");
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

/*
 * Laisse le joueur cliquer dans la fenêtre, et retourne les coordonnées
 * dans une variable de type Point
 */
Point clic()
{
	SDL_Event event;
	Point p;
	int pas_de_clic = 1;

	while (pas_de_clic)
	{
		SDL_WaitEvent(&event);

		if (event.type == SDL_MOUSEBUTTONUP)
		{
			p = (Point) { event.button.x, event.button.y };
			pas_de_clic = !pas_de_clic;
		}
		else if (event.type == SDL_QUIT)
		{
			SDL_Quit();
			exit(0);
		}
		else if (event.type == SDL_KEYDOWN)
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_Quit();
				exit(0);
			}
	}

	return p;
}

/*
 * Pas testé
 * Vérifie que l'utilisateur quitte le jeu
 */
void verif_quitter_jeu()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			SDL_Quit();
			exit(0);
		}
		else if (event.type == SDL_KEYDOWN)
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_Quit();
				exit(0);
			}
	}
}

/* Affiche un point dans le terminal */
void print_point(Point p)
{
	printf("x : %d | y : %d\n", p.x, p.y);
}


/*
 * En mode joueur contre joueur, les joueurs entrent leurs pseudos
 * Le joueur qui joue en premier est tiré au sort
 * En mode IA, le joueur entre son nom; il est le DEMON (convenu)
 * l'IA est donc l'HOMME
 * Le DEMON est à l'indice 0, l'HOMME l'indice 1
 */
void joueurs_entrent_noms(int ia_mode, Player joueurs[])
{
	int rst;
	const char *types[] = { "VIDE", "HOMME", "DEMON" };

	rst = rand();
	joueurs[0].JoueurT = DEMON;

	if (ia_mode)
	{
		puts("Joueur 1, entrez votre pseudo");
		joueurs[0].nom = entre_nom_dans_terminal();
		joueurs[1].nom = "IA";
	}
	else
	{
		if (rst % 2 == 0)
		{
			puts("Joueur 1, entrez votre pseudo");
			joueurs[0].nom = entre_nom_dans_terminal();
			puts("Joueur 2, entrez votre pseudo");
			joueurs[1].nom = entre_nom_dans_terminal();
		}
		else
		{
			puts("Joueur 1, entrez votre pseudo");
			joueurs[1].nom = entre_nom_dans_terminal();
			puts("Joueur 2, entrez votre pseudo");
			joueurs[0].nom = entre_nom_dans_terminal();
		}
		puts("Résultat du tirage au sort");
	}

	printf("Joueur %s : %s | Joueur %s : %s\n",
	joueurs[0].nom, types[joueurs[0].JoueurT],
	joueurs[1].nom, types[joueurs[1].JoueurT]);
	puts("Vous pouvez retourner dans l'interface graphique pour jouer c:");
}

/* Vérifie qu'un point est dans une zone rectangulaire de la fenêtre */
int verif_dans_rectangle(Point p, Point hg, Point bd)
{
	return p.x >= hg.x && p.y >= hg.y &&
		p.x <= bd.x && p.y <= bd.y;
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


/** Permet de vérifier si l’utilisateur a cliqué sur le bouton quitter dans le premier menu **/
int VerifQuitter(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONQUITTERX1)&&(in.mousex<BOUTTONQUITTERX2)&&(in.mousey>BOUTTONQUITTERY1)&&(in.mousey<BOUTTONQUITTERY2);
}

int verif_quitter(Point clic)
{
	Point hg = { BOUTTONQUITTERX1, BOUTTONQUITTERY1 };
	Point bd = { BOUTTONQUITTERX2, BOUTTONQUITTERY2 };
	return verif_dans_rectangle(clic, hg, bd);
}

/**  Permet de vérifier si l’utilisateur a cliqué sur le bouton jouer dans le premier menu  **/
int VerifMenu1(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONJOUERX1)&&(in.mousex<BOUTTONJOUERX2)&&(in.mousey>BOUTTONJOUERY1)&&(in.mousey<BOUTTONJOUERY2);
}

int verif_menu1(Point clic)
{
	Point hg = { BOUTTONJOUERX1, BOUTTONJOUERY1 };
	Point bd = { BOUTTONJOUERX2, BOUTTONJOUERY2 };
	return verif_dans_rectangle(clic, hg, bd);
}


/**  Permet de vérifier si l’utilisateur clique sur le bouton 1 VS 1 **/
int Verif1Vs1(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTON1V1X1)&&(in.mousex<BOUTTON1V1X2)&&(in.mousey>BOUTTON1V1Y1)&&(in.mousey<BOUTTON1V1Y2);
}

/* Verif1VS1 */
int verif_pvp(Point clic)
{
	Point hg = { BOUTTON1V1X1, BOUTTON1V1Y1 };
	Point bd = { BOUTTON1V1X2, BOUTTON1V1Y2 };
	return verif_dans_rectangle(clic, hg, bd);
}
/**  Permet de vérifier si l’utilisateur clique sur le bouton 1 VS IA **/
int Verif1VsIA(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTON1VSIAX1)&&(in.mousex<BOUTTON1VSIAX2)&&(in.mousey>BOUTTON1VSIAY1)&&(in.mousey<BOUTTON1VSIAY2);
}

/* Verif1VSIA */
int verif_pvia(Point clic)
{
	Point hg = { BOUTTON1VSIAX1, BOUTTON1VSIAY1 };
	Point bd = { BOUTTON1VSIAX2, BOUTTON1VSIAY2 };
	return verif_dans_rectangle(clic, hg, bd);
}

/**  Permet de vérifier si l’utilisateur clique sur le bouton Mode simple **/
int VerifModeSimple(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONSIMPLEX1)&&(in.mousex<BOUTTONSIMPLEX2)&&(in.mousey>BOUTTONSIMPLEY1)&&(in.mousey<BOUTTONSIMPLEY2);
}
int verif_mode_simple(Point clic)
{
	Point hg = { BOUTTONSIMPLEX1, BOUTTONSIMPLEY1 };
	Point bd = { BOUTTONSIMPLEX2, BOUTTONSIMPLEY2 };
	return verif_dans_rectangle(clic, hg, bd);
}




/**  Permet de vérifier si l’utilisateur clique sur le bouton Mode variante **/
int VerifModeVariante(Input in)
{
	return in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONVARIANTEX1)&&(in.mousex<BOUTTONVARIANTEX2)&&(in.mousey>BOUTTONVARIANTEY1)&&(in.mousey<BOUTTONVARIANTEY2);
}
int verif_mode_variante(Point clic)
{
	Point hg = { BOUTTONVARIANTEX1, BOUTTONVARIANTEY1 };
	Point bd = { BOUTTONVARIANTEX2, BOUTTONVARIANTEY2 };
	return verif_dans_rectangle(clic, hg, bd);
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

	SDL_Flip(ecran.image);
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
	char *pseudo_joueur1 = entre_nom_dans_terminal(); //LE PSEUDO EST DE 9 CARACTERE MAXIMUM
	char *pseudo_joueur2 = entre_nom_dans_terminal();
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

	SDL_Flip(ecran.image);
	TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(textevictoire);
	SDL_FreeSurface(textedefaite);
	SDL_FreeSurface(pseudovainqueur);
	SDL_FreeSurface(pseudoperdant);
	SDL_FreeSurface(scorevainqueur);
	SDL_FreeSurface(scoreperdant);
	free(pseudo_joueur1);
	free(pseudo_joueur1);
}


/*
 * Place un pion sur l'interface graphique et dans le plateau de jeu
 * Pas beau, TODO à enlever
 */
void placer_pion(int *estCoupValide, Case caseSelection, img ecran, img *pion,
				 Ressource sprite, int joueur, Player joueurs[])
{
	*estCoupValide = 1;
	Point hg1=CaseToPointhg(caseSelection);
	AfficherPion(ecran, pion, sprite, hg1, joueur);
	ChangerContenuCase(caseSelection, &joueurs[joueur]);
	infoPartie(ecran, joueurs,sprite);
	SDL_Flip(ecran.image);
}

/*
 * Pas beau, TODO à enlever
 */
void deplacer_pion(int *estCoupValide, Case caseSelection, Case caseDeplacement,
				   img ecran, Player joueurs[], Ressource sprite, img *case_vide,
				   img *pion, int *joueur)
{
	*estCoupValide = 1;

	Point hg1 = CaseToPointhg(caseSelection);
	Point hg2 = CaseToPointhg(caseDeplacement);

	infoPartie(ecran, joueurs, sprite);
	AfficherPion(ecran, pion, sprite, hg2, *joueur);
	SupprimerPion(case_vide, sprite, hg1, *joueur);
}

/* Retourne un Point là où le joueur a cliqué */
Point clic_souris(Input in)
{
	return (Point) { in.mousex, in.mousey };
}


/** Permet d'afficher le menu convenable selon le NbTour passer en parametre **/
void AfficheMenu(int nbTour, int *tour, img fond, img ecran)
{	if (nbTour==1)
	{	*tour=1;
		fond.image=SDL_LoadBMP("ChoixAdv.bmp");
	}

	if (nbTour==2)
	{
		*tour=2;
		fond.image=SDL_LoadBMP("menuChoix.bmp");
	}

	if (nbTour==3)
	{
		*tour=3;
		fond.image=SDL_LoadBMP("table.bmp");
	}

	affiche_menu(fond,ecran);
}

/** Permet de remet le compteur de clic à 0 pour pouvoir récuperer d'autres clic **/
void RenitiliserClic( Input *in)
{
	in->mousebuttons[SDL_BUTTON_LEFT]=0;
}

