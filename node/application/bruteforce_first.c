#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    return 0;
}

void char_to_int(char *src,int *dst,char *dictionary)
{
    size_t i;
    for(i=0;i<strlen(src);i++)
    {
        *(dst + i) = findKey(*(src + i),dictionary); 
    }
}

void char_to_int_plg1(char *plg1,char *plg2,int *dst,char *dictionary)
{
    if(strlen(plg1) < strlen(plg2))
    {
        size_t i;
        for(i=0;i<strlen(plg2)-strlen(plg1);i++)
        {
            *(dst +i) = -1;
        }
        for(i=strlen(plg2)-strlen(plg1);i<=strlen(plg2);i++)
        {
            *(dst + i) = findKey(*(plg1 + i),dictionary);
        }
    }
    else
    {
        char_to_int(plg1,dst,dictionary);
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
        int *plg_2 = malloc(sizeof(int) * strlen(argv[2]));
        int *real_pwd = malloc(sizeof(int) * strlen(argv[3]));
        int *try_found = malloc(sizeof(int) * strlen(argv[2]));
        char *Dictionary= malloc(126-33);

        size_t size_plg = strlen(argv[2]);
        size_t size_dic = strlen(Dictionary)
        add_Dictionary(33,126,Dictionary);
        
        char_to_int(argv[2],plg_2,Dictionary);
        char_to_int(argv[3],real_pwd,Dictionary);
        char_to_int_plg1(argv[1],argv[2],try_found,Dictionary);

        while(compareString(try_found,plg_2,size_plg) != 1 && compareString(try_found,real_pwd,size_plg)!= 1)
            increment_str(try_found,size_plg,0,Dictionary,size_dic);
        if(compareString(try_found,real_pwd,size_plg) == 1)
            printf("1");
        else
            printf("0");

    }
    return 0;
}
