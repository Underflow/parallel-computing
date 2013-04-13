/* 
** Pour utiliser le bruteforce il suffit de l'initiliasé lorsque
** l'on veut l'utiliser avec la fonction init_bf(int MAXCAR,char* pwd_launch) ensuite
** il appeler la fonction generate_new_plg, cette fonction génère
** une plage reconnaissable par le binaire brute force du client du type:
** [-1][-1][-1][-1] [-1][-1][-1][50]  
**  PLG 1   SEPARATION  PLG2
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "brute_force.h"

static const int BASE=93;
static char* mdp;

/* 
** Le bruteforce doit être initialisé, le paramètre
** est le nombre de caractères maximal du mot de passe
*/

void init_bf(int MAXCAR,char* mdp_launch)
{
    size_t i;
    MAX_CAR=MAXCAR;
    mdp=malloc(MAXCAR*sizeof(int));
    act_plg=malloc(MAXCAR*sizeof(int));
    max_plg=malloc(MAXCAR*sizeof(int));

    strcat(mdp,mdp_launch);

    for(i=0;i<MAXCAR;i++)
    {
        *(act_plg + i) = -1;
        *(max_plg + i) = BASE;
    }
}

void convert(int* convers,int b)
{

    size_t i=MAX_CAR-1;
    int quotient=b;
    int reste;
    for(size_t j=0;j<MAX_CAR;j++)
        *(convers + j) = -1;

    while(quotient)
    {
        reste = quotient % BASE;
        *(convers + i) = reste;
        quotient = quotient / BASE;
        i--;
    }
}

/*
** Cette fonction ajoute à act_plg un nombre en base 10 
*/
void add(int b)
{
    int* conversion;
    int retenue=0;
    conversion=malloc(MAX_CAR*sizeof(int));
    convert(conversion,b);

    size_t i=MAX_CAR-1;
    while(i)
    {
        if(i>=0)
        {
            if((*(conversion + i) == -1) && *(act_plg + i) == -1) 
            {
                if(retenue)
                    *(act_plg + i) = retenue;
                break;
            }
            else if(*(act_plg + i) == -1 && *(conversion + i) > -1)
            {
                int somme= *(conversion +i) + retenue;
                retenue=0;
                if(somme > BASE)
                {
                    retenue=somme/BASE;
                *(act_plg + i) = somme -retenue*BASE;
                }
                else
                {
                    *(act_plg +i) = somme;
                }
            }
            else if(*(conversion + i) == -1 && *(act_plg + i) > -1)
            {
                int somme= *(act_plg + i) + retenue;
                retenue=0;
                if(somme > BASE)
                {
                    retenue=somme/BASE;
                    *(act_plg + i) = somme - retenue*BASE;
                }
                else
                {
                    *(act_plg + i) = somme;
                }

            }
            else if(*(conversion + i) > -1 && *(act_plg + i) > -1)
            {
                int somme= *(conversion + i) + *(act_plg + i) + retenue;
                retenue=0;
                if(somme > BASE)
                {
                    retenue= somme / BASE;
                    *(act_plg + i) = somme - retenue*BASE;
                }
                else
                {
                    *(act_plg + i) = somme;
                }
            }
            i--;
        }
        else
            break;
    }

}

char* generate_new_plg(int calcul)
{
    int* begin=malloc(sizeof(int) * MAX_CAR);
    int* end=malloc(sizeof(int) * MAX_CAR);

    for(size_t i=0;i<MAX_CAR;i++)
        *(begin + i) = *(act_plg +i);

    add(calcul);

    for(size_t i=0;i<MAX_CAR;i++)
        *(end + i) = *(act_plg + i);


    char* str=malloc(1024);

    for(size_t i=0;i<MAX_CAR;i++)
    {
        char aux[2];
        sprintf(aux,"[%d]",*(begin + i));
        strcat(str,aux);
        aux[0]='\0';
        aux[1]='\0';
    }

    strcat(str," ");

    for(size_t i=0;i<MAX_CAR;i++)
    {
        char aux[2];
        sprintf(aux,"[%d]",*(end + i));
        strcat(str,aux);
        aux[0]='\0';
        aux[1]='\0';
    }
    strcat(str," ");
    strcat(str,mdp);

    return str;

}



