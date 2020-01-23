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

	//AFFICHAGE FIN DE PARTIE
	/*	if(victoire==0)
		{
			afficheFinJeu(ecran,sprite,joueurs[0]);

		}
	*/
	
	//TANT QUE L'UTILISATEUR N'A PAS QUITTÉ ou qu'il n'a pas gagné
	while((!in.key[SDLK_ESCAPE]) && (!in.quit)) 
	{
		UpdateEvents(&in);
		
		// Si on clic sur bouton jouer du menu 0
		if (VerifMenu1(in)&&(tour==0))
		{	
			AfficheMenu(1,&tour,fond,ecran);
			RenitiliserClic(&in);
		}		 
		
		// Si on clic sur 1 VS 1
		if (Verif1Vs1(in)&&(tour==1))
		{	AfficheMenu(2,&tour,fond,ecran);
			RenitiliserClic(&in);
		}
		
		// Si on clic sur 1 VS IA
		if (Verif1VsIA(in)&&(tour==1))
		{	// On met à 1 estVSIA
			estVSIA = 1;
			AfficheMenu(2,&tour,fond,ecran);
			RenitiliserClic(&in);
		}

		//si on choisit le mode simple
		if (VerifModeSimple(in)&&(tour==2))
		{	AfficheMenu(3,&tour,fond,ecran);
			infoPartie(ecran, joueurs,sprite);
			RenitiliserClic(&in);
		}

		//si on choisit le mode variante
		if (VerifModeVariante(in)&&(tour==2))
		{  // On met à 1 estModeVariante
			estModeVariante = 1;
			AfficheMenu(3,&tour,fond,ecran);
			infoPartie(ecran, joueurs,sprite);
			RenitiliserClic(&in);
		}

		//SI ON CLIC SUR SCORE (a faire) 

		// tantque le jeu n'est pas fini
		if (tour == 3 && !estGameOver)
		{	estCoupValide = 0;
			
			//si l'utilisateur a cliqué sur le button gauche de la souris ou s'il s'agit du joueur HOMME contrôlé par l'IA
			if(in.mousebuttons[SDL_BUTTON_LEFT] || (estVSIA && tour_de_homme(joueurs, joueur)))
			{	RenitiliserClic(&in);
				
				// s'il s'agit du joueur HOMME contrôlé par l'IA
				if(estVSIA && tour_de_homme(joueurs, joueur)) 
				{	
					caseSelection = RecupCaseDeSelectionIA(joueurs[joueur]);
				}
				else
				{	do
					{caseSelection = PointToCase(clic_souris(in));
					} while (!dans_le_plateau(caseSelection));
				}

				//si la case de selection est vide on vérifie qu'il dispose d'une reserve de pièce suffisante
				if(VerifCaseVide(caseSelection) && joueurs[joueur].piece_reserve > 0)
				{	placer_pion(&estCoupValide, caseSelection, ecran, &pion, sprite, joueur, joueurs);}
				
				//si la case de sélection contient un pion qui appartient au joueur
				else if(VerifMemeType(caseSelection, joueurs[joueur]))
				{	RenitiliserClic(&in);
					UpdateEvents(&in);
					
					do {	estCoupValide = 0;// faux
							UpdateEvents(&in);

						//si L'utilisateur clique sur la case d'arrivée ou s'il s'agit du joueur HOMME contrôlé par l'IA
						if(in.mousebuttons[SDL_BUTTON_LEFT] || (estVSIA && tour_de_homme(joueurs, joueur)))
						{	if (estVSIA && tour_de_homme(joueurs, joueur))
								{caseDeplacement = RecupCaseArriveeIA(caseSelection);}
							else
								{caseDeplacement = PointToCase(clic_souris(in));}
						
							//si la case destination est dans le plateau
							if(dans_le_plateau(caseDeplacement))
							{	RenitiliserClic(&in);
								
								//si la case distation est vide et il s'agit d'un mouvement orthogonal ou le joueur va manger un pion adversaire
								if(VerifCaseVide(caseDeplacement) && (VerifDeplacementOrthogonal(caseSelection,caseDeplacement)
									|| VerifCoupValide(caseSelection, caseDeplacement, joueurs[joueur].JoueurT)))
								{	
									// DANS LE CAS OU LE JOUEUR VEUT MANGER LE PION DE L'ADVERSAIRE
									if(VerifCoupValide(caseSelection, caseDeplacement, joueurs[joueur].JoueurT))
									{	aMangerAdversaire = 1;
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
									{	AppliqueCoup(caseSelection, caseDeplacement, joueurs[joueur].JoueurT);}

									//deplacement du pion sera appliquer qq soit le type de mouvementdans 
									//(manger adversaire ou faire un mouvement orthogonal)
									 
									deplacer_pion(&estCoupValide, caseSelection, caseDeplacement,ecran, joueurs, sprite, &case_vide,&pion, &joueur);
									SDL_BlitSurface(case_vide.image, NULL, ecran.image, &case_vide.position);
									SDL_Flip(ecran.image);

									// prendre 2eme pion aux choix apres avoir manger le pion de ladversaire
									//si le nombre de piece sur le plateau du joueur adverse est > 0 dans la mode simple
									// oule nombre de piece sur dans le reseve du joueur adverse est > 0 dans la mode varinate
									if((!estModeVariante && aMangerAdversaire && joueurs[JoueurAd].piece_plateau > 0) ||
									(estModeVariante && aMangerAdversaire && joueurs[JoueurAd].piece_reserve > 0))
									{
										RenitiliserClic(&in);

										estCoupValide = 0;
										do {
											UpdateEvents(&in);

											if (in.mousebuttons[SDL_BUTTON_LEFT] || (estVSIA && tour_de_homme(joueurs, joueur)))
											{
												//si on a mangé un pion, le deuxieme pion à manger est le premier pion DEMON
												// que l'on trouve dans le plateau
												if(estVSIA && tour_de_homme(joueurs, joueur)) 
												{
													ia_pioche_pion(&caseSelection);
												} 
												else 
												{
													caseSelection=PointToCase(clic_souris(in));
													RenitiliserClic(&in);
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
											}

										} while(!estCoupValide && (!in.key[SDLK_ESCAPE]) && (!in.quit));

									}
								}
							}
						}
					} while(!estCoupValide && (!in.key[SDLK_ESCAPE]) && (!in.quit));

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
		}

		//SI ON CLIC SUR QUITTER
		if (VerifQuitter(in) &&(tour==0))
		{
			SDL_Quit();
		}
	}

	return EXIT_SUCCESS;
}

