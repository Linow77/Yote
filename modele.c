#include "modele.h"




/* Initialise les cases du plateau à VIDE */
void InitPlateau() {
	int i, j;

	for (i = 0; i != 6; i++) {
		for (j = 0; j != 5; j++) {
			plateau[i][j] = VIDE;
		}
	}
}




/*
 * Au début du jeu le 1er joueur est tiré au sort
 * Ne sert plus TODO à enlever
 */
void TireAuSortJoueur(Player joueurs[]) {
	if (rand() % 2) {
		joueurs[0].JoueurT = HOMME;
		joueurs[1].JoueurT = DEMON;
	}
	else {
		joueurs[0].JoueurT = DEMON;
		joueurs[1].JoueurT = HOMME;
	}
}

/* Initialise une variable joueur */
void Init_joueur(Player *player) {
	*player = (Player) { HOMME, 0, 12, 0, 0, NULL };
}

/* Initialise un tableau de joueurs */
void Init_joueurs(Player players[]) {
	Init_joueur(&(players[0]));
	Init_joueur(&(players[1]));
}


int MemeType(Case c, TypeContents type) {
	return plateau[c.y][c.x] == type;
}


void SetCase(Case *c, int x, int y)
{
	c->x = x;
	c->y = y;
}

// Renvoie le type de l'adversaire (DEMON ou HOMME)
TypeContents Adversaire(TypeContents joueur)
{
	if (joueur == DEMON) return HOMME;
	else return DEMON;
}

// Vérifie si un mouvement est égal à un autre
// Remplacé par VerifSurSesPas
int VerifMouvementsContraires(Move m1, Move m2)
{
	return EqlCase(m1.ancienne_position, m2.nouvelle_position) && EqlCase(m1.nouvelle_position, m2.ancienne_position);
}

// Vérifie qu'une case est égale à une autre
int EqlCase(Case c1, Case c2)
{
	return c1.x == c2.x && c1.y == c2.y;
}





/* Modifie une case en fonction des arguments x et y */
void set_case(Case *c, int x, int y)
{
	c->x = x;
	c->y = y;
}





/** Changement du joueur courant **/
void Changer_joueur(int *joueur)
{
	if(*joueur == 0)
		*joueur = 1;
	else
		*joueur = 0;
}

