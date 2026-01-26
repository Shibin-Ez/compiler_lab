%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
%}

/* %token DIGIT */
%token LETTER
%token DIGIT
%left '+'
%left '*'

%%

start: LETTER rest '\n' {printf("Valid variable name\n");exit(1);}
      
rest: rest LETTER | rest DIGIT | ;

%%


yyerror(char const *s)
{
    printf("Invalid variable name");
}

yylex(){
    int c = getchar();

    if (c == EOF) {
      return 0;
    }
    else if(isalpha(c)){
        return LETTER;
    }
    else if(isdigit(c)){
        return DIGIT;
    }
    else if(c == '\n'){
        return '\n';
    }
    
    yylex();
}

main()
{
    yyparse();
    return 1;
}

