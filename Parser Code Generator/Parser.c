// Navon Francis
// Parser
// Euripides Montagne
// 11/20/2017

#include "./Parser.h"

int tx = 1;
int cx = 0;
int correct = 0;
int lev = 1;
int dx = 4;
int regIdx = 0;
int space = 0;
int tokenVal = 0;

void parse(instruction *code, listy* lst, FILE* ofp) {
  code->codeSize = 0;
  symbol table[1000];
  stack* reg = stackInit();
  // pointers for symbol table
  int l = 0;
  int d = 0; // data index
  int t = 0; // tables index
  int i = 0;

  block(reg, code, table, lst, ofp);

  if(lst->list[lst->index].lex != periodsym) {
    error(0, 9);
  }

  gen(code, 9, 0, 0, 3, ofp);

  if(correct == 0) {
    printf("\nThe program is syntactically correct!\n");
  }

}

void block(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp) {
  space = 4;
  int jumpAddr = cx;
  int tempTableIdx = tx;
  lev++;


  gen(code, 7, 0, 0, 0, ofp);

  if(lst->list[lst->index].lex == constsym)
    constDeclaration(reg, code, table, lst, ofp);

  if(lst->list[lst->index].lex == varsym)
    varDeclaration(reg, code, table, lst, ofp);

  int tempSpace = space;

  if(lst->list[lst->index].lex == procsym)
    procDeclaration(reg, code, table, lst, ofp);

  code->memArr[jumpAddr].m = cx;
  gen(code, 6, 0, 0, tempSpace, ofp);
  // CHECK STATMENT

  statement(reg, code, table, lst, ofp);

  lev--;
  tx = tempTableIdx;
}

void constDeclaration(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp) {
  int curr = 0;
  if(lst->list[lst->index].lex != constsym)
    return;

  do { // enter, we have a comma or terminal
    // terminal indent
    lst->index++;

    if(lst->list[lst->index].lex != identsym) {
      error(0, 4);
    }

    strcpy(table[tx].name, lst->list[lst->index].words);

    // Terminal equalsym
    if(lst->list[lst->index].lex != eqlsym) {
      error(0, 0);
    }

    lst->index++;

    // Terminal if we get a numbersym aka a literal
    if(lst->list[lst->index].lex != numbersym) {
      error(0, 2);
    }

    lst->index++;

    // add the constant to the symbol table
    table[tx].kind = 1;
    table[tx].level = 0;
    table[tx].val = atoi(lst->list[lst->index].words);
    tx++;
    curr++;

    lst->index++;
  } while (lst->list[lst->index].lex == commasym);


  if(lst->list[lst->index].lex != semicolonsym) {
    error(0, 5);
  }


  lst->index++;
}

void varDeclaration(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp) {

  if(lst->list[lst->index].lex != varsym)
    return;

  do { // enter, we have a comma or terminal

    // get token
    lst->index++;

    if(lst->list[lst->index].lex != identsym) {
      //error(0, 4);
    }



    // enter
    table[tx].kind = 2;
    strcpy(table[tx].name, lst->list[lst->index].words);
    table[tx].level = lev;
    table[tx].addr = dx;

    tx++;
    space++;
    dx++;

    lst->index++;


  } while (lst->list[lst->index].lex == commasym);

  if(lst->list[lst->index].lex != semicolonsym) {
    error(0, 5);
  }

  lst->index++;
}

