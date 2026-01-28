#include "generator.h"
#include "../ast/ast.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define STACK_DATA_START_ADDR 4096
#define STACK_MEM_START_ADDR 4122

int registerPtr = 0;

reg_index codeGen(struct tnode *t, FILE *fp, int entryLabel, int exitLabel);
void generateExitCode(FILE *fp);
reg_index generateOpCode(struct tnode *t, FILE *fp, reg_index leftReg,
                         reg_index rightReg);
void generateAssgCode(struct tnode *t, FILE *fp, reg_index regToSave);
void generateReadCode(struct tnode *t, FILE *fp);
void generateWriteCode(struct tnode *t, FILE *fp, reg_index regToPrint);
void generateWhileCode(struct tnode *t, FILE *fp);
void generateIfCode(struct tnode *t, FILE *fp, int entryLabel, int exitLabel);
void generateIfElseCode(struct tnode *t, FILE *fp, int entryLabel, int exitLabel);

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

int getMemoryLocation(char *varname) {
  return STACK_DATA_START_ADDR + varname[0] - 'a';
}

int startCodeGen(struct tnode *t, FILE *fp) {

  // Initialize ABI
  fprintf(fp, "0\n2056\n0\n0\n0\n0\n0\n0\n");

  // Set stack after the reserved static data allocated location
  fprintf(fp, "MOV SP, %d\n", STACK_MEM_START_ADDR - 1);

  codeGen(t, fp, -1, -1);

  // Gracefully Terminate using Exit Call
  generateExitCode(fp);

  return 0;
}

reg_index codeGen(struct tnode *t, FILE *fp, int entryLabel, int exitLabel) {
  if (t == NULL) {
    return -1;
  }

  switch (t->nodetype) {
  case CONST_NODE: {
    // LEAF Node
    reg_index reg = getReg();
    fprintf(fp, "MOV R%d, %d\n", reg, t->val);
    return reg;
  }
  case VAR_NODE: {
    // Leaf Node
    reg_index reg = getReg();
    int mem_location = getMemoryLocation(t->varname);
    fprintf(fp, "MOV R%d, [%d]\n", reg, mem_location);
    return reg;
  }
  case READ_NODE:
    generateReadCode(t, fp);
    return -1;
  case WRITE_NODE: {
    reg_index leftReg = codeGen(t->left, fp, entryLabel, exitLabel);
    generateWriteCode(t, fp, leftReg);
    freeReg();
    return -1;
  }
  case CONN_NODE:
    codeGen(t->left, fp, entryLabel, exitLabel);
    codeGen(t->right, fp, entryLabel, exitLabel);
    return -1;
  case ASSG_NODE: {
    reg_index rightReg = codeGen(t->right, fp, entryLabel, exitLabel);
    generateAssgCode(t, fp, rightReg);
    freeReg();
    return -1;
  }
  case OP_NODE: {
    reg_index leftReg = codeGen(t->left, fp, entryLabel, exitLabel);
    reg_index rightReg = codeGen(t->right, fp, entryLabel, exitLabel);
    leftReg = generateOpCode(t, fp, leftReg, rightReg);
    freeReg();
    return leftReg;
  }
  case WHILE_NODE: {
    generateWhileCode(t, fp);
    return -1;
  }
  case IF_NODE: {
    generateIfCode(t, fp, entryLabel, exitLabel);
    return -1;
  }
  case IFELSE_NODE: {
    generateIfElseCode(t, fp, entryLabel, exitLabel);
    return -1;
  }
  case BREAK_NODE: {
    // Leaf node
    if (exitLabel != -1)
      fprintf(fp, "JMP L%d\n", exitLabel);
    return -1;
  }
  case CONTINUE_NODE: {
    if (entryLabel != -1)
      fprintf(fp, "JMP L%d\n", entryLabel);
  }
  default:
    return -1;
  }
}

void generateExitCode(FILE *fp) {
  reg_index reg = getReg();

  fprintf(fp, "MOV R%d, \"Exit\"\n", reg);
  for (int i = 0; i < 5; i++) {
    fprintf(fp, "PUSH R%d\n", reg);
  }
  fprintf(fp, "CALL 0\n");

  freeReg();
}

reg_index generateOpCode(struct tnode *t, FILE *fp, reg_index leftReg,
                         reg_index rightReg) {
  assert(t && t->nodetype == OP_NODE);

  if (strcmp(t->varname, "+") == 0) {
    fprintf(fp, "ADD R%d, R%d\n", leftReg, rightReg);
  } else if (strcmp(t->varname, "-") == 0) {
    fprintf(fp, "SUB R%d, R%d\n", leftReg, rightReg);
  } else if (strcmp(t->varname, "*") == 0) {
    fprintf(fp, "MUL R%d, R%d\n", leftReg, rightReg);
  } else if (strcmp(t->varname, "/") == 0) {
    fprintf(fp, "DIV R%d, R%d\n", leftReg, rightReg);
  } else if (strcmp(t->varname, ">=") == 0) {
    fprintf(fp, "GE R%d, R%d\n", leftReg, rightReg);
  } else if (strcmp(t->varname, ">") == 0) {
    fprintf(fp, "GT R%d, R%d\n", leftReg, rightReg);
  } else if (strcmp(t->varname, "<=") == 0) {
    fprintf(fp, "LE R%d, R%d\n", leftReg, rightReg);
  } else if (strcmp(t->varname, "<") == 0) {
    fprintf(fp, "LT R%d, R%d\n", leftReg, rightReg);
  } else if (strcmp(t->varname, "==") == 0) {
    fprintf(fp, "EQ R%d, R%d\n", leftReg, rightReg);
  } else if (strcmp(t->varname, "!=") == 0) {
    fprintf(fp, "NE R%d, R%d\n", leftReg, rightReg);
  } else {
    fprintf(stderr, "Unknown operator: %s\n", t->varname);
    assert(0);
  }

  return leftReg;
}

