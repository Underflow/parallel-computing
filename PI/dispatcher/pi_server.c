#include "pi_server.h"

char* generate_plg(int start, long long int n)
{
double h = 1.0 / (long double)n;
char* plg = malloc(1024);
int start_i, stop_i; 
start_i = start*2500000+1; // index du début de la somme
stop_i = start_i + 2499999; // index de la fin de la somme (ici somme de 1 à 2500000 puis de 2500001 à 5000000 etc)
if (stop_i <= n) // on a pas encore atteint la fin de la somme
sprintf(plg, "%d %d %.20f", start_i, stop_i, h);
else
sprintf(plg, "-1"); // toutes les sous sommes ont été faites
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
