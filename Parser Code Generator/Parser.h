#ifndef PARSE
#define PARSE

#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./LexicalAnalyzer.h"
#include "./pMachine.h"
#include "./CodeGenerator.h"


// typedef struct {
//   int op; // Op code
//   int r;  // Register
//   int l;  // L
//   int m;  // M
// } instruction;

//Recommended data structure for the symbol.
typedef struct {
	int kind; 		  // const = 1, var = 2, proc = 3
	char name[12];	// name up to 11 chars
	int val; 		    // number (ASCII value)
	int level; 		  // L level
	int addr; 		  // M address
} symbol;

// code array
instruction codee[500];

void parse(listy lst, int* reg, instruction* code);
void error (int recovery, int n);
void block(listy lst, int* reg, instruction* code, symbol* table);
void constDeclaration(listy lst, int* reg, instruction* code, symbol* table);
void varDeclaration(listy lst, int* reg, instruction* code, int* addrPos, symbol* table);
void procDeclaration(listy lst, int* reg, instruction* code, symbol* table);

#endif
