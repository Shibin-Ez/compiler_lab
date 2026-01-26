%{
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
    #include "../generator.h"
%}

%%

[0-9]+ {
          yylval.no = makeConstantLeafNode(atoi(yytext));
          return NUM;
        }
"begin" {return BEGN;}
"end" {return END;}
"read" {return READ;}
"write" {return WRITE;}
[a-z] {
          yylval.no = makeVariableLeafNode(yytext);
          return ID;
      }
"+"   {return PLUS;}
"*"   {return MUL;}
"-"   {return MINUS;}
"/"   {return DIV;}
[()=;]   {return *yytext;}
[ \t\n]      ; /* skip whitespace */

%%

int yywrap()
{
    return 1;
}