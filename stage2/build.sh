#!/bin/bash
cd ast && lex ast.l && yacc -d ast.y && cd ..
gcc -Wall ast/y.tab.c ast/lex.yy.c ast/ast.c exprtree/exprtree.c generator.c -o compiler