#ifndef GENERATOR_H
#define GENERATOR_H

#include "ast/ast.h"
#include "exprtree/exprtree.h"
#include <stdio.h>

// Registers
#define reg_index int

// Code generation
reg_index startCodeGen(struct tnode *t, FILE *fp);

#endif /* GENERATOR_H */