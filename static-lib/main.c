#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib/mlc.h"

char* gen_task(int id)
{
    char *str = malloc(1024);
    strcpy(str, "echo Salut");
    return str;
}

void get_result(int id, double mac, int size_of, char* data)
{
    unsigned char *hwaddr = (unsigned char*)&mac;
    printf("--- \n Received result. \n Task : %d \n Hwaddr : %.2x:%.2x:%.2x:%.2x:%.2x:%.2x \n Data : %s \n --- \n", id, hwaddr[0], hwaddr[1], hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5], data);
}

int main(int argc, char* argv[])
{
    init(&gen_task, &get_result);
    return 0;
}
