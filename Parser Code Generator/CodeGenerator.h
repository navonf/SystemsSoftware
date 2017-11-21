#ifndef GEN
#define GEN

#include "Stack.h"

typedef struct memory {
	int op; // OP code
	int r;  // reg
	int l;  // L
	int m;  // M
} mem;

// this wrapper array keeps track of the codeSize, we will need in Parser.c
typedef struct {
	mem memArr[1000];
	int codeSize;
} instruction;

#endif
