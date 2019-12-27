#ifndef TABLE_SCORE
#define TABLE_SCORE



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/******************************************/
/*               CONSTANTES               */
/******************************************/

#define MAX_SCORE 5
#define MAX_SIZE  10
#define SCORE_FILE "score.txt"

#define D_TB 1
#define ALLOW_NAME_DUPLICATIONS 0
#define DEBUG printf("**%d**\n", __LINE__);
#define CLEAR system("clear");


/******************************************/
/*               STRUCTURES               */
/******************************************/

typedef struct TableScore
{
    char **players;// array of the players' names
    unsigned int number;// number of scores in the array
    unsigned int scores[MAX_SCORE];
} TableScore;


/******************************************/
/*        PROTOTYPES DES FONCTIONS        */
/******************************************/

void init_table_score(TableScore *table);
void alloc_table_score(TableScore *table);
void free_table_score(TableScore *table);

int save_score(TableScore *table_s);
int get_scores(TableScore *table_s);
void print_tablescore(TableScore *t);

unsigned int delete_by_name(TableScore *t, char *name);
unsigned int search_by_name(TableScore *t, char *name);
unsigned int get_score_by_name(TableScore *t, char *name);
void push(TableScore *t, unsigned int index, unsigned int s, char *n);
void shift(TableScore *t, unsigned int index);
void insert(TableScore *table, unsigned int p_score, char *name);
void set(TableScore *t, unsigned int index, unsigned int s, char *n);
void increase_size(TableScore *t);
void decrease_size(TableScore *t);

int min(int a, int b);

void test_insert(TableScore *t);

#endif

