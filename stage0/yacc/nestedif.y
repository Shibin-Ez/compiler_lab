%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count = 0;
void handle_count();
%}

/* %token DIGIT */
%token IF
%left '+'
%left '*'

%%

start: stmts '\n' {exit(1);}

stmts: stmts stmt ';' {handle_count();}
     | stmt ';' {handle_count();}
     ;

stmt : IF expr stmt {count++;}
     | expr
     ;
expr : expr op expr
     | digit
     ;
op   : '+' | '*'
     ;
digit: '1' | '2' | '3' | '4' | '5'
     ;

%%

void handle_count() {
  if (count > 0) {
    printf("Nested if with count: %d\n", count);
    count = 0;
  }
}

yyerror(char const *s)
{
    printf("yyerror %s",s);
}

yylex(){
    char word[32];

    if (scanf("%31s", word) != 1) {
        return 0;
    }

    if (strcmp(word, "if") == 0) {
        return IF;
    }
    

    return word[0];
}

main()
{
    yyparse();
    return 1;
}

