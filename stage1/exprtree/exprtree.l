%{
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
    #include "exprtree.h"
%}

%%

[0-9]+ {
          yylval.no = makeLeafNode(atoi(yytext));
          return NUM;
        }
"+"   {return PLUS;}
"*"   {return MUL;}
"-"   {return MINUS;}
"/"   {return DIV;}
[()]   return *yytext;
[\n]      return END;
[ \t]      ; /* skip whitespace */

%%

int yywrap()
{
    return 1;
}