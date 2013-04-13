//Maximal size of the list
#define SIZE 100

typedef struct s_task *task;
struct s_task
{
    char *task;
    int id;
};

typedef struct task_list *task_list;
struct task_list
{
    int size;
    task *tasks;
    int curr_task;
    int curr_pos;
};


void init_tlist(task_list l, int size);
int insert_tlist(int pos, task tsk, task_list l);
int free_pos_tlist(task_list l);
task next_tlist(task_list l);
void delete_tlist(int pos, task_list l);
void replace_tlist(int pos, task tsk, task_list l);
