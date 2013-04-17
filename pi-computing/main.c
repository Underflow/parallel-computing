#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../static-lib/lib/mlc.h"
#include "pi_server.h"

double somme = 0.0;

char* gen_task(int id)
{
    char *str = malloc(1024);
    char *plg = generate_plg(id,100000000000);
    if(plg)
    {
    strcpy(str, "/cluster/bin/application/pi_client ");
    strcat(str, plg);
    strcat(str, " 0.0");
    }
    else
    {
	strcpy(str, "echo 0.O");
    }
    printf("Generate task %d\n", id);
    return str;
}

void get_result(int id, double hwaddr, int size_of, char* data)
{
    printf("--- \n Received result. \n Task : %d \n Data : %s \n --- \n", id, data);
    double result = strtod(data, NULL);
    int res = atoi(data);
    if (res == -1)
     system("pkill dispatcher");
    make_sum(result, &somme);
}

int main(int argc, char* argv[])
{
    init(&gen_task, &get_result);
    return 0;
}
