#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "table_score.h"
#include "affichage.h"

int main()
{
	int tour= 0, joueur=0, estCoupValide = 0, aMangerAdversaire = 0, estModeVariante = 0, estVSIA = 0, estGameOver = 0, JoueurAd;
	Point hgDelete;

	Case caseSelection, caseDeplacement;
	Player joueurs[2];
	img fond,ecran,pion, case_vide;
	Input in; //VARIABLE GESTION EVENEMENT
	Ressource sprite;
	srand(time(NULL));

	/** INITIALISATION DU PLATEAU **/
	InitPlateau();
	/** INITIALISATION DES JOUEURS **/
	Init_joueurs(joueurs);
	//TireAuSortJoueur(joueurs);
	//affiche_type_joueur(joueurs[0].JoueurT);
	//affiche_type_joueur(joueurs[1].JoueurT);
	/** CHARGEMENT DES IMAGES **/
	chargement(&sprite);

	//CHARGEMENT DES IMAGES & POSITIONS DES OBJETS
	chargement_objets(&fond, &ecran);

	//GESTION DES EVENEMENTS :
	memset(&in,0,sizeof(in));

	//On affiche le menu si la partie n'a pas commencée MENU 0
	affiche_menu(fond,ecran);
/*
	Point p = clic();
	print_point(p);
	Point p2 = clic();
	print_point(p2);
	Point p3 = clic();
	print_point(p3);
	if (verif_dans_rectangle(p, p2, p3))
		printf("Dans rectangle\n");
	SDL_Event event;
	while (event.type != SDL_QUIT)
	{
		SDL_WaitEvent(&event);
	}
	SDL_Quit();

	return 0;
	*/

	//AFFICHAGE FIN DE PARTIE
	/*
	int victoire = 0;
    if(victoire==0)
	{
		afficheFinJeu(ecran,sprite,joueurs[0]);
	}
	*/

	Point c;

	do
	{
		c = clic();
		if (verif_menu1(c) &&(tour==0))
		{
			AfficheMenu(1,&tour,fond,ecran);
		}

		// Si on clic sur 1 VS 1
		else if (verif_pvp(c) &&(tour==1))
		{
			AfficheMenu(2,&tour,fond,ecran);
		}

		// Si on clic sur 1 VS IA
		else if (verif_pvia(c) &&(tour==1))
		{
			estVSIA = 1;
			AfficheMenu(2,&tour,fond,ecran);
		}

		else if (verif_mode_simple(c) &&(tour==2))
		{
			AfficheMenu(3,&tour,fond,ecran);
			infoPartie(ecran, joueurs,sprite);
		}

		else if (verif_mode_variante(c) &&(tour==2))
		{
			estModeVariante = 1;
			AfficheMenu(3,&tour,fond,ecran);
			infoPartie(ecran, joueurs,sprite);
		}

		else if (verif_quitter(c) &&(tour==0))
		{
			SDL_Quit();
		}

		printf("%d\n", tour);
	} while (tour != 3);

	/*
	int rst = rand();
	joueurs[0].JoueurT = DEMON;
	if (estVSIA)
	{
		puts("Joueur 1, entrez votre pseudo");
		joueurs[0].nom = "IA";
		joueurs[1].nom = entre_nom_dans_terminal();
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
	printf("Joueur %s : %s | Joueur %s : %s\n", joueurs[0].nom, types[joueurs[0].JoueurT], joueurs[1].nom, types[joueurs[1].JoueurT]);
	puts("Vous pouvez retourner dans l'interface graphique pour jouer c:");
	*/

	joueurs_entrent_noms(estVSIA, joueurs);
	//SI ON CLIC SUR SCORE (a faire)

	// tant que le jeu n'est pas fini
	while (tour == 3 && !estGameOver)
	{
		estCoupValide = 0;

		// s'il s'agit du joueur HOMME contrôlé par l'IA
		if(estVSIA && tour_de_homme(joueurs, joueur))
		{
			caseSelection = RecupCaseDeSelectionIA(joueurs[joueur]);
		}
		else
		{
			do
			{
				caseSelection = PointToCase(clic());
			} while (!dans_le_plateau(caseSelection));
		}

		//si la case de selection est vide on vérifie qu'il dispose d'une reserve de pièce suffisante
		if(VerifCaseVide(caseSelection) && joueurs[joueur].piece_reserve > 0)
		{
			placer_pion(&estCoupValide, caseSelection, ecran, &pion, sprite, joueur, joueurs);}

		//si la case de sélection contient un pion qui appartient au joueur
		else if(VerifMemeType(caseSelection, joueurs[joueur]))
		{

			do {
				estCoupValide = 0;// faux

				//si L'utilisateur clique sur la case d'arrivée ou s'il s'agit du joueur HOMME contrôlé par l'IA
				if (estVSIA && tour_de_homme(joueurs, joueur))
				{
					caseDeplacement = RecupCaseArriveeIA(caseSelection);
				}
				else
				{
					caseDeplacement = PointToCase(clic());
				}

				//si la case destination est dans le plateau
				if(dans_le_plateau(caseDeplacement))
				{

					//si la case distation est vide et il s'agit d'un mouvement orthogonal ou le joueur va manger un pion adversaire
					if(VerifCaseVide(caseDeplacement) && (VerifDeplacementOrthogonal(caseSelection,caseDeplacement)
						|| VerifCoupValide(caseSelection, caseDeplacement, joueurs[joueur].JoueurT)))
					{
						// DANS LE CAS OU LE JOUEUR VEUT MANGER LE PION DE L'ADVERSAIRE
						if(VerifCoupValide(caseSelection, caseDeplacement, joueurs[joueur].JoueurT))
						{
							aMangerAdversaire = 1;
							Case caseASupprimer = DetermineCaseASupprimer(caseSelection, caseDeplacement);
							hgDelete=CaseToPointhg(caseASupprimer);

							JoueurAd=NbJoueurAdv(joueur);
							AppliqueCoupV2(caseSelection, caseASupprimer, caseDeplacement, &joueurs[joueur], &joueurs[JoueurAd] );

							// ON CHANGE LE JOUEUR POUR SUPPRIMER LE PION DE LADVERSAIRE
							SupprimerPion(&case_vide,sprite, hgDelete, joueur_adv(joueur));

							// ON REVIENT SUR LE JOUEUR INITIAL
							infoPartie(ecran, joueurs,sprite);
							SDL_BlitSurface(pion.image, NULL, ecran.image, &pion.position);
							SDL_BlitSurface(case_vide.image, NULL, ecran.image, &case_vide.position);
							SDL_Flip(ecran.image);
						}
						else
						{
							AppliqueCoup(caseSelection, caseDeplacement, joueurs[joueur].JoueurT);}

						//deplacement du pion sera appliquer qq soit le type de mouvementdans
						//(manger adversaire ou faire un mouvement orthogonal)

						// fonction pas bien
						deplacer_pion(&estCoupValide, caseSelection, caseDeplacement,ecran, joueurs, sprite, &case_vide,&pion, &joueur);
						SDL_BlitSurface(case_vide.image, NULL, ecran.image, &case_vide.position);
						SDL_Flip(ecran.image);

						// prendre 2eme pion aux choix apres avoir manger le pion de ladversaire
						//si le nombre de piece sur le plateau du joueur adverse est > 0 dans la mode simple
						// oule nombre de piece sur dans le reseve du joueur adverse est > 0 dans la mode varinate
						if((!estModeVariante && aMangerAdversaire && joueurs[JoueurAd].piece_plateau > 0) ||
						(estModeVariante && aMangerAdversaire && joueurs[JoueurAd].piece_reserve > 0))
						{

							estCoupValide = 0;
							do {

								//si on a mangé un pion, le deuxieme pion à manger est le premier pion DEMON
								// que l'on trouve dans le plateau
								if(estVSIA && tour_de_homme(joueurs, joueur))
								{
									ia_pioche_pion(&caseSelection);
								}
								else
								{
									caseSelection=PointToCase(clic());
								}

								// on vérifie que caseSelection s'agit d'une case de l'adversaire et qu'elle n'est pas vide
								if(plateau[caseSelection.x][caseSelection.y] != VIDE
								&& plateau[caseSelection.x][caseSelection.y] != joueurs[joueur].JoueurT)
								{
									estCoupValide = 1;
									hgDelete=CaseToPointhg(caseSelection);

									JoueurAd=NbJoueurAdv(joueur);
									AppliqueCoupV3(caseSelection, &joueurs[joueur], &joueurs[JoueurAd]);

									// ON CHANGE LE JOUEUR POUR SUPPRIMER LE NOUVEAU PION DE L'ADVERSAIRE
									SupprimerPion(&case_vide,sprite, hgDelete, joueur_adv(joueur));

									// ON REVIENT SUR LE JOUEUR INITIAL
									infoPartie(ecran, joueurs,sprite);
									SDL_BlitSurface(pion.image, NULL, ecran.image, &pion.position);
									SDL_BlitSurface(case_vide.image, NULL, ecran.image, &case_vide.position);
									SDL_Flip(ecran.image);
								}

							} while(!estCoupValide && (!in.key[SDLK_ESCAPE]) && (!in.quit));

						}
					}
				}
			} while(!estCoupValide); //&& (!in.key[SDLK_ESCAPE]) && (!in.quit));

		}

		if(estCoupValide)
		{
			Changer_joueur(&joueur);
			// Pour le modeVariante le message game over s'affiche si le nombre de piece dans la reserve et dans le
			// plateau sont égales à 0
			// Pour le mode simple le message game over s'affiche si le nombre de piece dans de le plateau est égale
			// à 0
			if( (estModeVariante && joueurs[joueur].piece_plateau == 0 && joueurs[joueur].piece_reserve == 0) ||
				(!estModeVariante && joueurs[joueur].piece_plateau == 0 && aMangerAdversaire)) {

				// ici afficher le message de game over à l'écran
				printf("Game over\n");
				estGameOver = 1;

			}
			aMangerAdversaire = 0;
		}

	}

	SDL_Quit();

	return EXIT_SUCCESS;
}


		/*

		*/
