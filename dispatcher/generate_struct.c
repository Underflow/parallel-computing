#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc,char *argv[])
{

    // Send DATA Model    
    struct block
    {
        uint8_t client_id[8];
        uint8_t cluster_id;
        uint8_t opcode;
        uint8_t size_of_data[8];
    }__attribute__((packed));
    struct block *test;


    FILE *file;

    test=malloc(sizeof(struct block));


    if(argc==1)
    {
        test->client_id[0]=00035;
        test->cluster_id=00030;
        test->opcode=00036;
        test->size_of_data[0]=50;
        
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
        printf("%d",test->size_of_data[0]);
    }
    /*else
        printf("Argument 1 faux , read ou write\n");
*/


    return 0;
}
