%{
/*** Auxiliary declarations section ***/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
                        printf($<word>1);
                        exit(1);
                      }
      ;

expr: expr '+' expr     {
                          $<word>$ = malloc(strlen($<word>1) + strlen($<word>3) + 4);
                          sprintf($<word>$, "+ %s %s", $<word>1, $<word>3);
                        }
    | expr '*' expr     {
                          $<word>$ = malloc(strlen($<word>1) + strlen($<word>3) + 4);
                          sprintf($<word>$, "* %s %s", $<word>1, $<word>3);
                        }
    | '(' expr ')'      { $<word>$ = $<word>2; }
    | VARIABLE          { $<word>$ = $<word>1; }
    ;

%%

/*** Auxiliary functions section ***/

int yyerror(char const *s)
{
    printf("yyerror %s",s);
    return;
}

int main()
{
    yyparse();
    return 1;
}