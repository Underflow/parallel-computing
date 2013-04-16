%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YY_HEADER_NO_UNDEFS

%}
%expect 0


%token DIGIT


%left PLUS MIN MUL DIV
%left EQUAL

%start INPUT
%%

INPUT   :
        | INPUT EXPR
;

EXPR    : DIGIT { $$ = 1; }
;

%%


int yyerror(char *msg) {
    printf("Lexing error: %s\n", msg);
}
