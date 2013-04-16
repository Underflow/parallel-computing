#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc != 2)
        printf("Bad usage : %s file\n", argv[0]);
    else
    {
        FILE *f = fopen(argv[1], "r");
        yyrestart(f);
        yyparse(f);
        fclose(f);
    }
    return 0;
}
