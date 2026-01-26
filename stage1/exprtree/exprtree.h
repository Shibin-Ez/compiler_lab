#ifndef EXPRTREE_H
#define EXPRTREE_H

#include <stdio.h>
typedef struct tnode {
  int val;                    // value of the expression tree
  char *op;                   // indicates the opertor
  struct tnode *left, *right; // left and right branches
} tnode;

/*Make a leaf tnode and set the value of val field*/
struct tnode *makeLeafNode(int n);

/*Make a tnode with opertor, left and right branches set*/
struct tnode *makeOperatorNode(char c, struct tnode *l, struct tnode *r);

/*To evaluate an expression tree*/
int evaluate(struct tnode *t, FILE *fp);

// Registers
#define reg_index int
int getReg();
void freeReg();
reg_index codeGen(struct tnode *t, FILE *fp);

#endif /* EXPRTREE_H */