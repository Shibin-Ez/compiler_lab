%{
    #include <stdio.h>
    #include <string.h>
    #include "linker.h"
    
    int line_pos = 0;
%}

%%

L[0-9]+":"[ \t]*\n    { 
                        /* Line of Label */
                        if (pass == 1) {
                          label_table_insert(yytext, line_pos);
                        }
                      }

[0-9]+[ \t]*\n        { 
                        /* Line of Number */
                        // It's Header, Skipping for pass 1
                        if (pass == 2) {
                          fprintf(out_fp, "%s", yytext);
                        }
                      }

"JMP"[ \t]+L[0-9]+[ \t]*\n  {
                              if (pass == 1) {
                                line_pos++;
                              } else if (pass == 2) {
                                int label_no;
                                sscanf(yytext, "JMP L%d", &label_no);
                                int code_addr = label_table_find(label_no);
                                fprintf(out_fp, "JMP %d\n", code_addr);
                              }
                            }

("JZ"|"JNZ")[ \t]+R[0-9]+[ \t]*,[ \t]*L[0-9]+[ \t]*\n  {
                              if (pass == 1) {
                                line_pos++;
                              } else if (pass == 2) {
                                char instr_name[4];
                                int reg_no, label_no;
                                sscanf(yytext, "%s R%d, L%d", instr_name, &reg_no, &label_no);
                                int code_addr = label_table_find(label_no);
                                fprintf(out_fp, "%s R%d, %d\n", instr_name, reg_no, code_addr);
                              }
                            }

[^\n]+\n              { 
                        /* Line of Rest (valid instruction) */
                        if (pass == 1) {
                          line_pos++;
                        } else {
                          fprintf(out_fp, "%s", yytext);
                        }
                      }

\n                    { /* empty line - ignore */ }

%%

int yywrap()
{
    return 1;
}