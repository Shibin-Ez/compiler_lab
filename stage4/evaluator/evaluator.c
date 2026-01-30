#include "evaluator.h"
#include "../ast/ast.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

int memory[26] = {0};

int getMemoryLocation(char *varname) { return varname[0] - 'a'; }

int operate(int a, int b, char *op) {
  if (strcmp(op, "+") == 0) {
    return a + b;
  } else if (strcmp(op, "-") == 0) {
    return a - b;
  } else if (strcmp(op, "*") == 0) {
    return a * b;
  } else if (strcmp(op, "/") == 0) {
    return a / b;
  } else if (strcmp(op, ">") == 0) {
    return a > b ? 1 : 0;
  } else if (strcmp(op, ">=") == 0) {
    return a >= b ? 1 : 0;
  } else if (strcmp(op, "<") == 0) {
    return a < b ? 1 : 0;
  } else if (strcmp(op, "<=") == 0) {
    return a <= b ? 1 : 0;
  } else if (strcmp(op, "==") == 0) {
    return a == b ? 1 : 0;
  } else if (strcmp(op, "!=") == 0) {
    return a != b ? 1 : 0;
  } else {
    fprintf(stderr, "Unknown operator: %s\n", op);
    assert(0);
  }
  return -1;
}

int evaluate(struct tnode *t) {
  if (t == NULL) {
    return -1;
  }

  switch (t->nodetype) {
  case CONST_NODE: {
    // LEAF Node
    return t->val;
  }
  case VAR_NODE: {
    // Leaf Node
    return memory[getMemoryLocation(t->varname)];
  }
  case READ_NODE: {
    // read input from user (from /dev/tty since lexer consumed stdin)
    int inputNum;
    FILE *tty = fopen("/dev/tty", "r");
    fscanf(tty, "%d", &inputNum);
    fclose(tty);

    // store it in memory
    int mem_location = getMemoryLocation(t->left->varname);
    memory[mem_location] = inputNum;
    return -1;
  }
  case WRITE_NODE: {
    // evaluate the expressing
    int val = evaluate(t->left);

    // print the value to console
    printf("%d\n", val);

    return -1;
  }
  case CONN_NODE:
    evaluate(t->left);
    evaluate(t->right);
    return -1;
  case ASSG_NODE: {
    // evaluate RHS
    int val = evaluate(t->right);

    // Save the value to memory
    int mem_location = getMemoryLocation(t->left->varname);
    memory[mem_location] = val;

    return -1;
  }
  case OP_NODE: {
    int leftVal = evaluate(t->left);
    int rightVal = evaluate(t->right);
    return operate(leftVal, rightVal, t->varname);
  }
  case IF_NODE: {
    int condition = evaluate(t->left);
    if (condition)
      evaluate(t->right);
  }
  case IFELSE_NODE: {
    int condition = evaluate(t->left);
    if (condition)
      evaluate(t->mid);
    else
      evaluate(t->right);
  }
  case WHILE_NODE: {
    while (evaluate(t->left) == 1) {
      evaluate(t->right);
    }
  }
  default:
    return -1;
  }
}