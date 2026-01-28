#ifndef AST_H
#define AST_H

#include <stdio.h>

#define VOID_TYPE -1
#define INT_TYPE 0
#define BOOL_TYPE 1

#define VAR_NODE 0 // Variable - Leaf
#define OP_NODE 1 // Operator 
#define CONN_NODE 2 // Connecter
#define ASSG_NODE 3 // Assignment
#define READ_NODE 4 // Read
#define WRITE_NODE 5 // Write
#define CONST_NODE 6 // Constant - Leaf
#define IF_NODE 7 // If
#define IFELSE_NODE 8 // If Else
#define WHILE_NODE 9 // While
#define BREAK_NODE 10 // Break
#define CONTINUE_NODE 11 // Continue
#define REPEAT_NODE 12 // Repeat-Until
#define DOWHILE_NODE 13 // Do-While

typedef struct tnode {
  int val;       // value of a number for NUM nodes.
  int type;      // type of variable  --(Integer only for stage2)
  char *varname; // name of a variable for ID nodes
  int nodetype;  // information about non-leaf nodes - read/write/connector/+/*
                 // etc.
  struct tnode *left, *mid, *right; // left, mid, and right branches
} tnode;

struct tnode *makeConnecterNode(struct tnode *l, struct tnode *r);
struct tnode *makeAssgNode(struct tnode *l, struct tnode *r);
struct tnode *makeReadNode(struct tnode *l);
struct tnode *makeWriteNode(struct tnode *l);
struct tnode *makeVariableLeafNode(char *c);
struct tnode *makeIfNode(struct tnode *l, struct tnode *r);
struct tnode *makeIfElseNode(struct tnode *l, struct tnode* m, struct tnode *r);
struct tnode *makeWhileNode(struct tnode *l, struct tnode *r);
struct tnode *makeBreakLeafNode();
struct tnode *makeContinueLeafNode();
struct tnode *makeRepeatNode(struct tnode *l, struct tnode *r);
struct tnode *makeDoWhileNode(struct tnode *l, struct tnode *r);

/*Create a node tnode*/
struct tnode *createTree(int val, int type, char *c, struct tnode *l,
                         struct tnode *r);


#endif