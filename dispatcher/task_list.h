//Maximal size of the list
#define SIZE 100

typedef struct task_list *task_list;
struct task_list
{
    char *tasks[SIZE];
    int curr_pos;
};


void init_tlist(task_list l);
int insert_tlist(int pos, char *data, task_list l);
int free_pos_tlist(task_list l);
char *next_tlist(task_list l);
void delete_tlist(int pos, task_list l);
void replace_tlist(int pos, char* new_data, task_list l);
