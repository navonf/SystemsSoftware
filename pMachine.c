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
int rf[8];
instruction ir;

// Length of code
int codeLen = 0;

// Stack
int stack[MAX_STACK_HEIGHT];

// Lex
int lex[MAX_LEXI_LEVELS];

// Code array
instruction code[MAX_CODE_LENGTH];

int halt = 0;

// Function definitions
void pMachine();
void fetchCycle();
void executeCycle();
int base(int l, int base);

// Enter the virtual machine
void pMachine() {
  int i = 0;

  // Enter while loop for each instruction
  while(halt != 1) {
    i++;
    fetchCycle();
    executeCycle();

  }
}

// Scan in code
int main() {
  FILE *ifp, *ofp;
  ifp = fopen("input.txt","r");
  ofp = fopen("stacktrace.txt","w");

  int op = 0;
  int r = 0;
  int l = 0;
  int m = 0;
  int len = 0;

  while(fscanf(ifp, "%d", &op) != EOF) {
    // Read in values
    fscanf(ifp, "%d", &r);
    fscanf(ifp, "%d", &l);
    fscanf(ifp, "%d", &m);

    // Put the values in our code
    code[len].op = op;
    code[len].r = r;
		code[len].l = l;
		code[len].m = m;

    len++;
  }

  codeLen = len;

  pMachine();

  return 0;
}

// Run the Fetch Cycle:
// Put values in instruction register,
// and increment PC.
void fetchCycle() {
	ir.op = code[pc].op;
	ir.r = code[pc].r;
	ir.l = code[pc].l;
	ir.m = code[pc].m;

  pc++;
}

// Run the Execute Cycle:
void executeCycle() {

  switch(ir.op) {
    case 1:
      rf[ir.r] = ir.m;
      printf("LIT\t");
      break;

    case 2:
      sp = bp - 1;
      bp = stack[sp + 3];
      pc = stack[sp + 4];
      printf("RTN\t");
      break;

    case 3:
      rf[ir.r] = stack[base(ir.l, bp) + ir.m];
      printf("LOD\t");
      break;

    case 4:
      stack[base(ir.l, bp) + ir.m] = rf[ir.r];
      printf("STO\t");
      break;

    case 5:
      stack[sp + 1] = 0;			        // space to return value
      stack[sp + 2] = base(ir.l, bp); // static link (SL)
      stack[sp + 3] = bp;			        // dynamic link (DL)
      stack[sp + 4] = pc;	 		        // return address (RA)
      bp = sp + 1;
      pc = ir.m;
      printf("STO\n");
      break;

    case 6:
      sp = sp + ir.m;
      printf("INC\t");
      break;

    case 7:
      pc = ir.m;
      printf("JMP\t");
      break;

    case 8:
      if (rf[ir.r] == 0)
        pc = ir.m;
      printf("JPC\t");
      break;

    case 9:
      if(ir.m == 1) {
        printf("%d", rf[ir.r]);
        printf("SIO\t");
      }
      else if(ir.m == 2) {
        scanf("%d", &rf[ir.r]);
        printf("SIO\t");
      }
      else {
        halt = 1;
        printf("SIO\t");
      }
      break;

    case 10:
      rf[ir.r] = -rf[ir.l];
      printf("NEG\t");
      break;

    case 11:
      rf[ir.r] = rf[ir.l] + rf[ir.m];
      printf("ADD\t");
      break;

    case 12:
      rf[ir.r] = rf[ir.l] - rf[ir.m];
      printf("SUB\t");
      break;

    case 13:
      rf[ir.r] = rf[ir.l] * rf[ir.m];
      printf("MUL\t");
      break;

    case 14:
      rf[ir.r] = rf[ir.l] / rf[ir.m];
      printf("DIV\t");
      break;

    case 15:
      rf[ir.r] = rf[ir.r] % 2;
      printf("ODD\t");
      break;

    case 16:
      rf[ir.r] = rf[ir.l] % rf[ir.m];
      printf("MOD\t");
      break;

    case 17:
      rf[ir.r] = (rf[ir.l] == rf[ir.m]);
      printf("EQL\t");
      break;

    case 18:
      rf[ir.r] = rf[ir.l] != rf[ir.m];
      printf("NEQ\t");
      break;

    case 19:
      rf[ir.r] = rf[ir.l] < rf[ir.m];
      printf("LSS\t");
      break;

    case 20:
      rf[ir.r] = rf[ir.l] <= rf[ir.m];
      printf("LEQ\t");
      break;

    case 21:
      rf[ir.r] = rf[ir.l] > rf[ir.m];
      printf("GTR\t");
      break;

    case 22:
      rf[ir.r] = rf[ir.l] >= rf[ir.m];
      printf("GEQ\t");
      break;
  }
}

int base(int l, int base) {
  int b1; // Find base L levels down
  b1 = base;

  while (l > 0) {
    b1 = stack[b1 + 1];
    l--;
  }

  return b1;
}