void statement(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp) {
  int i, cx1, cx2;


  if(lst->list[lst->index].lex == identsym) {
    i = position(lst->list[lst->index].words, table, tx);

    if(i == 0) {
      // error(0, 11);
    }
    else if(table[i].kind != 2) {
      error(0, 12);
    }

    lst->index++;

    // if(lst->list[lst->index].lex != table[i].level) {
    //   error(0, 3);
    // }

    lst->index++;
    expression(reg, code, table, lst, ofp); //im here now

    gen(code, 4, regIdx-1, lev - table[i].level, table[i].addr, ofp);

    regIdx--;

    if(i != 0) {
      // emit(4, table[i].levelel, table[i].addr, reg, code);
    }

  }
  else if(lst->list[lst->index].lex == callsym) {
    lst->index++;

    i = position(lst->list[lst->index].words, table, tx);

    gen(code, 5, 0, lev - table[i].level, table[i].addr, ofp);
    lst->index++;
  }
  else if(lst->list[lst->index].lex == beginsym) {

    lst->index++;

    statement(reg, code, table, lst, ofp);


    while(lst->list[lst->index].lex == semicolonsym) {
      lst->index++;
      statement(reg, code, table, lst, ofp);
    }

    if(lst->list[lst->index].lex == endsym) {
      //rror(0, 28);
    }

    lst->index++;
  }
  else if(lst->list[lst->index].lex == ifsym) {
    lst->index++;
    condition(reg, code, table, lst, ofp);
    // more here
    if(lst->list[lst->index].lex != thensym){
      error(0, 16);
    }

    lst->index++;

    int ctemp = cx;
    gen(code, 8, regIdx - 1, 0 , 0, ofp);
    statement(reg, code, table, lst, ofp);

    if(lst->list[lst->index].lex == elsesym) {
      int ctemp2 = cx;

      gen(code, 7, 0, 0, 0, ofp);

      code->memArr[ctemp].m = cx;
      lst->index++;
      statement(reg, code, table, lst, ofp);
      code->memArr[ctemp2].m = cx;
      regIdx--;
     }
     else {
       code->memArr[ctemp].m = cx;
       regIdx--;
     }
  }
  else if(lst->list[lst->index].lex == whilesym) {
    cx1 = cx;
    lst->index++;
    condition(reg, code, table, lst, ofp);
    cx2 = cx;

    if(lst->list[lst->index].lex == dosym) {
      error(0, 18);
    }
    lst->index++;

    statement(reg, code, table, lst, ofp);
    gen(code, 8, 0, 0, cx1, ofp);

    code->memArr[cx2].m = cx;
    regIdx--;
  }
  else if(lst->list[lst->index].lex == readsym) {

    int i;
    lst->index++;


    if(lst->list[lst->index].lex != identsym) {
      error(0, 29);
    }

    i = position(lst->list[lst->index].words, table, tx);

    if(i == 0) {
      // error(0, 11);
    }

    gen(code, 9, regIdx, 0, 2, ofp);

    if(table[i].kind != 2) {
      error(0, 12);
    }

    gen(code, 4, regIdx, lev - table[i].level, table[i].addr, ofp);

    lst->index++;
  }
  else if(lst->list[lst->index].lex == writesym) {

    int i;
    lst->index++;

    if(lst->list[lst->index].lex != identsym) {
      error(0, 29);
    }

    i = position(lst->list[lst->index].words, table, tx);

    if(table[i].kind == 2) {
      gen(code, 3, regIdx, lev - table[i].level, table[i].addr, ofp);
      gen(code, 9, regIdx, 0, 1, ofp);
    }
    else if(table[i].kind == 1) {
      gen(code, 1, regIdx, 0, table[i].val, ofp);
      gen(code, 9, regIdx, 0, 1, ofp);
    }

    lst->index++;
  }
}