int joueur_adv(int joueur)
{
	if (joueur == 0) return 1;
	else return 0;
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

int a_encore_pieces_en_reserve(Player joueur)
{
	return joueur.piece_reserve > 0;
}

int a_encore_pieces_sur_plateau(Player joueur)
{
	return joueur.piece_plateau > 0;
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
		if(caseDepart.y < caseArrivee.y) {
			if(plateau[caseArrivee.x][caseArrivee.y - 1] != VIDE && plateau[caseArrivee.x][caseArrivee.y - 1] != type) {
				return 1;
			}
		}

		if(caseDepart.y > caseArrivee.y) {
			if(plateau[caseArrivee.x][caseArrivee.y + 1] != VIDE && plateau[caseArrivee.x][caseArrivee.y + 1] != type) {
				return 1;
			}
		}
	}

	// mouvement vertical **/
	if(caseDepart.y == caseArrivee.y) {
		if(caseDepart.x < caseArrivee.x) {
			if(plateau[caseArrivee.x -1][caseArrivee.y] != VIDE && plateau[caseArrivee.x -1][caseArrivee.y] != type) {
				return 1;
			}
		}

		if(caseDepart.x > caseArrivee.x) {
			if(plateau[caseArrivee.x +1][caseArrivee.y] != VIDE && plateau[caseArrivee.x +1][caseArrivee.y] != type) {
				return 1;
			}
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



/**
  returne un nombre aléatoire entre a et b
 */
int rand_a_b(int a, int b) {
	 static int first = 0;

	 if(first == 0) {
		 // pour générer des nombres alétoires différents à chaque nouvelle execution du programme
		 // le srand est executé une seule fois
		 srand(time (NULL));
		 first = 1;
	 }

	 return rand()%b + a;
 }




/*
 * Vérifie si un pion peut se déplacer
 * Il faut donc vérifier qu'au moins une case autour du pion
 * soit vide
 */
int pion_peut_se_deplacer(Case c)
{
	if (c.x > 0)
		if (VerifCaseVide((Case) { c.x - 1, c.y }))
			return 1;
	if (c.x < 6)
		if (VerifCaseVide((Case) { c.x + 1, c.y }))
			return 1;
	if (c.y > 0)
		if (VerifCaseVide((Case) { c.x, c.y - 1 }))
			return 1;
	if (c.y < 5)
		if (VerifCaseVide((Case) { c.x, c.y + 1 }))
			return 1;
	return 0;
}

/* Retourne l'adversaire du joueur */
TypeContents adv(TypeContents joueur)
{
	if (joueur == HOMME) return DEMON;
	else return HOMME;
}

/*
 * Vérifie qu'un pion peut en manger un autre
 * On suppose que la case n'est pas vide
 */
int pion_peut_manger(Case c, TypeContents joueur)
{
	TypeContents a = adv(joueur);

	if (c.x > 1)
		if (VerifCaseVide((Case) { c.x - 2, c.y }) &&
			plateau[c.x - 1][c.y] == a)
			return 1;
	if (c.x < 5)
		if (VerifCaseVide((Case) { c.x + 2, c.y }) &&
			plateau[c.x + 1][c.y] == a)
			return 1;
	if (c.y > 1)
		if (VerifCaseVide((Case) { c.x, c.y - 2 }) &&
			plateau[c.x][c.y - 1] == a)
			return 1;
	if (c.y < 4)
		if (VerifCaseVide((Case) { c.x, c.y + 2 }) &&
			plateau[c.x][c.y + 1] == a)
			return 1;
	return 0;
}


 /** Méthode qui permet de récuperer les coordonnées x y d'une case ou l'IA Peut se déplacer **/
Case RecupCaseArriveeIA (Case caseDepart)
{
	Case caseArriveeIA;
	caseArriveeIA.x = -1;
	caseArriveeIA.y = -1;
	int x = caseDepart.x;
	int y = caseDepart.y;

	// si la case sur notre gauche contient un demon et que la case à gauche du demon est vide alors
	// on peut déplacer le pion controlé par l'IA
	 if (x-2 >= 0 && plateau[x - 1][y] == DEMON && plateau[x - 2][y] == VIDE) {
		caseArriveeIA.x = x - 2;
		caseArriveeIA.y = y;

	// si la case en haut contient un demon et que la case en haut du demon est vide alors
	// on peut déplacer le pion controlé par l'IA vers le haut
	} else if (y-2 >= 0 && plateau[x][y-1] == DEMON && plateau[x][y - 2] == VIDE) {
		caseArriveeIA.x = x;
		caseArriveeIA.y = y - 2;

	// si la case sur notre droite contient un demon et que la case à droite du demon est vide alors
	// on peut déplacer le pion controlé par l'IA
	} else if (x+2 < 6 && plateau[x+1][y] == DEMON && plateau[x + 2][y] == VIDE) {
		caseArriveeIA.x = x + 2;
		caseArriveeIA.y = y;

	// si la case en bas contient un demon et que la case en bas du demon est vide alors
	// on peut déplacer le pion controlé par l'IA vers le bas
	} else if (y+2 < 4 && plateau[x][y+1] == DEMON && plateau[x][y + 2] == VIDE) {
		caseArriveeIA.x = x;
		caseArriveeIA.y = y + 2;

	// si la case à gauche est vide alors on peut déplacer le pion vers la gauche
	} else if(x-1 >= 0 && plateau[x-1][y] == VIDE ) {
		caseArriveeIA.x = x -1;
		caseArriveeIA.y = y;

	// si la case en haut est vide alors on peut déplacer le pion vers le haut
	} else if (y-1 >= 0 && plateau[x][y-1] == VIDE) {
		caseArriveeIA.x = x;
		caseArriveeIA.y = y - 1;

	// si la case à droite est vide alors on peut déplacer le pion vers la droite
	} else if (x+1 < 6 && plateau[x + 1][y] == VIDE) {
		caseArriveeIA.x = x + 1;
		caseArriveeIA.y = y;

	// si la case en bas est vide alors on peut déplacer le pion vers le bas
	} else if (y+1 < 4 && plateau[x][y+1] == VIDE) {
		caseArriveeIA.x = x;
		caseArriveeIA.y = y + 1;

	}

	return caseArriveeIA;
}

/* Methode qui permet de selectionner une case sur le plateau pour l'IA
 * Soit l'ia prend :
 *	- un pion, qui peut soit se déplacer soit manger (donc se déplacer)
 *	- une case au pif; si c'est un pion, on reprend les mêmes conditions plus
 *	haut, sinon c'est une case vide où il peut placer un pion */
Case RecupCaseDeSelectionIA (Player joueur) {
	Case caseSelectionIA;
	int i;
	int j;
	int stop = 0;
	int nombrePionHommePlateau = joueur.piece_plateau;

	// Si le nombre de pion sur le plateau est supérieur ou égale à 4
	// alors l'IA sélectionne un pion qui lui appartient pour le déplacer
	if (nombrePionHommePlateau >= 4) {
		for (i = 0; i < 6 && !stop; i++) {
			for (j = 0; j < 5 && !stop; j++) {
				if (plateau[i][j] == joueur.JoueurT) {
					set_case(&caseSelectionIA, i, j);

					if (pion_peut_se_deplacer(caseSelectionIA) ||
						pion_peut_manger(caseSelectionIA, joueur.JoueurT))
						stop = !stop;
				}
			}
		}

	}
	else
	{
		do
		{
			caseSelectionIA.x = rand_a_b(0, 5);
			caseSelectionIA.y = rand_a_b(0, 4);
		} while (!(pion_peut_se_deplacer(caseSelectionIA) ||
				 pion_peut_manger(caseSelectionIA, joueur.JoueurT) ||
				 (VerifCaseVide(caseSelectionIA) && joueur.piece_reserve > 0)));
	}

	return caseSelectionIA;
}



/* Vérifie qu'une case est dans le plateau */
int dans_le_plateau(Case c)
{
	return c.x != -1 && c.y != -1;
}


/* l'IA sélectionne pioche un pion de son adversaire (le premier pion qu'il
 * trouve) */
void ia_pioche_pion(Case *caseSelection)
{
	int i;
	int j;
	int found = 0;

	for (i = 0; i < 6 && !found; i++)
	{
		for (j = 0; j < 5 && !found; j++)
		{
			if (plateau[i][j] == DEMON)
			{
				set_case(caseSelection, i, j);
				found = 1;
			}
		}
	}
}


/*
 * Vérifie si le joueur courant est l'HOMME
 */
int tour_de_homme(Player joueurs[], int joueur)
{
	return joueurs[joueur].JoueurT == HOMME;
}

/* Retourne une chaîne de caractères entrée dans le terminal */
char *entre_nom_dans_terminal()
{
	char *str = (char *) malloc(sizeof(char) * TAILLE_MAX_NOM);
	//char *skip_line;

    /*
	do
	{
		//puts(" entrez votre nom : ");
		fgets(str, sizeof(str), stdin);
		skip_line = strchr(str, '\n');
		*skip_line = '\0';
	} while (strlen(str) >= TAILLE_MAX_NOM || str[0] == '\0');
    */
    scanf(" %s", str);

	return str;
}




/*
 * Donne un nom par défaut aux joueurs
 */
void joueurs_par_defaut(Player joueurs[])
{
	joueurs[0].nom = "Toto";
	joueurs[1].nom = "Tata";
}

/*
 * Affiche les champs d'un joueur : nom, score, nombre de pièces...
 */
void print_player(Player p)
{
	printf("Nom : %s\n", p.nom);
	printf("Score : %d\n", p.score);
	printf("Pièces en réserve : %d\n", p.piece_reserve);
	printf("Pièces capturées : %d\n", p.piece_cap);
	printf("Pièces sur le plateau : %d\n", p.piece_plateau);
}

