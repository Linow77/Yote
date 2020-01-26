#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "table_score.h"
#include "affichage.h"

int main()
{
	int tour= 0, joueur=0, estCoupValide = 0, aMangerAdversaire = 0, estModeVariante = 0, estVSIA = 0, estGameOver = 0, permission= 0, estReserveAdiminuer=0, nbCoup=0,JoueurAd ;
	Point hgDelete;
	TableScore scores;

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
	/**Initialisation du fichier des scores **/
	init_table_score(&scores);
	alloc_table_score(&scores);
	get_scores(&scores);
	//joueurs_par_defaut(joueurs);

	/** CHARGEMENT DES IMAGES **/
	chargement(&sprite);

	//CHARGEMENT DES IMAGES & POSITIONS DES OBJETS
	chargement_objets(&fond, &ecran);

	//GESTION DES EVENEMENTS :
	memset(&in,0,sizeof(in));

	//On affiche le menu si la partie n'a pas commencée MENU 0
	affiche_menu(fond,ecran);


	Point c;

	do
	{
		c = clic();
		if (verif_menu1(c) &&(tour==0))
		{
			AfficheMenu(1,&tour,fond,ecran, joueurs);
		}

		// Si on clic sur 1 VS 1
		else if (verif_pvp(c) &&(tour==1))
		{
			AfficheMenu(2,&tour,fond,ecran, joueurs);
			joueurs_entrent_noms(estVSIA, joueurs);
			print_player(joueurs[0]);
			print_player(joueurs[1]);
			joueurs[0].score = get_score_by_name(&scores, joueurs[0].nom);
			joueurs[1].score = get_score_by_name(&scores, joueurs[1].nom);
		}

		// Si on clic sur 1 VS IA
		else if (verif_pvia(c) &&(tour==1))
		{
			estVSIA = 1;
			AfficheMenu(2,&tour,fond,ecran, joueurs);
			joueurs_entrent_noms(estVSIA, joueurs);
			joueurs[0].score = get_score_by_name(&scores, joueurs[0].nom);
			joueurs[1].score = get_score_by_name(&scores, joueurs[1].nom);
		}

        else if (verif_menu_score(c) && tour == 0)
		{
			AfficheScore(fond,ecran,&tour,&scores);
		}

        else if(verif_bouton_retour(c) && tour == 4)
		{
			fond.image=SDL_LoadBMP("menu_principal.bmp");
			affiche_menu(fond,ecran);
			tour=0;
		}

		else if (verif_mode_simple(c) &&(tour==2))
		{
			AfficheMenu(3,&tour,fond,ecran, joueurs);
			infoPartie(ecran, joueurs,sprite, 1);
		}	//Ici on met 1 au lieu de joueur car le premier affichage est un démon,
			// or l'affichage de infopartie se faisant après le tour joué, il faut prévoir
			//le début de la partie

		else if (verif_mode_variante(c) &&(tour==2))
		{
			estModeVariante = 1;
			AfficheMenu(3,&tour,fond,ecran, joueurs);
			infoPartie(ecran, joueurs,sprite, 1);
		}

		else if (verif_quitter(c) &&(tour==0))
		{
			free_table_score(&scores);
			SDL_Quit();
			return EXIT_SUCCESS;
		}

	} while (tour != 3);


	// tant que le jeu n'est pas fini
	while (!estGameOver)
	{
		estCoupValide = 0;
		JoueurAd = joueur_adv(joueur);

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
						if(VerifCoupValide(caseSelection, caseDeplacement, joueurs[joueur].JoueurT)) {
							permission =1;
							aMangerAdversaire = 1;
							Case caseASupprimer = DetermineCaseASupprimer(caseSelection, caseDeplacement);
							hgDelete=CaseToPointhg(caseASupprimer);

							JoueurAd=NbJoueurAdv(joueur);
							AppliqueCoupV2(caseSelection, caseASupprimer, caseDeplacement, &joueurs[joueur], &joueurs[JoueurAd] );

							SupprimerPion(&case_vide,sprite, hgDelete, joueur_adv(joueur));

							infoPartie(ecran, joueurs,sprite, joueur_adv(joueur));
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
						deplacer_pion(&estCoupValide, caseSelection, caseDeplacement,ecran, joueurs, sprite, &case_vide,&pion, &joueur, permission);
						permission =0;
						SDL_BlitSurface(case_vide.image, NULL, ecran.image, &case_vide.position);
						SDL_Flip(ecran.image);

						// prendre 2eme pion aux choix apres avoir manger le pion de ladversaire
						//si le nombre de piece sur le plateau du joueur adverse est > 0 dans la mode simple
						// oule nombre de piece sur dans le reseve du joueur adverse est > 0 dans la mode varinate
						if((!estModeVariante && aMangerAdversaire && joueurs[JoueurAd].piece_plateau > 0) ||
							(estModeVariante && aMangerAdversaire && (joueurs[JoueurAd].piece_reserve > 0 || joueurs[JoueurAd].piece_plateau > 0))) {

							estCoupValide = 0;
							do {

								//si on a mangé un pion, le deuxieme pion à manger est le premier pion DEMON
								// que l'on trouve dans le plateau
								if(estVSIA && tour_de_homme(joueurs, joueur))
								{
									if(joueurs[JoueurAd].piece_plateau > 0)
									{
										ia_pioche_pion(&caseSelection);

									} else if ( estModeVariante )
									{
										ia_pioche_pion_reserve(&joueurs[joueur],&joueurs[JoueurAd], &estReserveAdiminuer);
										estCoupValide = 1;
										infoPartie(ecran, joueurs,sprite, joueur);
									}
								}
								else {
									if(joueurs[JoueurAd].piece_plateau > 0)
									{
										caseSelection=PointToCase(clic());
									}
									else if (estModeVariante){
										ia_pioche_pion_reserve(&joueurs[joueur],&joueurs[JoueurAd], &estReserveAdiminuer);
										estCoupValide = 1;
										infoPartie(ecran, joueurs,sprite, joueur);
									}
								}

								// on vérifie que caseSelection est une case de l'adversaire et qu'elle n'est pas vide
								if(!estReserveAdiminuer && plateau[caseSelection.x][caseSelection.y] != VIDE
								&& plateau[caseSelection.x][caseSelection.y] != joueurs[joueur].JoueurT)
								{
									estCoupValide = 1;
									hgDelete=CaseToPointhg(caseSelection);

									JoueurAd=NbJoueurAdv(joueur);
									AppliqueCoupV3(caseSelection, &joueurs[joueur], &joueurs[JoueurAd]);

									SupprimerPion(&case_vide,sprite, hgDelete, joueur_adv(joueur));

									infoPartie(ecran, joueurs,sprite, joueur);
									SDL_BlitSurface(pion.image, NULL, ecran.image, &pion.position);
									SDL_BlitSurface(case_vide.image, NULL, ecran.image, &case_vide.position);
									SDL_Flip(ecran.image);
								}

								estReserveAdiminuer=0;
							} while(!estCoupValide);

						}
					}
				}
			} while(!estCoupValide);

		}

		if(estCoupValide)
		{
			if (joueurs[JoueurAd].piece_plateau ==2 && joueurs[joueur].piece_plateau==2 && joueurs[JoueurAd].piece_reserve==0&&
			 joueurs[joueur].piece_reserve==0) {
			  nbCoup++;
			  }

			JoueurAd = joueur;
			Changer_joueur(&joueur);




			// Pour le modeVariante le message game over s'affiche si le nombre de piece dans la reserve et dans le
			// plateau sont égales à 0
			// Pour le mode simple le message game over s'affiche si le nombre de piece dans de le plateau est égale
			// à 0

			if( (estModeVariante && joueurs[joueur].piece_plateau == 0 && joueurs[joueur].piece_reserve == 0) ||
				(!estModeVariante && joueurs[joueur].piece_plateau == 0 && aMangerAdversaire))
			{
				Changer_joueur(&joueur);
				joueurs[joueur].score++;
				insert(&scores, joueurs[joueur].score, joueurs[joueur].nom);
				save_score(&scores);
				afficheFinJeu(ecran, sprite, joueurs, joueur);

				estGameOver = 1;

			}
			else if(nbCoup>=10)
			{ estGameOver = 1;

				//TODO
				// afficher Partie nulle a la fin

				}
			aMangerAdversaire = 0;
		}

	}

	wait_quit();
	free_table_score(&scores);
	SDL_Quit();
	return EXIT_SUCCESS;
}


