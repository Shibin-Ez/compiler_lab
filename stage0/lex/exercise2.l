%{
  #include <stdlib.h>
  #include <stdio.h>

  int int_count = 0;
  int float_count = 0;
%}

integer [0-9]+
float [0-9]+\.[0-9]+

%%

{integer} {
  int_count++;
}

{float} {
  float_count++;
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
  printf("Integers: %d, Floating_Points: %d\n", int_count, float_count);
  return 1;
}