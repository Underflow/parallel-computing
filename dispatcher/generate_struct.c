#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc,char *argv[])
{

    // Send DATA Model    
    struct block
    {
        uint8_t client_id;
        char cluster_id;
        char opcode;
        uint8_t size_of;
        char *data;
    }__attribute__((packed));
    struct block *test;


    FILE *file;

    test=malloc(sizeof(struct block));


    if(argc==1)
    {
        test->client_id=00035;
        test->cluster_id='c';
        test->opcode='a';
        test->data = malloc(10*sizeof(test->data));
        test->data ="azert";

        char *str=malloc(10*sizeof(*str));
        str="coucoucoucououccoucocucocucocucoucocucocuocuccuoccouu";
        printf("%d\n",sizeof(str));
        test->size_of=sizeof(test);
        printf("%u\n",sizeof(test->data));

        file=fopen("struct_test","wb");
        fwrite(test,sizeof(struct block),1,file);
        fclose(file);
    }
    else /*if(strcmp(argv[1],"read")==0)*/
    {
        file = fopen("struct_test", "r" );
        if (file == NULL)
        {
            printf("erreur lecture" );
            exit(1);
        }
        fread(test, sizeof(struct block), 1, file);
        fclose(file);
        printf("%d",test->size_of);
    }
    /*else
        printf("Argument 1 faux , read ou write\n");
*/


    return 0;
}