void generateAssgCode(struct tnode *t, FILE *fp, reg_index regToSave) {
  assert(t && t->left && t->left->nodetype == VAR_NODE);

  char *varname = t->left->varname;
  int mem_location = getMemoryLocation(varname);

  // Mov value in rightReg to memory
  fprintf(fp, "MOV [%d], R%d\n", mem_location, regToSave);
}

void generateReadCode(struct tnode *t, FILE *fp) {
  assert(t != NULL);
  assert(t->nodetype == READ_NODE);
  assert(t->left != NULL);
  assert(t->left->nodetype == VAR_NODE);

  char *varname = t->left->varname;
  int mem_location = getMemoryLocation(varname);

  reg_index reg = getReg();

  // Push 1st Argument "Read"
  fprintf(fp, "MOV R%d, \"Read\"\n", reg);
  fprintf(fp, "PUSH R%d\n", reg);

  // Push 2nd Argument -1
  fprintf(fp, "MOV R%d, -1\n", reg);
  fprintf(fp, "PUSH R%d\n", reg);

  // Push 3rd Argument memory location on stack to store the input
  fprintf(fp, "MOV R%d, %d\n", reg, mem_location);
  fprintf(fp, "PUSH R%d\n", reg);

  // Push 4th, 5th Args (Irrelevant)
  fprintf(fp, "PUSH R%d\n", reg);
  fprintf(fp, "PUSH R%d\n", reg);

  // Call the Library
  fprintf(fp, "CALL 0\n");

  // POP all 5 argument from stack
  for (int i = 0; i < 5; i++) {
    fprintf(fp, "POP R%d\n", reg);
  }

  freeReg();
}

void generateWriteCode(struct tnode *t, FILE *fp, reg_index regToPrint) {
  assert(t != NULL);
  assert(t->nodetype == WRITE_NODE);
  assert(t->left != NULL);

  reg_index reg = getReg();

  // Push 1st Argument "Write"
  fprintf(fp, "MOV R%d, \"Write\"\n", reg);
  fprintf(fp, "PUSH R%d\n", reg);

  // Push 2nd Argument -2
  fprintf(fp, "MOV R%d, -2\n", reg);
  fprintf(fp, "PUSH R%d\n", reg);

  // Push 3rd Argument: value to print
  fprintf(fp, "PUSH R%d\n", regToPrint);

  // Push 4th, 5th Args (Irrelevent)
  fprintf(fp, "PUSH R%d\n", reg);
  fprintf(fp, "PUSH R%d\n", reg);

  // Call the Library
  fprintf(fp, "CALL 0\n");

  // POP all 5 argument from stack
  for (int i = 0; i < 5; i++) {
    fprintf(fp, "POP R%d\n", reg);
  }

  freeReg();
}

int label = 0;

int getLabel() { return label++; }

void generateWhileCode(struct tnode *t, FILE *fp) {
  assert(t != NULL);
  assert(t->nodetype == WHILE_NODE);
  assert(t->left != NULL);

  int label_startwhile = getLabel();
  int label_endwhile = getLabel();

  // start the label for while loop
  fprintf(fp, "L%d:\n", label_startwhile);

  // compute the condition
  reg_index conditionReg = codeGen(t->left, fp, -1, -1);

  // Jump to label_endwhile if condition is false
  fprintf(fp, "JZ R%d, L%d\n", conditionReg, label_endwhile);

  // code for stmt list inside the while block
  codeGen(t->right, fp, label_startwhile, label_endwhile);

  // Jump back to label_startwhile as one iteration of the loop is over
  fprintf(fp, "JMP L%d\n", label_startwhile);

  // Print label_endwhile as the above line marks the end of the loop
  fprintf(fp, "L%d:\n", label_endwhile);
}

void generateIfCode(struct tnode *t, FILE *fp, int entryLabel, int exitLabel) {
  assert(t != NULL);
  assert(t->nodetype == IF_NODE);
  assert(t->left != NULL);

  int label_endif = getLabel();

  // compute the condition
  reg_index conditionReg = codeGen(t->left, fp, -1, -1);

  // Jump to label_endif, if the condition is false
  fprintf(fp, "JZ R%d, L%d\n", conditionReg, label_endif);

  // code for stmt list inside the if block
  codeGen(t->right, fp, entryLabel, exitLabel);

  // Print label_endif as the above line marks the end of the block
  fprintf(fp, "L%d:\n", label_endif);
}

void generateIfElseCode(struct tnode *t, FILE *fp, int entryLabel, int exitLabel) {
  assert(t != NULL);
  assert(t->nodetype == IFELSE_NODE);
  assert(t->left != NULL);

  int label_else = getLabel();
  int label_endif = getLabel();

  // compute the condition
  reg_index conditionReg = codeGen(t->left, fp, -1, -1);

  // Jump to label_else, if the condition is false
  fprintf(fp, "JZ R%d, L%d\n", conditionReg, label_else);

  // code for stmt list inside the if block
  codeGen(t->mid, fp, entryLabel, exitLabel);

  // Jump directly to label_endif, bcz else block should be skipped
  fprintf(fp, "JMP L%d\n", label_endif);

  // Print label_else, bcz the else block starts here
  fprintf(fp, "L%d:\n", label_else);

  // code for stmt list inside the else block
  codeGen(t->right, fp, entryLabel, exitLabel);

  // Print label_endif, as it is the end if the whole if-else block
  fprintf(fp, "L%d:\n", label_endif);
}