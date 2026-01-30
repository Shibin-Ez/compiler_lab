// linker.h
#ifndef LINKER_H
#define LINKER_H

#include <stdio.h>

// External variables from lex.yy.c
extern FILE *yyin;
extern char *yytext;
extern int yylval;

// Variable to track first pass of lex and second
extern int pass;
extern FILE *out_fp;

// Lexer function
int yylex(void);

// Your functions
void label_table_insert(char *label, int line_no);
int label_table_find(int label_no);
// void writeInstruction(char *instr);
// void writeJumpInstr(char *instr_name, int label_no);

#endif