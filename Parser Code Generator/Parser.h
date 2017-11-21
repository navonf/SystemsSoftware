#ifndef PARSE
#define PARSE

#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./LexicalAnalyzer.h"
// #include "./pMachine.h"
#include "./Stack.h"
// #include "./vm.h"
#include "./CodeGenerator.h"

#define CODE_SIZE 1000


// code array
// instruction code[500];

//Recommended data structure for the symbol.
typedef struct {
	int kind; 		  // const = 1, var = 2, proc = 3
	char name[12];	// name up to 11 chars
	int val; 		    // number (ASCII value)
	int level; 		  // L level
	int addr; 		  // M address
} symbol;

void parse(instruction* code, listy* lst, FILE* ofp);
void error (int recovery, int n);
void block(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp);
void constDeclaration(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp);
void varDeclaration(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp);
void procDeclaration(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp);
void statement(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp);
void expression(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp);
void condition(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp);
void term(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp);
void factor(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp);
void gen(instruction* code, int op, int r, int l, int m, FILE* ofp);
int position(char* id, symbol* table, int tx);

#endif
