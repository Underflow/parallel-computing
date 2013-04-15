task generate_task(int id);
void free_task(task t);
void free_tlist(task_list l);
task_list init_tasks(int size, int start);
void end_task(int id, task_list tlist);
