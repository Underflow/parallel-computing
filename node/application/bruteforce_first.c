#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static const char MAX_CAR=8;

void increment_str(int* src,int size,int offset,char *dictionary,size_t size_dic)
{   
    size_t j = offset;
    size_t i = size -1 - offset;
    if (i < 0)
        return;


    if(*(src + i) == size_dic -1)
    {
        j++;
        *(src + i) = 0;

        increment_str(src,size,j,dictionary,size_dic);
    }
    else
        *(src + i) = src[i] + 1;

}

int compareString(int* str_1,int* str_2,int size)
{
    size_t i;
    for(i=0;i<size;i++)
    {
        if(str_1[i] != str_2[i])
        {
            return 0;
        }
    }
    return 1;
}

void add_Dictionary(int ascii_begin,int ascii_end,char *dictionary)
{
    size_t i;
    for(i=ascii_begin; i <= ascii_end; i++)
    {
        *(dictionary + i - ascii_begin)=(char)i;
    }
}

int findKey(char searsch,char *dictionary)
{
    size_t i;
    for(i=0;i<strlen(dictionary);i++)
    {
        if(*(dictionary + i) == searsch)
            return i;
    }
    return -1;
}

void char_to_int(char *src,int *dst,char *dictionary)
{
        size_t i=MAX_CAR;
    while(i!=-1)
    {
        if(i>strlen(src))
        {
            *(dst + MAX_CAR -i)= -1;
        }
        else
        *(dst + MAX_CAR -1- i) = findKey(*(src + i),dictionary); 

        i--;
    }
}

void parse_plg(char *src,int *dst,int size)
{
    size_t i,j;
    size_t begin= 0;
    size_t end=0;
    size_t dst_i = size -1;

    for(i=0;i<size;i++)
        *(dst + i) = -1;

    j=strlen(src);
    while(j!=-1)
    {  
        if(src[j] == ']' )
        {
            end=j;
        }
        else if(src[j] == '[')
        {
            char *aux=malloc(2);
            begin=j;
            strncpy(aux,src + begin +1  ,end-begin-1);
            *(dst+dst_i) = atoi(aux);
            dst_i--;
            free(aux);
        }
        j=j-1;
    }
}
int main(int argc,char * argv [])
{
    /* 
    ** Application Brute-force / Binaire client
    ** ----------------------------------------
    ** Quelques modifications à effectuer pour gérer les
    **  memory leak et les valeurs de retour du binaire
    */
    /*
    ** 3 arguments : 
    ** -------------
    ** - Première plage ex : AAAAAA
    ** - Fin de la plage ex : FFFFFF sachant que AAAAAA < AAAAAF
    ** - Mot de passe réel
    ** 
    ** AAA < AAAA
    */

    if(argc==4)
    {
        int *plg_2 = malloc(sizeof(int) * MAX_CAR);
        int *real_pwd = malloc(sizeof(int) * MAX_CAR);
        int *try_found = malloc(sizeof(int) * MAX_CAR);
        char *Dictionary= malloc(126-33);

        size_t size_plg = MAX_CAR;
        add_Dictionary(33,126,Dictionary);
        size_t size_dic = strlen(Dictionary);

        char_to_int(argv[3],real_pwd,Dictionary);
        parse_plg(argv[1],try_found,size_plg);
        parse_plg(argv[2],plg_2,size_plg);
       
          while(compareString(try_found,plg_2,size_plg) != 1 && compareString(try_found,real_pwd,size_plg)!= 1)
           increment_str(try_found,size_plg,0,Dictionary,size_dic);
           if(compareString(try_found,real_pwd,size_plg) == 1)
           printf("1");
           else
           printf("0");

    }

    return 0;
}
