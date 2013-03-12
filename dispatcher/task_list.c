#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task_list.h"

//Initialise the list
void init_tlist(task_list l, int size)
{
    l->size = size;
    l->tasks = malloc(size * sizeof(struct s_task));
    l->curr_pos = -1;
    int i;
    for(i = 0; i < l->size; i++)
        l->tasks[i] = NULL;
}

//Inserts data at the end of list l
int insert_tlist(int pos, task tsk, task_list l)
{
    if(pos < l->size && pos >= 0)
    {
        if(!l->tasks[pos])
        {
            l->tasks[pos] = tsk;
            return pos;
        }
    }
    return -1;
}

int free_pos_tlist(task_list l)
{
    int i = 0;
    while(i < l->size && l->tasks[i])
    {
        i++;
    }
    if( i < l->size)
        return i;
    else
        return -1;
}

//Returns the next element of the list
task next_tlist(task_list l)
{
    do
    {
        l->curr_pos = (l->curr_pos + 1)%(l->size);
    }
    while(l->tasks[l->curr_pos] == NULL);
    return l->tasks[l->curr_pos];
}

//Deletes data of the list in placing an other task at his previous place
void delete_tlist(int pos, task_list l)
{
    if(pos < l->size && pos >= 0)
        l->tasks[pos] = NULL;
}

//Replaces data with new_data in the list l
void replace_tlist(int pos, task tsk, task_list l)
{
    if(pos < l->size && pos >= 0)
        l->tasks[pos] = tsk;
}
