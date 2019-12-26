#include <stdio.h>
#include <stdlib.h>
#include "table_score.h"

// Main

int main()
{
	TableScore scores;
	init_table_score(&scores);
	alloc_table_score(&scores);
	// lecture des scores depuis un fichier score.txt
	// ! ne pas créer le fichier score.txt, il se crée tout seul !
	//get_scores(&scores);

	insert(&scores, 13, "toto");
	print_tablescore(&scores);// affichage dans le terminal
	insert(&scores, 33, "jesus");
	insert(&scores, 64, "luke");
	insert(&scores, 30, "link");
	insert(&scores, 3, "mario");
	insert(&scores, 4, "obiwan");
	print_tablescore(&scores);// affichage dans le terminal
	delete_by_name(&scores, "jesus");
	print_tablescore(&scores);// affichage dans le terminal
	// sauvegarde des scores dans le fichier score.txt
	//save_score(&scores);
	free_table_score(&scores);

    return 0;
}

