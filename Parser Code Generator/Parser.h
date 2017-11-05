#ifndef PARSE
#define PARSE

#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./LexicalAnalyzer.h"
#include "./pMachine.h"
#include "./Stack.h"
// #include "./CodeGenerator.h"

#define CODE_SIZE 1000

typedef struct {
  int op; // Op code
  int r;  // Register
  int l;  // L
  int m;  // M
} instruction;

// code array
instruction code[500];

//Recommended data structure for the symbol.
typedef struct {
	int kind; 		  // const = 1, var = 2, proc = 3
	char name[12];	// name up to 11 chars
	int val; 		    // number (ASCII value)
	int level; 		  // L level
	int addr; 		  // M address
} symbol;



void parse(stack* reg, instruction* code);
void error (int recovery, int n);
void block(stack* reg, instruction* code, symbol* table);
void constDeclaration(stack* reg, instruction* code, symbol* table);
void varDeclaration(stack* reg, instruction* code, symbol* table);
void procDeclaration(stack* reg, instruction* code, symbol* table);
void statement(stack* reg, instruction* code, symbol* table);
void emit(int op, int l, int m, int r, instruction* code);
void expression(stack* reg, instruction* code, symbol* table);
void condition(stack* reg, instruction* code, symbol* table);
void term(stack* reg, instruction* code, symbol* table);
void factor(stack* reg, instruction* code, symbol* table);
int position(char* id, symbol* table, int tx);

#endif
