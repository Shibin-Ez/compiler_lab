%{
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
    #include "../generator/generator.h"
%}

%%

[0-9]+ {
          yylval.no = makeConstantLeafNode(atoi(yytext));
          return NUM;
        }
"begin" { return BEGN; }
"end" { return END; }
"read" { return READ; }
"write" { return WRITE; }
"if" { return IF; }
"then" { return THEN; }
"else" { return ELSE; }
"endif" { return ENDIF; }
"while" { return WHILE; }
"do" { return DO; }
"endwhile" { return ENDWHILE; }
"break" { 
            yylval.no = makeBreakLeafNode();
            return BREAK;
        }
"continue"  { 
                yylval.no = makeContinueLeafNode();
                return CONTINUE;
            }
"repeat" { return REPEAT; }
"until" { return UNTIL; }

[a-z] {
          yylval.no = makeVariableLeafNode(yytext);
           return ID; 
      }
"+"     { return PLUS; }
"*"     { return MUL; }
"-"     { return MINUS; }
"/"     { return DIV; }
">"     { return GT; }
"<"     { return LT; }
">="    { return GTE; }
"<="    { return LTE; }
"!="    { return NEQ; }
"=="    { return EQ; }
[()=;]   { return *yytext; }
[ \t\n]      ; /* skip whitespace */

%%

int yywrap()
{
    return 1;
}