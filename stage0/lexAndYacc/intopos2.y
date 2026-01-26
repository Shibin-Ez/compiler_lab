%{
/*** Auxiliary declarations section ***/

#include<stdio.h>
#include<stdlib.h>

%}

 /*** YACC Declarations section ***/
%union {
  int integer;
  char* word;
}

%token VARIABLE OP NEWLINE
%type <word> VARIABLE OP
%type <integer> NEWLINE
%left '+'
%left '*'

%%

/*** Rules Section ***/
start : expr NEWLINE  {
                        printf("\nComplete\n");
                        exit(1);
                      }
      ;

expr: expr '+' expr     {printf("+ ");}
    | expr '*' expr     {printf("* ");}
    | '(' expr ')'
    | VARIABLE          {printf("%s ", $<word>1);}
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