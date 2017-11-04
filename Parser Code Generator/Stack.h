// Navon Francis
// Stack of Integers

#ifndef STACK
#define STACK

#include <stdlib.h>
#include <stdio.h>
// each individual record in the stack, using a next pointer to iterate
typedef struct record {
  int val;
  struct record* next;
} record;

// wrapper for the stack, keeping track of height
typedef struct stack {
	record* head;
	int height;
} stack;

stack* stackInit();
void stackPush(int number, stack* stacky);
int stackPop(stack* stacky);

#endif
