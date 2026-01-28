%{
 #include <stdlib.h>
 #include <stdio.h>
 #include "../generator.h"
 #include "../evaluator/evaluator.h"
 int yylex(void);
 void yyerror(char const *s);
%}

%union{
  struct tnode *no;
}
%type <no> program Slist Stmt InputStmt OutputStmt AssignStmt expr
%token <no> BEGN READ WRITE NUM ID END
%token PLUS MINUS MUL DIV
%left PLUS MINUS
%left MUL DIV

%%

program : BEGN Slist END
        {
          $$ = $2;
          // FILE *fp;
          // fp = fopen("out.xsm", "w");
          // startCodeGen($$, fp);

          evaluate($$);

          exit(1);
        }
        | BEGN END
        ;
Slist : Slist Stmt {$$ = makeConnecterNode($1, $2);}
      | Stmt {$$ = $1;}
      ;
Stmt : InputStmt | OutputStmt | AssignStmt;
InputStmt: READ '(' ID ')' ';' {$$ = makeReadNode($3);};
OutputStmt: WRITE '(' expr ')' ';' {$$ = makeWriteNode($3);};
AssignStmt: ID '=' expr ';' {$$ = makeAssgNode($1, $3);};

expr : expr PLUS expr  {$$ = makeOperatorNode('+',$1,$3);}
  | expr MINUS expr   {$$ = makeOperatorNode('-',$1,$3);}
  | expr MUL expr {$$ = makeOperatorNode('*',$1,$3);}
  | expr DIV expr {$$ = makeOperatorNode('/',$1,$3);}
  | '(' expr ')'  {$$ = $2;}
  | NUM   {$$ = $1;}
  | ID    {$$ = $1;}
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