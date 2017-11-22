#ifndef VM
#define VM

// Navon Francis
// P machine (VM)
// Euripides Montagne
// 9/29/2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants
#define MAX_STACK_VM_HEIGHT 2000
#define MAX_CODE_VM_LENGTH 500
#define MAX_LEXI_LEVELS 3

typedef struct {
  int op; // Op code_vm
  int r;  // Register
  int l;  // L
  int m;  // M
} instruct;

// PM/0 Initial/Default Values:
int sp = 0;      // stack_vm pointer
int bp = 1;      // base pointer
int pc = 0;      // program counter
int rf[8];       // register file
instruct ir;  // instruct register

// Length of code_vm
int code_vmLen = 0;

// stack_vm
int stack_vm[MAX_STACK_VM_HEIGHT];

// Lex
int lex[MAX_LEXI_LEVELS];

// code_vm array
instruct code_vm[MAX_CODE_VM_LENGTH];

// Halt flag
int halt = 0;

// Function definitions

int start();
void pMachine();
void fetchCycle();
void executeCycle();
int base(int l, int base);


#endif
