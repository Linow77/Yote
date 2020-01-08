#include "table_score.h"


/*******************************************/
/*        DEFINITIONS DES FONCTIONS        */
/*******************************************/

/* Initialize the structure
 * TODO : Merge with alloc_table_score() ? */
void init_table_score(TableScore *table)
{
    table->players = NULL;
    table->number = 0;

    return;
}

// Allocate memory for the table of scores
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

// Get the scores from a file (see filename in DEFINEs)
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

// Deletes the score of a player according to his name
// We loop through the scores, if the name matches one player,
// we get the score. Then the scores below are shifted to
// 'erase' the score. Finally the score deleted is returned.
unsigned int delete_by_name(TableScore *t, char *name)
{
    int index;
    unsigned int score = 0;

    index = search_by_name(t, name);

    if (index != -1)
    {
        score = t->scores[index];
        shift(t, index);
    }

    return score;
}

// Returns the score of a player, by name
// If the player doesn't exist, returns 0
unsigned int get_score_by_name(TableScore *t, char *name)
{
    int r = search_by_name(t, name);

    if (r == -1) return 0;
    else return t->scores[r];
}

/* Returns a score with a given name
 * If the score isn't found, -1 is returned */
unsigned int search_by_name(TableScore *t, char *name)
{
    int r;

    for (r = 0; r != t->number; r++)
    {
        if (strcmp(name, t->players[r]) == 0) return r;
    }

    return -1;
}


// Prints the scores into the terminal
// ranked from best to worse
void print_tablescore(TableScore *t)
{
    int r;// rank of the player

    puts("\n\tSCORES\n");
    puts("RANG\tJOUEUR\tPOINTS\n");
    for (r = 0; r != t->number; r++)
    {
        printf("%d\t%s\t%d\n", r + 1, t->players[r], t->scores[r]);
    }

    return;
}

// Save the scores in a file (see name of file in DEFINE's)
int save_score(TableScore *table_s)
{
    int num;
    FILE* file = NULL;

    /* If there are no scores */
    if (table_s->number == 0) return 0;

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

/*
 * Insert a score with a name
 * If the player has already a score, but is lower than p_score,
 * the player's score is replaced with p_score.
 * The score can be either 'inserted' or appended to the end
 * of the structure
 * */
void insert(TableScore *t, unsigned int p_score, char *name)
{
    int r;
    int old_score;
    int can_be_inserted = 0;

    if (!ALLOW_NAME_DUPLICATIONS)
    {
        old_score = delete_by_name(t, name);
        if (old_score > p_score) return;
    }

    // while the score is lower, we loop the scores
    for (r = 0; r != t->number && !can_be_inserted; r++)
    {
        can_be_inserted = (t->scores[r] < p_score);
    }

    if (can_be_inserted)// insert
    {
        r--;
        push(t, r, p_score, name);
    }
    else if (r < MAX_SCORE)// append
    {
        set(t, r, p_score, name);
        increase_size(t);
    }

}

/* Increase size of structure */
void increase_size(TableScore *t)
{
    if (t->number < MAX_SCORE) t->number++;
}

/* Decrease size of structure */
void decrease_size(TableScore *t)
{
    if (t->number > 0) t->number--;
}

/* Returns the minimum between a and b */
int min(int a, int b)
{
    if (a < b) return a;
    return b;
}

/* Push an array from a given index
 * [a, b, c, d, e]
 * push(2, x)
 * [a, b, x, c, d, e]
 * */
void push(TableScore *t, unsigned int index, unsigned int s, char *n)
{
    int i = min(t->number, MAX_SCORE - 1);

    for (; i != index; i--)
    {
        set(t, i, t->scores[i - 1], t->players[i - 1]);
    }

    set(t, i, s, n);
    increase_size(t);
}

/* Shift an array from a given index
 * [a, b, c, d, e]
 * shift(2)
 * [a, b, d, e]
 * */
void shift(TableScore *t, unsigned int index)
{
    int i;

    for (i = index; i != t->number - 1; i++)
    {
        set(t, i, t->scores[i + 1], t->players[i + 1]);
    }

    decrease_size(t);
}

void set(TableScore *t, unsigned int index, unsigned int s, char *n)
{
    t->scores[index] = s;
    strcpy(t->players[index], n);
}

// Free memory of the table of scores
// Still some memory leaks though @.@ ?
void free_table_score(TableScore *table)
{
    int num;

    for (num = 0; num != table->number; num++)
    {
        //free(table->players[num]);
    }

    free(table->players);
}

void test_insert(TableScore *t)
{
	insert(t, 23, "toto");
	insert(t, 53, "jesus");
	insert(t, 64, "luke");
	insert(t, 80, "link");
	insert(t, 9, "mario");
}

