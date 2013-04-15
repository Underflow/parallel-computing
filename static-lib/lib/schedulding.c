#include <stdlib.h>
#include <stdio.h>
#include "task_list.h"
#define _BSD_SOURCE
#include <unistd.h>
#include <string.h>

typedef char*(*fintptr)(int);

extern void* tsk_gen_ptr;

task generate_task(int id)
{
    task t = malloc(sizeof(struct s_task));
    fintptr gen_tsk_fun = (fintptr)tsk_gen_ptr;
    char* str = gen_tsk_fun(id);
    printf("Task : %s\n", str);
    printf("Generate task %d\n", id);

    t->id = id;
    t->task = str;
    return t;
}

void free_task(task t)
{
    if(t)
    {
        free(t->task);
        free(t);
    }
}

void free_tlist(task_list l)
{
    while(l->size>0)
    {
        free_task(l->tasks[--l->size]);
    }
    free(l->tasks);
    free(l);
}

task_list init_tasks(int size, int start)
{
    task_list tlist = malloc(sizeof(struct task_list));
    init_tlist(tlist, size);

    for(int i = start; i < start + size; i++)
    {
        insert_tlist(i, generate_task(i), tlist);
    }
    tlist->curr_task = start + size - 1;
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
