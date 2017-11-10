// Navon Francis
// P machine (VM)
// Euripides Montagne
// 9/29/2017

#include "./pMachine.h"



typedef struct {
  int op; // Op codee
  int r;  // Register
  int l;  // L
  int m;  // M
} instruc;

// codee array
instruc codee[MAX_CODE_LENGTH];

instruc ir;  // instruc register



// Stack
int stack[MAX_STACK_HEIGHT];

// Lex
int lex[MAX_LEXI_LEVELS];

int halt = 0;

// PM/0 Initial/Default Values:
int sp = 0;      // stack pointer
int bp = 1;      // base pointer
int pc = 0;      // program counter
int rf[8];       // register file

// Length of codee
int codeeLen = 0;

// Enter the virtual machine
void pMachine() {

  FILE *ifp, *ofp;
  ifp = fopen("parse.txt", "r");

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


    // Put the values in our codee
    codee[len].op = op;
    codee[len].r = r;
		codee[len].l = l;
		codee[len].m = m;

    len++;

    if(len > 1000) break;
  }
  codeeLen = len;
  fclose(ifp);

  printf("Stack trace:\nInitial Values\t\t\t\tpc\tbp\tsp\n");

  int ii = 0;
  // Enter while loop for each instruc
  while(halt != 1) {
    ii++;
    if(ii > 1000) break;
    // Print PC
    printf("%d\t", pc);

    // Enter fetch cycle
    fetchCycle();
    // Enter execute cycle
    executeCycle();

    printf("%d\t%d\t%d\t%d\t%d\t%d\t",
    ir.r, ir.l, ir.m, pc, bp, sp);

    int i;
    int flag = 0;
    for(i = 1; i<=sp; i++) {
      if(i == 7 && sp > 7) {
				printf("| ");
        flag = 1;
      }
      if(i == 11 && sp > 11 && flag == 1) {
				printf("| ");
      }
      printf("%d ", stack[i]);
    }

    printf("\n");
  }

  printf("\nOutput:\n%d\n", rf[0]);
}

// Run the Fetch Cycle:
// Put values in instruc register,
// and increment PC.
void fetchCycle() {
	ir.op = codee[pc].op;
	ir.r = codee[pc].r;
	ir.l = codee[pc].l;
	ir.m = codee[pc].m;

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
      // Generate a new activation record
      printf("CAL\t");
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
        // printf("%d", rf[ir.r]);
        printf("SIO\t");
      }
      else if(ir.m == 2) {
        scanf("%d", &rf[ir.r]);
        printf("SIO\t");
      }
      else {
        halt = 1;
        pc = 0;
        sp = 0;
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

  while (l > 0)
  {
    b1 = stack[b1 + 1];
    l--;
  }

  return b1;
}
