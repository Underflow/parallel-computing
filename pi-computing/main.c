#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../static-lib/lib/mlc.h"

char* gen_task(int id)
{
    char *str = malloc(1024);
    strcpy(str, "echo Salut");
    return str;
}

void get_result(int id, char* data)
{
    printf("--- \n Received result. \n Task : %d \n Data : %s \n --- \n", id, data);
}

int main(int argc, char* argv[])
{
    init(&gen_task, &get_result);
    return 0;
}
