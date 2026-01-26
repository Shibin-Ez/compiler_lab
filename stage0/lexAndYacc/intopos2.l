%{
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
%}

%%

[a-zA-Z]+ {
          yylval.word = strdup(yytext);
          return VARIABLE;
        }
"+"   return *yytext;
"*"   return *yytext;
[()]   return *yytext;
[\n]      return NEWLINE;
[ \t]      ; /* skip whitespace */

%%

yywrap()
{
    return 1;
}