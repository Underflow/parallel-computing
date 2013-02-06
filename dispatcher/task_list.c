#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Maximal size of the list
const unsigned int SIZE = 100;

//Struct of the list
typedef struct s_list *list;
struct s_list
{
	char *tasks[SIZE];
	int bg, bd;
};

//Initialise the list
void init_list(list l)
{
	l->bg = l->bd = 0;
}

//Inserts data at the end of list l
void insert(char *data, list l)
{
	if(l->bd < SIZE)
	{
		l->tasks[l->bd++] = data;
	}
}

//Returns the next element of the list
char *get_next_task(list l)
{
	if (l->bd == 0)
		return NULL;
	l->bg++;
	l->bg %= l->bd;
	return l->tasks[l->bg];
}

//Deletes data of the list in placing an other task at his previous place
void delete(char *data, list l)
{
	int i;
	for (i = 0; i < l->bd && (strcmp(l->tasks[i], data) != 0); i++)
		;
	if (i != l->bd)
	{
		l->tasks[i] = l->tasks[l->bd-1];
		l->bd--;
		if (l->bd == l-> bg)
			l->bg = 0;
	}
}

//Replaces data with new_data in the list l
void replace(char* data, char* new_data, list l)
{	
	int i;
	for (i = 0; i < l->bd && (strcmp(l->tasks[i], data) != 0); i++)
		;
	if (i != l->bd)
		l->tasks[i] = new_data;
}

int main()
{	
	/* Some tests
	list l;
	init_list(l);
	char message[] = "task 1";
	char message2[] = "task 2";
	char message3[] = "task 3";
	insert(message, l);
	insert(message2, l);
	insert(message3, l);
	delete(message, l);
	replace(message2, message3, l);
	int i;
	for (i = 0; i < l->bd; i++)
		printf("%s\n", l->tasks[i]);
	printf("%s", get_next_task(l)); */
	return 0;
}
