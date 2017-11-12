// Navon Francis
// Compiler Driver
// Euripides Montagne
// 11/03/2017

#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./Parser.h"

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
int startVM();
int base(int l, int base);
void pMachine();
void fetchCycle();
void executeCycle();
void printSymbols(int num);


int main(int argc, char* argv[]) {

  // flags for each case
  int cmd;
  int runLexer = 0;
  int runVM = 0;
  int runParser = 0;

  listy myListy = lexy();
  instruction code;

  while( (cmd = getopt(argc, argv, "lav")) != 1) {
    if(cmd == 'l') {
      runLexer = 1;
    }
    else if(cmd == 'a') {
      runParser = 1;
    }
    else if(cmd == 'v') {
      runVM = 1;
    }
    else {
      break;
    }

  }

  printf("in:\n");
  if(runLexer == 1) {

    printf("Lexeme List:\n");
    int i = 0;

    for(i = 0; i < myListy.size; i++) {
      if(myListy.list[i].type == 2) {
        printf("%d ", myListy.list[i].lex);
        printf("%s ", myListy.list[i].words);
      }
      else if(myListy.list[i].type == 1) {
        printf("%d ", myListy.list[i].lex);
        printf("%s ", myListy.list[i].words);
      }
      else {
        printf("%d ", myListy.list[i].lex);
      }
    }

    printf("\nSymbols:\n");

    for(i = 0; i < myListy.size; i++) {
      if(myListy.list[i].type == 2) {
        printSymbols(myListy.list[i].lex);
        printf("%s ", myListy.list[i].words);
      }
      else if(myListy.list[i].type == 1) {
        printSymbols(myListy.list[i].lex);
        printf("%s ", myListy.list[i].words);
      }
      else {
        printSymbols(myListy.list[i].lex);
      }
    }
    printf("\n\n");
  }


  printf("\nout:\n");
  if(runParser == 1) {
    parse(&code, &myListy);

    FILE* ofp = fopen("parse.txt", "w");

    int i;
    for (i = 0; i < code.codeSize; i++) {
      fprintf(ofp, "%d %d %d %d \n", code.memArr[i].op,code.memArr[i].r,code.memArr[i].l,code.memArr[i].m);
    }

    for (i = 0; i < code.codeSize; i++) {
      printf("%d %d %d %d \n", code.memArr[i].op,code.memArr[i].r,code.memArr[i].l,code.memArr[i].m);
    }

    fclose(ofp);
  }

  if(runVM == 1) {
    startVM();
  }


  return 0;
}

void printSymbols(int num) {
  if(num == 1) {
    printf("nulsym ");
  }
  else if(num == 2) {
    printf("identsym ");

  }
  else if(num == 3) {
    printf("numbersym ");

  }
  else if(num == 4) {
    printf("plussym ");

  }
  else if(num == 5) {
    printf("minussym ");

  }
  else if(num == 6) {
    printf("multsym ");
  }
  else if(num == 7) {
    printf("slashsym ");
  }
  else if(num == 8) {
    printf("oddsym ");
  }
  else if(num == 9) {
    printf("eqlsym ");
  }
  else if(num == 10) {
    printf("neqsym ");
  }
  else if(num == 11) {
    printf("lessym ");
  }
  else if(num == 12) {
    printf("leqsym ");
  }
  else if(num == 13) {
    printf("gtrsym ");
  }
  else if(num == 14) {
    printf("geqsym ");
  }
  else if(num == 15) {
    printf("lparentsym ");
  }
  else if(num == 16) {
    printf("rparentsym ");
  }
  else if(num == 17) {
    printf("commasym ");
  }
  else if(num == 18) {
    printf("semicolonsym ");
  }
  else if(num == 19) {
    printf("periodsym ");
  }
  else if(num == 20) {
    printf("becomessym ");
  }
  else if(num == 21) {
    printf("beginsym ");
  }
  else if(num == 22) {
    printf("endsym ");
  }
  else if(num == 23) {
    printf("ifsym ");
  }
  else if(num == 24) {
    printf("thensym ");
  }
  else if(num == 25) {
    printf("whilesym ");
  }
  else if(num == 26) {
    printf("dosym ");
  }
  else if(num == 27) {
    printf("callsym ");
  }
  else if(num == 28) {
    printf("constsym ");
  }
  else if(num == 29) {
    printf("intsym ");
  }
  else if(num == 30) {
    printf("procsym ");
  }
  else if(num == 31) {
    printf("writesym ");
  }
  else if(num == 32) {
    printf("readsym ");
  }
  else if(num == 33) {
    printf("elsesym ");
  }
 }

 // Wasn't working with the import, getting a weird duplicate symbol error.
 // dropped VM code in the CompilerDriver.c
 int startVM() {
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

     // Put the values in our code_vm
     code_vm[len].op = op;
     code_vm[len].r = r;
 		code_vm[len].l = l;
 		code_vm[len].m = m;

     len++;
   }

   code_vmLen = len;
   pMachine();

   return 0;
 }

 // Enter the virtual machine
 void pMachine() {
   printf("stack_vm trace:\nInitial Values\t\t\t\tpc\tbp\tsp\n");

   // Enter while loop for each instruct
   while(halt != 1) {

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
       printf("%d ", stack_vm[i]);
     }

     if(ir.op == 9) {

     }

     printf("\n");
   }

   printf("\nOutput:\n%d\n", rf[0]);
 }

 // Run the Fetch Cycle:
 // Put values in instruct register,
 // and increment PC.
 void fetchCycle() {
 	ir.op = code_vm[pc].op;
 	ir.r = code_vm[pc].r;
 	ir.l = code_vm[pc].l;
 	ir.m = code_vm[pc].m;

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
       bp = stack_vm[sp + 3];
       pc = stack_vm[sp + 4];
       printf("RTN\t");
       break;

     case 3:
       rf[ir.r] = stack_vm[base(ir.l, bp) + ir.m];
       printf("LOD\t");
       break;

     case 4:
       stack_vm[base(ir.l, bp) + ir.m] = rf[ir.r];
       printf("STO\t");
       break;

     case 5:
       stack_vm[sp + 1] = 0;			        // space to return value
       stack_vm[sp + 2] = base(ir.l, bp); // static link (SL)
       stack_vm[sp + 3] = bp;			        // dynamic link (DL)
       stack_vm[sp + 4] = pc;	 		        // return address (RA)
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

   while (l > 0) {
     b1 = stack_vm[b1 + 1];
     l--;
   }

   return b1;
 }
