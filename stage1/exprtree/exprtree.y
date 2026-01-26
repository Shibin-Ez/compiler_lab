%{
 #include <stdlib.h>
 #include <stdio.h>
 #include "exprtree.h"
 int yylex(void);
 void yyerror(char const *s);
%}

%union{
  struct tnode *no;
}
%type <no> expr program
%token <no> NUM END
%token PLUS MINUS MUL DIV
%left PLUS MINUS
%left MUL DIV

%%

program : expr END {
    $$ = $2;
    FILE *fp;
    fp = fopen("out.xsm", "w");
    evaluate($1, fp);

    exit(1);
   }
  ;

expr : expr PLUS expr  {$$ = makeOperatorNode('+',$1,$3);}
  | expr MINUS expr   {$$ = makeOperatorNode('-',$1,$3);}
  | expr MUL expr {$$ = makeOperatorNode('*',$1,$3);}
  | expr DIV expr {$$ = makeOperatorNode('/',$1,$3);}
  | '(' expr ')'  {$$ = $2;}
  | NUM   {$$ = $1;}
  ;

%%

void yyerror(char const *s)
{
    printf("yyerror %s",s);
}

int main(void) {
  
  yyparse();

  return 0;
}