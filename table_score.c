#include "table_score.h"


/*******************************************/
/*        DEFINITIONS DES FONCTIONS        */
/*******************************************/

void init_table_score(TableScore *table)
{
    table->players = NULL;
    table->number = 0;

    return;
}


void alloc_table_score(TableScore *table)
{
    int num;

    table->players = ((char **) malloc(sizeof(char *) * MAX_SCORE));

    for (num = 0; num != MAX_SCORE; num++)
    {
        table->players[num] = (char *) malloc(sizeof(char) * MAX_SIZE);
    }

    return;
}


int get_scores(TableScore *table_s)
{
    FILE* file = NULL;
    int num;

    file = fopen(SCORE_FILE, "r");
    if (file != NULL)
    {
        for (num = 0; !(feof(file)); num++)
        {
            // we get the name and the score of each player
            fscanf(file, "%s %d\n", table_s->players[num], &(table_s->scores[num]));
        }
        table_s->number = num;// number of players/number of lines of the file
        fclose(file);

        return 1;// success, we read the file
    }

    return 0;
}


void best_scores(TableScore *t)
{
    int r;// rank of the player

    getchar();// remove newline from scanf
    CLEAR

    puts("\n\tSCORES\n");
    puts("RANG\tJOUEUR\tPOINTS\n");
    for (r = 0; r != t->number; r++)
    {
        printf("%d\t%s\t%d\n", r + 1, t->players[r], t->scores[r]);
    }

    printf("\nAppuyez sur entrer pour revenir au menu");
    getchar();

    return;
}


int save_score(TableScore *table_s)
{
    FILE* file = NULL;
    int num;

    file = fopen(SCORE_FILE, "w");
    if (file != NULL)
    {
        for (num = 0; num != table_s->number; num++)
        {
            // we write the name and the score of the player
            fprintf(file, "%s %d\n", table_s->players[num], table_s->scores[num]);
        }
        fclose(file);
        return 1;// success, we read the file
    }

    return 0;
}


void input_score(TableScore *table, unsigned int p_score, char *nom)
{
    int num, num2;

    if (table->number != MAX_SCORE)
    {
        table->number++;
        table->scores[table->number - 1] = 0;// the value isn't initialized yet
    }

    // we iterate through the score table till we find a place for the player's
    // score; the table is crescently sorted
    for (num = 0; num != table->number && table->scores[num] > p_score; num++);

    // if we reached the end of the table, no insertion
    if (num == table->number) return;

    // we push the array, so that we can insert the player's score and name
    for (num2 = table->number - 1; num2 != num; num2--)
    {
        table->scores[num2] = table->scores[num2 - 1];
        strcpy(table->players[num2], table->players[num2 - 1]);
    }

    table->scores[num] =  p_score;// insertion
    table->players[num] = nom;// insertion

    return;
}

void input_player_name(TableScore *table, unsigned int rank)
{
    char name[MAX_BUFFER];// in case the user input is too much, we use a buffer
    char *skip_line;
    //int c;

    printf("Entrez votre pseudo : ");
    //getchar();// to remove the newline from the scanf

    do
    {
        fgets(name, sizeof(name), stdin);// we get the user input
        skip_line = strchr(name, '\n');// we remove the newline from the input
        *skip_line = '\0';
    } while (strlen(name) >= MAX_SIZE || name[0] == '\0');

    strcpy(table->players[rank], name);

    return;
}

