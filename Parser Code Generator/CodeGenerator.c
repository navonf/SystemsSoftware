// Navon Francis
// Code Generator
// Euripides Montagne
// 11/03/2017
#include "CodeGenerator.h"


// implementation with registers
void emit(int opr, int l, int m, stack* stacky, instruction* code) {

  // pass in opr to execute code gen
	switch(opr) {
      // LIT
      case 01:
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = l;
				code->memArr[code->codeSize].m = m;
				code->memArr[code->codeSize].r = stacky->height;
				stackPush(stacky->height, stacky);
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
				code->memArr[code->codeSize].r = stacky->height;
				stackPush(stacky->height, stacky);
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

			// INC
			case 06:
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
				if(code->memArr[code->codeSize].m == 1){
					code->memArr[code->codeSize].op = opr;
					code->memArr[code->codeSize].op = m;
					stackPop(stacky);
					code->memArr[code->codeSize].r = stacky->height;
					stackPush(stacky->height, stacky);
					break;
				}
				else if(code->memArr[code->codeSize].m == 2){
					code->memArr[code->codeSize].op = opr;
					code->memArr[code->codeSize].m = m;
					stackPop(stacky);
					code->memArr[code->codeSize].r  = stacky->height;
					stackPush(stacky->height, stacky);
					break;
				}
				else {
					code->memArr[code->codeSize].op = opr;
					code->memArr[code->codeSize].m = m;
					break;
				}

			case 10:
				// NEG
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stackPop(stacky);
				code->memArr[code->codeSize].r = stacky->height;
				stackPush(stacky->height, stacky);
				break;

			case 11:
				// ADD
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->height-1;
				code->memArr[code->codeSize].m = stacky->height;
				code->memArr[code->codeSize].r = stacky->height-1;
			    break;

			case 12:
				// SUB
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->height-1;
				code->memArr[code->codeSize].m = stacky->height;
				code->memArr[code->codeSize].r = stacky->height-1;
				break;

			case 13:
				// MUL
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->height-1;
				code->memArr[code->codeSize].m = stacky->height;
				code->memArr[code->codeSize].r = stacky->height-1;
				break;

			case 14:
				// Div
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->height-1;
				code->memArr[code->codeSize].m = stacky->height;
				code->memArr[code->codeSize].r = stacky->height-1;
				break;

			case 15:
				// ODD
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].r = stackPop(stacky);
				stackPush(stacky->height, stacky);
	 			break;

	 		case 16:
	 			// MOD
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->height-1;
				code->memArr[code->codeSize].m = stacky->height;
				code->memArr[code->codeSize].r = stacky->height-1;
	 			break;

	 		case 17:
	 			// EQL
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->height-1;
				code->memArr[code->codeSize].m = stacky->height;
				code->memArr[code->codeSize].r = stacky->height-1;
	 			break;

	 		case 18:
	 			// NEQ
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->height-1;
				code->memArr[code->codeSize].m = stacky->height;
				code->memArr[code->codeSize].r = stacky->height-1;
	 			break;

	 		case 19:
	 			// LSS
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->height-1;
				code->memArr[code->codeSize].m = stacky->height;
				code->memArr[code->codeSize].r = stacky->height-1;
	 			break;

	 		case 20:
	 			// LEQ
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->height-1;
				code->memArr[code->codeSize].m = stacky->height;
				code->memArr[code->codeSize].r = stacky->height-1;
	 			break;

	 		case 21:
	 			// GTR
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->height-1;
				code->memArr[code->codeSize].m = stacky->height;
				code->memArr[code->codeSize].r = stacky->height-1;
	 			break;

	 		case 22:
	 			// GEQ
				stackPop(stacky);
				code->memArr[code->codeSize].op = opr;
				code->memArr[code->codeSize].l = stacky->height-1;
				code->memArr[code->codeSize].m = stacky->height;
				code->memArr[code->codeSize].r = stacky->height-1;
	 			break;
	}
	code->codeSize++;
}
