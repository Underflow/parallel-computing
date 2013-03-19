#include <stdlib.h>
#include <stdio.h>
#include "task_list.h"
#define _BSD_SOURCE
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "brute_force.h"


/*
struct { int freq; int len; unsigned long delay; } freqs[] = {
#include "notes.def"
};
*/

task generate_task(int id)
{
    task t = malloc(sizeof(struct s_task));
    char* str = malloc(1024);
    //static int note = 0;
    char* plg = generate_new_plg(300000);
    strcpy(str,"./application/bruteforce ");
    strcat(str, plg);
    //printf("%s\n",str);
    printf("Generate task %d\n", id);
    /*sprintf(str,
            //"usleep $(( $((%lu - `date +%%s`))  ));"
            //"echo `date +%%s` -- %u;"
            "echo '\x1b[10;%d]\x1B[11;%d]\a' >> /dev/null;"
            "echo BEEP;"
            "eject -T &",
            //wait[note] + start * 1000UL,
            freqs[note].freq,
            freqs[note].len);
    note = (note + 1) % (sizeof (freqs) / sizeof (freqs[0]));*/

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
    init_bf(8,"TEST");
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
