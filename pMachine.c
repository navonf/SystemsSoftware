// Navon Francis
// P machine (VM)
// Euripides Montagne
// 9/29/2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

typedef struct {
  int op; // Op code
  int r;  // Register
  int l;  // L
  int m;  // M
} instruction;

// PM/0 Initial/Default Values:
int sp = 0;
int bp = 1;
int pc = 0;
instruction ir;

// Stack
int stack[MAX_STACK_HEIGHT];

// Lex
int lex[MAX_LEXI_LEVELS];

// Code array
instruction code[MAX_CODE_LENGTH];

void pMachine(instruction *code) {

}

int main() {
  FILE* ifp, *ofp;
  ifp = fopen("input.txt","r");
  ofp = fopen("stacktrace.txt","w");
}

void fetchCycle(instruction *code, instruction *ir, int *pc) {
	ir->op = code[*pc].op;
	ir->r = code[*pc].r;
	ir->l = code[*pc].l;
	ir->m = code[*pc].m;

  *pc = *pc + 1;
}
