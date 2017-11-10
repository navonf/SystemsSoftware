#ifndef GEN
#define GEN


#include "Stack.h"
#include "pMachine.h"

typedef struct memory {
	int op; // OP code
	int r;  // reg
	int l;  // L
	int m;  // M
} mem;

// this wrapper array keeps track of the codeSize, we will need in Parser.c
typedef struct {
	mem memArr[MAX_CODE_LENGTH];
	int codeSize;
} instruction;

void emit(int opr, int l, int m, stack* stacky, instruction* code);

#endif
