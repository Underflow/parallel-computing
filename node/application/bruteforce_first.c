#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void increment_str(char* src,int offset)
{   
    size_t j = offset;
    size_t i = strlen(src) -1 - offset;
    if (i < 0)
        return;


    if(*(src + i) == 'Z')
    {
        j++;
        *(src + i) = '0';

        increment_str(src,j);
    }
    else if(*(src + i) == '9')
        *(src + i) = 'A';
    else
        *(src + i) = (char)src[i] + 1;

}

int compareString(char* str_1,char* str_2)
{
    if(strlen(str_1) == strlen(str_2))
    {
        size_t i;
        for(i=0;i<strlen(str_1);i++)
        {
            if((char)str_1[i] != (char)str_2[i])
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
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
    */

    if(argc==4)
    {
        char *plg_2 = argv[2];
        char *real_pwd = argv[3];
        char *try_found = argv[1];

        strcpy(plg_2,argv[2]);
        strcpy(real_pwd,argv[3]);
        strcpy(try_found,argv[1]);

        while(compareString(try_found,plg_2) != 1 && compareString(try_found,real_pwd)!= 1)
        {
            increment_str(try_found,0);
            printf("%s\n",try_found);
        }
        if(compareString(try_found,real_pwd) == 1)
        {
            printf("Find Mot de passe trouvé : %s",try_found);
        }
        else
        {
            printf("Not_Found");
        }

    }
    return 0;
}
