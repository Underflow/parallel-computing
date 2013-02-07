#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Maximal size of the list
#define SIZE 100

//Struct of the list
// bd : taille de la liste
// bg : tache pointee

//Todo : Rajouter size à l'interieur de la struct
// Initialiser size dans init_list
typedef struct s_list *list;
struct s_list
{
    char *tasks[SIZE];
    int curr_pos;
};

//Initialise the list
void init_list(list l)
{
    l->curr_pos = -1;
    int i;
    for(i = 0; i < SIZE; i++)
        l->tasks[i] = NULL;
}

//Inserts data at the end of list l
int insert(int pos, char *data, list l)
{
    if(pos < SIZE - 1 && pos >= 0)
    {
        if(!l->tasks[pos])
        {
            l->tasks[pos] = data;
            return pos;
        }
    }
    return -1;
}

int get_free_pos(list l)
{
    int i = 0;
    while(i < SIZE && l->tasks[i])
    {
        i++;
    }
    if( i < SIZE)
        return i;
    else
        return -1;
}

//Returns the next element of the list
char *get_next_task(list l)
{
    do
    {
        l->curr_pos = (l->curr_pos + 1)%SIZE;
    }
    while(l->tasks[l->curr_pos] == NULL);
    return l->tasks[l->curr_pos];
}

//Deletes data of the list in placing an other task at his previous place
void delete_task(int pos, list l)
{
    if(pos < SIZE - 1 && pos >= 0)
        l->tasks[pos] = NULL;
}

//Replaces data with new_data in the list l
void replace(int pos, char* new_data, list l)
{ 
    if(pos < SIZE - 1 && pos >= 0)
        l->tasks[pos] = new_data;
}

int main()
{ 
    list l=malloc(sizeof(list));
    init_list(l);
    insert(get_free_pos(l), "Tache 1\n", l);
    int t = insert(get_free_pos(l), "Tache 2\n", l);
    insert(get_free_pos(l), "Tache 3\n", l);
    delete_task(t, l);
    int i;
    for (i = 0; i < 5; i++)
            printf("%s", get_next_task(l));
    return 0;
}
