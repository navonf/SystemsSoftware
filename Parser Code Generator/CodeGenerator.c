// Navon Francis
// Code Generator
// Euripides Montagne
// 11/03/2017
#include "CodeGenerator.h"

void emit(int opr, int l, int m, stack* stacky, instruction* code) {

  // pass in opr to execute code Generator
	switch (opr) {
      // LIT
      case 01:
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = l;
				code->memArr[code->codeSize].m = m;
				code->memArr[code->codeSize].r = stacky->size;
				stackPush(stacky->size, stacky);
				break;

      // RTN
			case 02:
				code->memArr[code->codeSize].op = opr;
				break;

      // LOD
			case 03:
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = l;
				code->memArr[code->codeSize].m = m;
				code->memArr[code->codeSize].r = stacky->size;
				stackPush(stacky->size, stacky);
				break;

      // STO
			case 04:
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = l;
				code->memArr[code->codeSize].m = m;
				code->memArr[code->codeSize].r = stackPop(stacky);
				break;

      // CAL
			case 05:
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].m = m;
				code->memArr[code->codeSize].l = l;
				break;

			case 06:
				// INC
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].m = m;
				code->memArr[code->codeSize].l = l;
				break;

			case 07:
				// JMP
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = l;
				code->memArr[code->codeSize].m = m;
				break;

			case 8:
				// JPC
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = l;
				code->memArr[code->codeSize].m = m;
				code->memArr[code->codeSize].r = stackPop(stacky);
				break;

			case 9:
				// SIO Write
				code->memArr[code->codeSize].op = opr;
				stackPop(stacky);
				code->memArr[code->codeSize].r  = stacky->size;
				stackPush(stacky->size, stacky);
				break;

			case 10:
				// SIO Read
				code->memArr[code->codeSize].op = opr;
				stackPop(stacky);
				code->memArr[code->codeSize].r  = stacky->size;
				stackPush(stacky->size, stacky);
				break;

			case 11:
				// SIO Halt
				code->memArr[code->codeSize].op = opr;
				break;

			case 12:
				// NEG
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stackPop(stacky);
				code->memArr[code->codeSize].r = stacky->size;
				stackPush(stacky->size, stacky);
				break;

			case 13:
				// ADD
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->size-1;
				code->memArr[code->codeSize].m = stacky->size;
				code->memArr[code->codeSize].r = stacky->size-1;
			    break;

			case 14:
				// SUB
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->size-1;
				code->memArr[code->codeSize].m = stacky->size;
				code->memArr[code->codeSize].r = stacky->size-1;
				break;

			case 15:
				// MUL
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->size-1;
				code->memArr[code->codeSize].m = stacky->size;
				code->memArr[code->codeSize].r = stacky->size-1;
				break;

			case 16:
				// Div
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->size-1;
				code->memArr[code->codeSize].m = stacky->size;
				code->memArr[code->codeSize].r = stacky->size-1;
				break;

			case 17:
				// ODD
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].r = stackPop(stacky);
				stackPush(stacky->size, stacky);
	 			break;

	 		case 18:
	 			// MOD
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->size-1;
				code->memArr[code->codeSize].m = stacky->size;
				code->memArr[code->codeSize].r = stacky->size-1;
	 			break;

	 		case 19:
	 			// EQL
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->size-1;
				code->memArr[code->codeSize].m = stacky->size;
				code->memArr[code->codeSize].r = stacky->size-1;
	 			break;

	 		case 20:
	 			// NEQ
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->size-1;
				code->memArr[code->codeSize].m = stacky->size;
				code->memArr[code->codeSize].r = stacky->size-1;
	 			break;

	 		case 21:
	 			// LSS
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->size-1;
				code->memArr[code->codeSize].m = stacky->size;
				code->memArr[code->codeSize].r = stacky->size-1;
	 			break;

	 		case 22:
	 			// LEQ
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->size-1;
				code->memArr[code->codeSize].m = stacky->size;
				code->memArr[code->codeSize].r = stacky->size-1;
	 			break;

	 		case 23:
	 			// GTR
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->size-1;
				code->memArr[code->codeSize].m = stacky->size;
				code->memArr[code->codeSize].r = stacky->size-1;
	 			break;

	 		case 24:
	 			// GEQ
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->size-1;
				code->memArr[code->codeSize].m = stacky->size;
				code->memArr[code->codeSize].r = stacky->size-1;
	 			break;
	}
	code->codeSize++;
}