void condition(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp) {
  if(lst->list[lst->index].lex == oddsym) {
    lst->index++;
    expression(reg, code, table, lst, ofp);
    gen(code, 15, regIdx - 1, regIdx - 1, 0, ofp);
  }
  else {
    expression(reg, code, table, lst, ofp);

    if (lst->list[lst->index].lex != eqlsym && lst->list[lst->index].lex != neqsym &&
  			lst->list[lst->index].lex != lessym && lst->list[lst->index].lex != leqsym &&
  			lst->list[lst->index].lex != gtrsym && lst->list[lst->index].lex != geqsym) {
          error(0,30);
        }

    lst->index++;
    expression(reg, code, table, lst, ofp);

    // op code 2
    if (lst->list[lst->index].lex == eqlsym) {
      gen(code, 17, regIdx -2, regIdx - 2, regIdx -1, ofp);
    }
  	else if (lst->list[lst->index].lex == neqsym) {
      gen(code, 18, regIdx -2, regIdx - 2, regIdx -1, ofp);
    }
  	else if (lst->list[lst->index].lex == lessym) {
      gen(code, 19, regIdx -2, regIdx - 2, regIdx -1, ofp);
    }
  	else if (lst->list[lst->index].lex == leqsym) {
      gen(code, 20, regIdx -2, regIdx - 2, regIdx -1, ofp);
    }
  	else if (lst->list[lst->index].lex == gtrsym) {
      gen(code, 21, regIdx -2, regIdx - 2, regIdx -1, ofp);
    }
  	else {
      gen(code, 22, regIdx -2, regIdx - 2, regIdx -1, ofp);
    }

    regIdx--;
  }
}

void expression(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp) {
  // storage for token
  int addop;

  if(lst->list[lst->index].lex == plussym || lst->list[lst->index].lex == minussym) {
    addop = lst->list[lst->index].lex;
    // get token
    lst->index++;



    term(reg, code, table, lst, ofp);

    if(addop == minussym) {
       gen(code, 10, regIdx -1, regIdx -1, 0, ofp);
    }
  }
  else {
    term(reg, code, table, lst, ofp);
  }

  while(lst->list[lst->index].lex == plussym || lst->list[lst->index].lex == minussym) {
    addop = lst->list[lst->index].lex;
    //get token
    lst->index++;

    term(reg, code, table, lst, ofp);
    // printf(" this is my token in expression: %d\n", lst->list[lst->index].lex);
    if(addop == plussym) {
      gen(code, 11, regIdx -2, regIdx -2, regIdx -1, ofp);
      regIdx--;
    }
    else {
      gen(code, 12, regIdx -2, regIdx - 2, regIdx -1, ofp);
      regIdx--;
    }
  }
}

void term(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp) {

  factor(reg, code, table, lst, ofp);

  while(lst->list[lst->index].lex == multsym || lst->list[lst->index].lex == slashsym) {
    lst->index++;
    factor(reg, code, table, lst, ofp);

    if(lst->list[lst->index].lex == multsym) {
      gen(code, 13, regIdx-2, regIdx -2, regIdx-1, ofp);
      regIdx--;
    }
    else{
      gen(code, 14, regIdx-2, regIdx -2, regIdx-1, ofp);
      regIdx--;
    }
  }
}

void factor(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp) {
  int i;

  if(lst->list[lst->index].lex == identsym) {
    i = position(lst->list[lst->index].words, table, tx);

    if(i == 0) {
      // error(0, 11);
    }
    //print out whats here

    if(table[i].kind == 2) {
      gen(code, 3, regIdx, lev - table[i].level, table[i].addr, ofp);
    }
    else if(table[i].kind == 1) {
      gen(code, 1, regIdx, 0, table[i].val, ofp);
    }
    else {
      error(0, 27);
    }
    regIdx++;
    lst->index++;
  }
  else if(lst->list[lst->index].lex == numbersym) {
    gen(code, 1, regIdx, 0, atoi(lst->list[lst->index].words), ofp);
    regIdx++;
    lst->index++;
  }
  else if(lst->list[lst->index].lex == lparentsym) {
    lst->index++;
    expression(reg, code, table, lst, ofp);

    if(lst->list[lst->index].lex == rparentsym) {
      lst->index++;
    }
    else {
      error(0, 23);
    }
  }
}

int position(char* id, symbol* table, int tx) {
  strcpy(table[0].name, id);
  int i = tx - 1;

  while(i > 0) {
    if(strcmp(table[i].name, id) == 0) {
      break;
    }
    else{
      i--;
    }
  }

  return i;
}

