#include "linker.h"
#include <stdio.h>
#include <stdlib.h>

#define ENTRY_POINT 2056

struct node {
  int label;
  int addr;
  struct node *next;
};

struct node *head = NULL;

// File for the output to print to
FILE *out_fp;

// Pass number (1 = build label table, 2 = resolve and output)
int pass = 1;

int get_code_addr(int line_no) { return ENTRY_POINT + 2 * line_no; }

void label_table_insert(char *label, int line_no) {
  // Label is of format: L{number}:\n

  int label_no = atoi(label + 1);
  int code_addr = get_code_addr(line_no);

  struct node *temp = malloc(sizeof(struct node));
  temp->label = label_no;
  temp->addr = code_addr;
  temp->next = head;
  head = temp;
}

// returns label's address
int label_table_find(int label_no) {
  struct node *p = head;
  while (p) {
    if (p->label == label_no) {
      return p->addr;
    }
    p = p->next;
  }

  return 0; // Not found
}

// void writeInstruction(char *instr) {
//   if (out_fp)
//     fprintf(out_fp, "%s", instr);
// }

// void writeJumpInstr(char *instr_name, int label_no) {
//   int code_addr = label_table_find(label_no);
//   fprintf(out_fp, "%s %d\n", instr_name, code_addr);
// }

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return 1;
  }

  yyin = fopen(argv[1], "r");
  if (!yyin) {
    fprintf(stderr, "Error: Cannot open file '%s'\n", argv[1]);
    return 1;
  }

  // First pass - build label table
  pass = 1;
  yylex();

  // Reset for second pass
  rewind(yyin);

  // Second pass - resolve labels and build output file
  pass = 2;
  out_fp = fopen("out.xsm", "w");
  yylex();

  fclose(out_fp);
  fclose(yyin);
  return 0;
}