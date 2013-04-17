#include <stdint.h>
#include <inttypes.h>
#include "pi_server.h"

char* generate_plg(int start, unsigned long long int n)
{
double h = 1.0 / (long double)n;
char* plg = malloc(1024);
uint64_t start_i;
uint64_t stop_i; 
start_i = start*10000000LLU+1LLU; // index du début de la somme
stop_i = start_i + 9999999LLU; // index de la fin de la somme (ici somme de 1 à 2500000 puis de 2500001 à 5000000 etc)
if (stop_i <= n) // on a pas encore atteint la fin de la somme
	sprintf(plg, "%" PRId64 " %" PRId64 " %.20f", start_i, stop_i, h);
else
	return NULL;

return plg;
}

void make_sum(double subsum, double *sum) // fait la somme totale en additionnant les sous sommes renvoyées par les clients
{
   *sum += subsum;
   printf("pi=%.30f\n", *sum); 
}

/*int main(int argc, char **argv)
{
double sum = 0;
for (i=0 ; i < size ; i++ )
{
      printf("somme=%.12f pour le
          noeud %d\n",
          sum_buf[i], i);
      sum += sum_buf[i];
    }
    printf("pi=%.12f\n", sum);

}*/
