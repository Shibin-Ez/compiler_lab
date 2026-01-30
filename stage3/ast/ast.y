%{
 #include <stdlib.h>
 #include <stdio.h>
 #include "../generator/generator.h"
 #include "../evaluator/evaluator.h"
 int yylex(void);
 void yyerror(char const *s);
%}

%union{
  struct tnode *no;
}
%type <no> program Slist Stmt InputStmt OutputStmt AssignStmt IfStmt WhileStmt expr
%type <no> BreakStmt ContStmt RepeatStmt DoWhileStmt
%token <no> BEGN READ WRITE NUM ID END IF THEN ELSE ENDIF WHILE DO ENDWHILE BREAK CONTINUE
%token REPEAT UNTIL
%token PLUS MINUS MUL DIV GT LT GTE LTE NEQ EQ 
%left PLUS MINUS
%left MUL DIV

%%

program : BEGN Slist END
        {
          $$ = $2;
          FILE *fp;
          fp = fopen("out.xsm", "w");
          startCodeGen($$, fp);

          // evaluate($$);

          exit(0);
        }
        | BEGN END
        ;
Slist : Slist Stmt {$$ = makeConnectorNode($1, $2);}
      | Stmt {$$ = $1;}
      ;
Stmt : InputStmt | OutputStmt | AssignStmt | IfStmt | WhileStmt | BreakStmt | ContStmt 
     | RepeatStmt | DoWhileStmt;
InputStmt: READ '(' ID ')' ';' {$$ = makeReadNode($3);};
OutputStmt: WRITE '(' expr ')' ';' {$$ = makeWriteNode($3);};
AssignStmt: ID '=' expr ';' {$$ = makeAssgNode($1, $3);};
IfStmt: IF '(' expr ')' THEN Slist ELSE Slist ENDIF ';' {$$ = makeIfElseNode($3, $6, $8);}
      | IF '(' expr ')' THEN Slist ENDIF ';' {$$ = makeIfNode($3, $6);}
      ;
WhileStmt: WHILE '(' expr ')' DO Slist ENDWHILE ';' {$$ = makeWhileNode($3, $6);}
BreakStmt: BREAK ';' {$$ = $1;}
ContStmt: CONTINUE ';' {$$ = $1;}
RepeatStmt: REPEAT Slist UNTIL '(' expr ')' ';' {$$ = makeRepeatNode($2, $5);}
DoWhileStmt: DO Slist WHILE '(' expr ')' ';' {$$ = makeDoWhileNode($2, $5);}

expr : expr PLUS expr  {$$ = makeOperatorNode("+",$1,$3);}
  | expr MINUS expr   {$$ = makeOperatorNode("-",$1,$3);}
  | expr MUL expr {$$ = makeOperatorNode("*",$1,$3);}
  | expr DIV expr {$$ = makeOperatorNode("/",$1,$3);}
  | '(' expr ')'  {$$ = $2;}
  | NUM   {$$ = $1;}
  | ID    {$$ = $1;}
  | expr GT expr {$$ = makeOperatorNode(">",$1,$3);}
  | expr LT expr {$$ = makeOperatorNode("<",$1,$3);}
  | expr GTE expr {$$ = makeOperatorNode(">=",$1,$3);}
  | expr LTE expr {$$ = makeOperatorNode("<=",$1,$3);}
  | expr NEQ expr {$$ = makeOperatorNode("!=",$1,$3);}
  | expr EQ expr {$$ = makeOperatorNode("==",$1,$3);}
  ;

%%

void yyerror(char const *s)
{
    printf("yyerror %s\n",s);
    exit(1);
}

int main(void) {
  
  yyparse();

  return 0;
}