%{
/*** Auxiliary declarations section ***/

#include<stdio.h>
#include<stdlib.h>

%}

 /*** YACC Declarations section ***/
%token DIGIT NEWLINE

%%

/*** Rules Section ***/
start : expr NEWLINE  {
                        printf("\nComplete\n");
                        exit(1);
                      }
      ;

expr: expr '+' expr     {printf("+ ");}
    | expr '-' expr     {printf("- ");}
    | '(' expr ')'
    | DIGIT             {printf("%d ",$1);}
    ;

%%

/*** Auxiliary functions section ***/

yyerror(char const *s)
{
    printf("yyerror %s",s);
    return;
}

main()
{
    yyparse();
    return 1;
}