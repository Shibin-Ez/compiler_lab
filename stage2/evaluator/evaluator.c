#include "evaluator.h"
#include "../ast/ast.h"
#include <stdio.h>

int memory[26] = {0};

int getMemoryLocation(char *varname) { return varname[0] - 'a'; }

int operate(int a, int b, char *op) {
  switch (op[0]) {
    case '+' : return a + b;
    case '-' : return a - b;
    case '*' : return a * b;
    case '/' : return a / b;
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
  default:
    return -1;
  }
}