%{
  #include <stdlib.h>
  #include <stdio.h>

  int word_count = 0;
%}

word A[a-zA-Z0-9][a-zA-Z0-9]

%%

{word} {
  word_count++;
}

%%

int yywrap()
{
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
  printf("Words: %d\n", word_count);
  return 1;
}