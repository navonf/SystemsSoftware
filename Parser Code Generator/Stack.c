// Navon Francis
// Stack of Integers

#include "Stack.h"

stack* stackInit() {
  // create the space for our stack
  stack* stacky = (stack*)malloc(sizeof(stack));

  // make our head start at NULL
  stacky->head = NULL;

  // init size
  stacky->size = 0;

  return stacky;
}

// push an integer onto the stack
void stackPush(int number, stack* stacky) {
  // allocate space for a new node on the stack
  record* node = (record*)malloc(sizeof(record));


  // store our number in the stack
	node->value = number;
	node->next = stacky->head;

  // set that as the new head, LIFO - Last in first out
	stacky->head = node;

  // increment our size
	stacky->height++;
}

// remove from the stop of our stack
int stackPop(stack* stacky) {
  int poppedVal = stacky->head->val;

  // grab the node to free it
	record* node = stacky->head;

  // fix our pointers
	stacky->head = stacky->head->next;

	free(node);
	stacky->height--;

	return poppedVal;
}
