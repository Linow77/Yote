#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <time.h>
#include <SDL/SDL_ttf.h>
#include "affichage.h"


///FONCTIONS RICHARD
void chargement (Ressource *sprite)
{
	sprite->pion_d=SDL_LoadBMP("pion_demon.bmp");
	sprite->pion_h=SDL_LoadBMP("pion_homme.bmp");
}

Case PointToCase(Point clic)
{
	Case case1;
	
	if(145<clic.x && clic.x<855 && 150<clic.y && clic.y<740) //SUR LE PLATEAU
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
	p.x=case1.x*120 +146;
	p.y=case1.y*120 +151;
	
	return p;
}

// FONCTIONS IMANE
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


//MAIN
int main(int argc, char *argv[])
{
	int tour= 0;
	img fond,ecran,pion;
	Input in; //VARIABLE GESTION EVENEMENT
	Ressource sprite;
	
	
	/** CHARGEMENT DES IMAGES **/
	chargement(&sprite);
	
	//CHARGEMENT DES IMAGES & POSITIONS DES OBJETS 
	chargement_objets(&fond, &ecran);
	
	//GESTION DES EVENEMENTS :
	memset(&in,0,sizeof(in));
	
	//On affiche le menu si la partie n'a pas commencée MENU 0
	affiche_menu(fond,ecran);
	
	
	while((!in.key[SDLK_ESCAPE])&&(!in.quit)) //TANT QUE L'UTILISATEUR N'A PAS QUITTÉ
	{
		UpdateEvents(&in);
		
		
			
			
			//SI ON CLIC SUR UN BOUTON DU MENU
			
			//SI ON CLIC SUR JOUER MENU 1
			if (in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONJOUERX1)&&(in.mousex<BOUTTONJOUERX2)&&(in.mousey>BOUTTONJOUERY1)&&(in.mousey<BOUTTONJOUERY2)&&(tour==0))
			{
				tour=1;
				fond.image=SDL_LoadBMP("ChoixAdv.bmp");
				affiche_menu(fond,ecran);
				
				
				
				//On remet le compteur de clic à 0 pour pouvoir récuperer d'autres clic
				in.mousebuttons[SDL_BUTTON_LEFT]=0;
			}
				
				//1 VS 1
				if (in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTON1V1X1)&&(in.mousex<BOUTTON1V1X2)&&(in.mousey>BOUTTON1V1Y1)&&(in.mousey<BOUTTON1V1Y2)&&(tour==1))
				{
					tour=2;
					fond.image=SDL_LoadBMP("menuChoix.bmp");
					affiche_menu(fond,ecran);
					
					in.mousebuttons[SDL_BUTTON_LEFT]=0;
				}
				//1 VS IA
				if (in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTON1VSIAX1)&&(in.mousex<BOUTTON1VSIAX2)&&(in.mousey>BOUTTON1VSIAY1)&&(in.mousey<BOUTTON1VSIAY2)&&(tour==1))
				{
					tour=2;
					fond.image=SDL_LoadBMP("menuChoix.bmp");
					affiche_menu(fond,ecran);
					in.mousebuttons[SDL_BUTTON_LEFT]=0;
				}
				//si on choisit le mode simple
				if (in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONSIMPLEX1)&&(in.mousex<BOUTTONSIMPLEX2)&&(in.mousey>BOUTTONSIMPLEY1)&&(in.mousey<BOUTTONSIMPLEY2)&&(tour==2))
				{
					tour=3;
					fond.image=SDL_LoadBMP("table.bmp");
					affiche_menu(fond,ecran);
					in.mousebuttons[SDL_BUTTON_LEFT]=0;
					
					/** affiche le pion **/
					pion.image=sprite.pion_d;
					SDL_SetColorKey(pion.image,SDL_SRCCOLORKEY,SDL_MapRGB(pion.image->format,255, 0, 255));
					pion.position.x=145;
					pion.position.y=510;
					
	
					SDL_BlitSurface(sprite.pion_d, NULL, ecran.image, &pion.position);
					SDL_Flip(ecran.image);
				
					/** **/
					
					
					
				}
				//si on choisit le mode variante
				if (in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONVARIANTEX1)&&(in.mousex<BOUTTONVARIANTEX2)&&(in.mousey>BOUTTONVARIANTEY1)&&(in.mousey<BOUTTONVARIANTEY2)&&(tour==2))
				{
					tour=3;
					fond.image=SDL_LoadBMP("table.bmp");
					affiche_menu(fond,ecran);
					in.mousebuttons[SDL_BUTTON_LEFT]=0;
				}
			
			//SI ON CLIC SUR SCORE
			/* a venir */
			
			///test point 
					Point clic,hg;
					Case case1;
					if(tour==3 && in.mousebuttons[SDL_BUTTON_LEFT])
					{
						clic.x=in.mousex;
						clic.y=in.mousey;
						
						case1=PointToCase(clic);
						if(case1.x!=-1 && case1.y!=-1){
							hg=CaseToPointhg(case1);
							pion.position.x=hg.x;
							pion.position.y=hg.y;
							SDL_BlitSurface(sprite.pion_d, NULL, ecran.image, &pion.position);
							SDL_Flip(ecran.image);
						}
						
					}
					
			//SI ON CLIC SUR QUITTER
			if (in.mousebuttons[SDL_BUTTON_LEFT]&&(in.mousex>BOUTTONQUITTERX1)&&(in.mousex<BOUTTONQUITTERX2)&&(in.mousey>BOUTTONQUITTERY1)&&(in.mousey<BOUTTONQUITTERY2)&&(tour==0))
			{
				
				SDL_Quit();
			}
		}
	return EXIT_SUCCESS;
}
