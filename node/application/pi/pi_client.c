#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

// fonction à intégrer
double f(double x)
{
  return (4.0 / (1.0 + x*x));
}

 /* Calcul de la partie de la somme
* approximant l’intégrale de f()
* à faire par ce client */
void sub_sum(long long int start_i,
             long long int stop_i, 
	     double h,
	     double* sous_sum)
{
  double f_xi, f_xi1;
  long long int i = 0;
  *sous_sum = 0.0;
  double x = 0;
  //printf("Sous-somme de %Ld à %Ld\n",
  //    start_i, stop_i);
  x = h*(start_i-1);
  f_xi1 = f(x);
  for ( i = start_i; i <= stop_i; i++ ) {
    f_xi = f_xi1;
    f_xi1 = f(x+h);
    *sous_sum += (f_xi+f_xi1);
    x += h;
  }
  *sous_sum *= h/2.0;
  printf("%.20f", *sous_sum); // on affiche le résultat de la somme partielle
}
/* En arguments : - début de la somme
		  - fin de la somme
		  - h */
int main(int argc, char **argv)
{
if (argc == 3 && atoi(argv[1]) == -1) // on a fini la totalité de la somme
printf("-1");
else
{
long long int start_i = atoll(argv[1]);
long long int stop_i = atoll(argv[2]);
double h = strtod(argv[3], NULL);
double sous_sum = strtod(argv[4], NULL);

sub_sum(start_i, stop_i, h, &sous_sum);
//printf("sous_sum : %f", sous_sum);
}
return 0;
}
