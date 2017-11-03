#ifndef GEN
#define GEN

#define MAX_CODE_LENGTH 500

#include "Stack.h"

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

void emit(int opr, int l, int m, stack* s, instruction* code);


#endif
