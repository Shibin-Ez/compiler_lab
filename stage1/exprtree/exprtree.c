#include "exprtree.h"
#include <stdio.h>
#include <stdlib.h>

struct tnode *makeLeafNode(int n) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->op = NULL;
  temp->val = n;
  temp->left = NULL;
  temp->right = NULL;
  return temp;
}

struct tnode *makeOperatorNode(char c, struct tnode *l, struct tnode *r) {
  struct tnode *temp;
  temp = (struct tnode *)malloc(sizeof(struct tnode));
  temp->op = malloc(sizeof(char));
  *(temp->op) = c;
  temp->left = l;
  temp->right = r;
  return temp;
}

int evaluate(struct tnode *t, FILE *fp) {
  reg_index reg = codeGen(t, fp);
  fprintf(fp, "PUSH R%d\n", reg);

  return 0;
}

int registerPtr = 0;

int getReg() {
  if (registerPtr < 20) {
    return registerPtr++;
  }

  // All registers in use
  return -1;
}

void freeReg() {
  if (registerPtr > 0) {
    registerPtr--;
  }
}

#define reg_index int
reg_index codeGen(struct tnode *t, FILE *fp) {
  if (t == NULL) {
    return -1;
  }

  if (t->op == NULL) {
    reg_index reg = getReg();
    fprintf(fp, "MOV R%d %d\n", reg, t->val);
    return reg;
  }

  reg_index leftReg = codeGen(t->left, fp);
  reg_index rightReg = codeGen(t->right, fp);

  if (leftReg == -1 || rightReg == -1) {
    return -1;
  }

  switch (*(t->op)) {
  case '+':
    fprintf(fp, "ADD R%d, R%d\n", leftReg, rightReg);
    break;
  case '-':
    fprintf(fp, "SUB R%d, R%d\n", leftReg, rightReg);
    break;
  case '*':
    fprintf(fp, "MUL R%d, R%d\n", leftReg, rightReg);
    break;
  case '/':
    fprintf(fp, "DIV R%d, R%d\n", leftReg, rightReg);
    break;
  }

  freeReg();
  return leftReg;
}