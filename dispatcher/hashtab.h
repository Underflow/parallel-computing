#include "uthash.h"

struct hash_tab{
    double id;
    int task_id;
    UT_hash_handle hh;
};

void add_new_link(struct hash_tab **h,double client_id,int task_id);
void delete_link(struct hash_tab **h,double client_id);
int return_task_from_link(struct hash_tab **h,double client_id);
