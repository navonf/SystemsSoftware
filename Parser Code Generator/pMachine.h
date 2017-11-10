#ifndef VM
#define VM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Constants
#define MAX_STACK_HEIGHT 2000
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

// Function definitions
void pMachine();
void fetchCycle();
void executeCycle();
int base(int l, int base);

#endif