void procDeclaration(stack* reg, instruction* code, symbol* table, listy* lst, FILE* ofp) {
  int procSize;
  dx = 4;

  while(lst->list[lst->index].lex == procsym) {
    // keep track of our size

    lst->index++;

    if(lst->list[lst->index].lex != identsym) {
      error(0, 4);
    }

    // enter
    table[tx].kind = 3;
    strcpy(table[tx].name, lst->list[lst->index].words);
    table[tx].level = lev;
    table[tx].addr = cx;
    tx++;

    lst->index++;

    if(lst->list[lst->index].lex != semicolonsym) {
      // error();
    }

    lst->index++;

    //void block(stack* reg, instruction* code, symbol* table, listy* lst, ofp);
    block(reg, code, table, lst, ofp);
    lst->index++;

    gen(code, 2, 0, 0, 0, ofp);
  }
}

void error(int r, int n) {
	correct = 1;

	switch (n) {
		case 0:
			printf("const most be followed by =.\n");
			break;
		case 1:
			printf("Use = instead of :=.\n");
			break;
		case 2:
			printf("= must be followed by a number.\n");
			break;
		case 3:
			printf("Identifier must be followed by :=.\n");
			break;
		case 4:
			printf("const, var, procedure must be followed by identifier.\n");
			break;
		case 5:
			printf("Semicolon or comma missing.\n");
			break;
		case 6:
			printf("Incorrect symbol after procedure declaration.\n");
			break;
		case 7:
			printf("Statement expected.\n");
			break;
		case 8:
			printf("Incorrect symbol after statement part in block.\n");
			break;
		case 9:
			printf("Period expected.\n");
			break;
		case 10:
			printf("Semicolon between statements missing.\n");
			break;
		case 11:
			printf("Undeclared identifier.\n");
			break;
		case 12:
			printf("Assignment to constant or procedure is not allowed.\n");
			break;
		case 13:
			printf("Assignment operator expected.\n");
			break;
		case 14:
			printf("Call must be followed by an identifier.\n");
			break;
		case 15:
			printf("Call of a constant or variable is meaningless.\n");
			break;
		case 16:
			printf("then	 expected.\n");
			break;
		case 17:
			printf("Semicolon or } expected.\n");
			break;
		case 18:
			printf("do expected.\n");
			break;
		case 19:
			printf("Incorrect symbol following statement.\n");
			break;
		case 20:
			printf("Relational operator expected.\n");
			break;
		case 21:
			printf("Expression must not contain a procedure identifier.\n");
			break;
		case 22:
			printf("Right parenthesis missing.\n");
			break;
		case 23:
			printf("The preceding factor cannot begin with this symbol.\n");
			break;
		case 24:
			printf("An expression cannot begin with this symbol.\n");
			break;
		case 25:
			printf("This number is too large.\n");
			break;
		case 26:
			printf("Procedure expected.\n");
			break;
		case 27:
			printf("Begin Expected.\n");
			break;
		case 28:
			printf("End Expected.\n");
			break;
		case 29:
			printf("Read/Write must be followed by a identifier.\n");
			break;
		case 30:
			printf("Compare operator expected.\n");
			break;
    case 31:
			printf("var already declared.\n");
			break;
    case 32:
      printf("procedure found, exit.");
      break;
		default:
			printf("Undeclared error.\n");
			break;
	}

  exit(0);
}

void gen(instruction* code, int op, int r, int l, int m, FILE* ofp) {
  if(cx > 500)
    error(0, 25);
  else {
    code->memArr[cx].op = op; 	//opcode
    code->memArr[cx].l = l;	    // lexicographical level
    code->memArr[cx].m = m;	    // modifier
    code->memArr[cx].r = r;
    cx++;
    code->codeSize++;
  }
}
