%{
  #include <stdio.h>  
%}

comment \/\*([^*]|\*+[^*/])*\*+\/

%%

{comment} {
  printf("FOUND COMMENT: %s\n", yytext);
}

%%

int yywrap() {
  return 1;
}

int main(int argc, char *argv[]) {
  if (argc > 1) {
    FILE *fp = fopen(argv[1], "r");
    if (fp) {
      yyin = fp;
    }
  }
  yylex();
  return 1;
}