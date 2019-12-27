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
	get_scores(&scores);

	insert(&scores, 23, "toto");
	print_tablescore(&scores);// affichage dans le terminal
	insert(&scores, 53, "jesus");
	insert(&scores, 64, "luke");
	insert(&scores, 80, "link");
	insert(&scores, 9, "mario");
	print_tablescore(&scores);// affichage dans le terminal
	insert(&scores, 44, "toto");
	print_tablescore(&scores);// affichage dans le terminal
    printf("Score of %s : %d\n", "jesus", get_score_by_name(&scores, "jesus"));
	// sauvegarde des scores dans le fichier score.txt
	save_score(&scores);
	free_table_score(&scores);

    return 0;
}

