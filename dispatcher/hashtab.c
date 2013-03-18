#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtab.h"

void add_new_link(struct hash_tab **h,double client_id,int task_id)
{
    struct hash_tab *new;
    
    HASH_FIND_INT(*h, &client_id, new);
    if(new==NULL)
    {
    new = malloc(sizeof(struct hash_tab));
    new->id=client_id;
    new->task_id=task_id;
    HASH_ADD_INT(*h,id,new);
    }
}

void delete_link(struct hash_tab **h,double client_id)
{
    struct hash_tab *current;
    HASH_FIND_INT(*h, &client_id, current);
    if(current!=NULL)
    {
        HASH_DEL(*h,current);
        free(current);
    }
}

int return_task_from_link(struct hash_tab **h,double client_id)
{
    struct hash_tab *searsch;

    HASH_FIND_INT(*h,&client_id,searsch);
    if(searsch != NULL)
        return searsch->task_id;
    return -1; // Dans la théorie il ne devrait jamais arriver ici
}

