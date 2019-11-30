#ifndef TABLE_SCORE
#define TABLE_SCORE



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/******************************************/
/*               CONSTANTES               */
/******************************************/

#define MAX_SCORE 5
#define SCORE_FILE "score.txt"

#define DEBUG printf("**%d**\n", __LINE__);
#define CLEAR system("clear");


/******************************************/
/*               STRUCTURES               */
/******************************************/

typedef struct TableScore
{
    char **players;
    unsigned int number;
    unsigned int scores[MAX_SCORE];
} TableScore;


/******************************************/
/*        PROTOTYPES DES FONCTIONS        */
/******************************************/

void init_table_score(TableScore *table);
void alloc_table_score(TableScore *table);

int get_scores(TableScore *table_s);
void best_scores(TableScore *t);// pas besoin
int save_score(TableScore *table_s);

void input_score(TableScore *table, unsigned int p_score, char *nom);
void input_player_name(TableScore *table, unsigned int rank);// pas besoin

#endif

