%option noyywrap
%{
  #include <stdlib.h>
  #include <stdio.h>
%}

number [0-9]+

%%

{number} {printf("Found : %d with %d digits\n",atoi(yytext), yyleng);}

%%

int main()
{
  yylex();
  return 1;
}