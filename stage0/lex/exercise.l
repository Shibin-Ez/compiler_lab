%{
  #include <stdlib.h>
  #include <stdio.h>

  int line_count = 0;
  int word_count = 0;
  int char_count = 0;
%}

character [a-zA-Z0-9]
word {character}+
line \n

%%

{word} {
  word_count++;
  char_count += yyleng;
}

{line} {
  line_count++;
  char_count++;
}

. {
  char_count++;
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
  printf("Lines: %d, Words: %d, Characters: %d\n", line_count, word_count, char_count);
  return 1;
}