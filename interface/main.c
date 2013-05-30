#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../static-lib/lib/mlc.h"
#include "gui.h"

char* gen_task(int id)
{
    char *str = malloc(1024);
    strcpy(str, "");
    return str;
}

void get_result(int id, double mac, int size_of, char* data)
{
    unsigned char *hwaddr = (unsigned char*)&mac;
    //printf("--- \n Received result. \n Task : %d \n Hwaddr : %.2x:%.2x:%.2x:%.2x:%.2x:%.2x \n Data : %s \n --- \n", id, hwaddr[0], hwaddr[1], hwaddr[2], hwaddr[3], hwaddr[4], hwaddr[5], data);
    // :: wprintw
}

int main(int argc, char* argv[])
{
    // -> Tread
    startGUI();
    // <- Thread
    init(&gen_task, &get_result);
    return 0;
}
