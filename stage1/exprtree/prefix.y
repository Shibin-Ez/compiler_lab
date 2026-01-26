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

expr : PLUS expr expr  {$$ = makeOperatorNode('+',$2,$3);}
  | MINUS expr expr   {$$ = makeOperatorNode('-',$2,$3);}
  | MUL expr expr {$$ = makeOperatorNode('*',$2,$3);}
  | DIV expr expr {$$ = makeOperatorNode('/',$2,$3);}
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