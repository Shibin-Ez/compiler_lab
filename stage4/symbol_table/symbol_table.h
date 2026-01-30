#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

struct Gsymbol {
  char* name;       // name of the variable
  int type;         // type of the variable
  int size;         // size of the type of the variable
  int binding;      // stores the static memory address allocated to the variable
  struct Gsymbol *next;
};

// Forward declaration of struct tnode (defined in ast.h)
struct tnode;

// Builds Global Symbol table from AST
int buildSymbolTable(struct tnode *t, int var_type);

void printSymbolTable();

struct Gsymbol *Lookup(char * name);            // Returns a pointer to the symbol table entry for the variable, returns NULL otherwise.
void Install(char *name, int type, int size);   // Creates a symbol table entry.

#endif /* SYMBOL_TABLE_H */
