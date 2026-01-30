%{
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
    #include "../generator/generator.h"
    #include "../spec/expl.h"
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
"decl" { return DECL; }
"enddecl" { return ENDDECL; }
"int"   { 
            yylval.no = makeTypeLeafNode(INT_TYPE);
            return INT; 
        }
"str"   { 
            yylval.no = makeTypeLeafNode(STR_TYPE);
            return STR; 
        }
[a-z]+  {
            yylval.name = strdup(yytext);
            return ID; 
        }
\"[^\"]*\"  {
                yylval.no = makeStringConstantLeafNode(yytext);
                return STRCONST;
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
[()=;,\[\]]   { return *yytext; }
[ \t\n]      ; /* skip whitespace */

%%

int yywrap()
{
    return 1;
}