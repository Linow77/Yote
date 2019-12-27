#include "affichage.h"
#include "table_score.h"



int main(int argc, char *argv[])
{
	int tour= 0, joueur=0, estPremierClic=1, estCoupValide = 0, aMangerAdversaire = 0, JoueurAd;
	int victoire=0;
	Point clic, hg1,hg2, hgDelete;
	Case case1, case2;
	Player joueurs[2];
	TTF_Font *police = NULL;
	img fond,ecran,pion, case_vide;
	Input in; //VARIABLE GESTION EVENEMENT
	Ressource sprite;

	// Tableau des scores
	TableScore scores;
	init_table_score(&scores);
	alloc_table_score(&scores);
	get_scores(&scores);
	test_insert(&scores);


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
    police = TTF_OpenFont("RuneicityDecorative001.ttf", 65);

	//GESTION DES EVENEMENTS :
	memset(&in,0,sizeof(in));

	//On affiche le menu si la partie n'a pas commencée MENU 0
	affiche_menu(fond,ecran);

	//AFFICHAGE FIN DE PARTIE
	/*	if(victoire==0)
		{
			afficheFinJeu(ecran,sprite,joueurs[0]);

		}
	*/


	while((!in.key[SDLK_ESCAPE]) && (!in.quit)) //TANT QUE L'UTILISATEUR N'A PAS QUITTÉ ou qu'il n'a pas gagné
	{
		UpdateEvents(&in);

		//SI ON CLIC SUR UN BOUTON DU MENU
		//affiche_coordonnees_clic(in);

		//SI ON CLIC SUR JOUER MENU 1
		if (VerifMenu1(in)&&(tour==0))
		{
			tour=1;
			fond.image=SDL_LoadBMP("ChoixAdv.bmp");
			affiche_menu(fond,ecran);

			//On remet le compteur de clic à 0 pour pouvoir récuperer d'autres clic
			in.mousebuttons[SDL_BUTTON_LEFT]=0;
		}
		if (VerifMenuScores(in) && tour == 0)
		{
			//puts("SCORES");
			affiche_menu(fond,ecran);
			//SDL_Flip(ecran.image);
			//affiche_scores(police, fond, &scores);
			fond.image=SDL_LoadBMP("scores_bg.jpg");
			affiche_menu(fond,ecran);
			in.mousebuttons[SDL_BUTTON_LEFT]=0;
			puts("Scores");
		}

		//SI ON CLIC SUR UN BOUTON DU MENU

		//SI ON CLIC SUR JOUER MENU 1
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
						AfficherPion(ecran,&pion, sprite, hg1, joueur);

						ChangerContenuCase(case1, &joueurs[joueur]);

						infoPartie(ecran, joueurs,sprite);

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
										AfficherPion(ecran,&pion, sprite, hg2, joueur);
										SupprimerPion(&case_vide,sprite, hg1, joueur);

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
			//TTF_CloseFont(police);// Erreur de segmentation
			//TTF_Quit();
			SDL_Quit();
		}
	}

	save_score(&scores);
	free_table_score(&scores);

	return EXIT_SUCCESS;
}
