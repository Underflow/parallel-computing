#include <stdlib.h>
#include <stdio.h>
#include "task_list.h"

task generate_task(int id)
{
    task t = malloc(sizeof(struct s_task));
    char* str = calloc(0, 30);
    sprintf(str, "Tache %d", id);
    t->id = id;
    t->task = str;
    return t;
}

void free_task(task t)
{
    free(t->task);
    free(t);
}

task_list init_tasks(int size, int start)
{
    task_list tlist = malloc(sizeof(struct task_list));
    init_tlist(tlist, size);
    
    for(int i = start; i < start + size; i++)
    {
        insert_tlist(i, generate_task(i), tlist);
    }
    tlist->curr_task = start;
    return tlist;
}

void end_task(int id, task_list tlist)
{
    int i = 0;
    while(i < tlist->size && tlist->tasks[i]->id != id)
    {
        i++;
    }
    if(i < tlist->size)
    {
        free_task(tlist->tasks[i]);
        replace_tlist(i, generate_task(++tlist->curr_task), tlist);
    }
}
