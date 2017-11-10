// Navon Francis
// Parser
// Euripides Montagne
// 11/03/2017

#include "./Parser.h"

int tx = 1;
int cx = 0;
int correct = 0;
int addr = 4;


void parse(instruction* code, listy* lst) {

  symbol table[1000];
  stack* reg = stackInit();
  // pointers for symbol table
  int l = 0;
  int d = 0; // data index
  int t = 0; // tables index
  int i = 0;

  emit(6, 0, 3, reg, code);
  block(reg, code, table, lst);

  // complete rest of stuff here
  lst->index++;
  if(lst->list[lst->index].lex != periodsym) {
    // error(0, 9);
  }

  emit(11, 0, 0, reg, code);

  if(correct == 0) {
    printf("\nThe program is syntactically correct!\n");
  }

  // FILE *fp;
  // fp = fopen("parse.txt", "w");
  // printf("\nGenerated Code:\n");
  // for(i=0; i<cx;i++) {
  //   fprintf(fp, "%d %d %d %d\n", code[i].op, code[i].r, code[i].l, code[i].m);
  // }
  //
  // fclose(fp);

  // for(i=0; i<cx;i++) {
  //   printf("%d %d %d %d\n", code[i].op, code[i].r, code[i].l, code[i].m);
  // }

}

void block(stack* reg, instruction* code, symbol* table, listy* lst) {
  // printf("\nSymbols IN PARSER:\n");
  // int i = 0;
  // for(i = 0; i < lst->size; i++) {
  //   printf("SYMBOL (%d) - ", i);
  //   if(lst->list[i].type == 2) {
  //     printf("lex: %d ", lst->list[i].lex);
  //     printf("char: %s ", lst->list[i].words);
  //   }
  //   else if(lst->list[i].type == 1) {
  //     printf("lex: %d ", lst->list[i].lex);
  //     printf("number: %s ", lst->list[i].words);
  //   }
  //   else {
  //     printf("lex: %d ", lst->list[i].lex);
  //   }
  // }

  constDeclaration(reg, code, table, lst);
  varDeclaration(reg, code, table, lst);
  // procDeclaration(reg, code, table);

  // CHECK STATMENT
  printf("in block: the index should not be 0: %d, should be: %d\n", lst->index, beginsym);

  statement(reg, code, table, lst);

}

void constDeclaration(stack* reg, instruction* code, symbol* table, listy* lst) {
  if(lst->list[lst->index].lex != constsym)
    return;

  do { // enter, we have a comma or terminal

    // terminal indent
    lst->index++;

    if(lst->list[lst->index].lex != identsym) {
      // error(0, 4);
      printf("const\n");
    }

    strcpy(table[tx].name, lst->list[lst->index].words);

    // Terminal equalsym
    lst->index++;
    if(lst->list[lst->index].lex != eqlsym) {
      // error(0, 0);
    }

    // Terminal if we get a numbersym aka a literal
    lst->index++;
    if(lst->list[lst->index].lex != numbersym) {
      // error(0, 2);
    }


    // add the constant to the symbol table
    table[tx].kind = 1;
    table[tx].level = 0;
    printf("curr: %d", lst->list[lst->index].lex);
    table[tx].val = lst->list[lst->index].lex;
    tx++;

    lst->index++;

  } while (lst->list[lst->index].lex == commasym);



  if(lst->list[lst->index].lex != semicolonsym) {
    // error(0, 5);
  }
}

void varDeclaration(stack* reg, instruction* code, symbol* table, listy* lst) {
  int curr = 0;

  if(lst->list[lst->index].lex != intsym)
    return;

    // printf("this is indexxxx: %d\n", lst->index);

  do { // enter, we have a comma or terminal
    // printf("what the f is here %d\n", lst->list[lst->index].lex);

    // terminal ident
    lst->index++;
    // printf("should be identsym: %d\n", lst->list[lst->index].lex);

    if(lst->list[lst->index].lex != identsym) {
      error(0, 4);
    }

    // printf("tx dos: %d\n", tx);
    //
    //
    // printf("yess!!:%s\n", lst->list[2].words);
    // printf("list index??? %d\n", lst->index);

    lst->index++;
    // printf("get token? %d\n", lst->list[lst->index].lex);
    table[tx].kind = 2;
    // printf("this is my curr var: %s\n", lst->list[lst->index].words);
    strcpy(table[tx].name, lst->list[lst->index].words);
    addr++;
    table[tx].level = 0;
    table[tx].addr = addr;
    tx++;
    curr++;

    // parses correctly!!! works good, gets out at semi colon
    // which is 18
  } while (lst->list[lst->index].lex == commasym);


  if(lst->list[lst->index].lex != semicolonsym) {
    error(0, 5);
  }
  // printf("this is my index inside varDec:%d\n", lst->index);

  emit(6, 0, curr, reg, code);
  lst->index++;

  printf("this is the current symbol: %d, should be: %d\n", lst->list[lst->index].lex, beginsym);
}

void statement(stack* reg, instruction* code, symbol* table, listy* lst) {
  int i, cx1, cx2;
  // printf("this is statement index:%d\n", lst->index);
  // lst->index++;
  // printf("-------: %d\n", lst->list[lst->index].lex);


  if(lst->list[lst->index].lex == identsym) {
    lst->index++;



    i = position(lst->list[lst->index].words, table, tx);

    if(i == 0) {
      // error(0, 11);
    }
    else if(table[i].kind != 2) {
      // error(0, 12);
    }
    lst->index++;

    // here or in there?------v
    if(lst->list[lst->index].lex != becomessym) {
      // error(0, 3);
    }

    if(lst->list[lst->index].lex == becomessym) {
      lst->index++;
    }


    expression(reg, code, table, lst);

    if(i != 0) {
      emit(4, 0, table[i].addr, 0, code);
    }



  }
  else if(lst->list[lst->index].lex == beginsym) {

    printf("made it to begin!\n");

    lst->index++;
    statement(reg, code, table, lst);

    while(lst->list[lst->index].lex == semicolonsym) {
      lst->index++;
      statement(reg, code, table, lst);
    }

    lst->index++;
    if(lst->list[lst->index].lex == endsym) {
      // error(0, 28);
    }

  }
  else if(lst->list[lst->index].lex == ifsym) {
    lst->index++;
    condition(reg, code, table, lst);
    // more here
    if(lst->list[lst->index].lex != thensym){
      // error(0, 16);
    }

    lst->index++;
    emit(8, 0, 0, 0, code);
    statement(reg, code, table, lst);
  }
  else if(lst->list[lst->index].lex == whilesym) {
    cx1 = cx;
    lst->index++;
    condition(reg, code, table, lst);
    cx2 = cx;
    emit(8, 0, 0, 0, code);
    //emit
    if(lst->list[lst->index].lex == dosym) {
      // error(0, 18);
    }
    lst->index++;

    statement(reg, code, table, lst);
    emit(7, 0, cx1, 0, code);

    code->memArr[cx1].m = cx;
  }
  else if(lst->list[lst->index].lex == readsym) {

    int i;
    lst->index++;
    //emit(10, 0, 0, 1, code);
    emit(4, 0, 0, 0, code);


    if(lst->list[lst->index].lex != identsym) {
      // error(0, 29);
    }

    i = position(lst->list[lst->index].words, table, tx);

    if(i == 0) {
      // error(0, 11);
    }
    else if(table[i].kind != 2) {
      // error(0, 12);
    }

    if(i != 0) {
      emit(4, 0, table[i].addr, 0, code); // needs fixing
    }

    lst->index++;
  }
  else if(lst->list[lst->index].lex == writesym) {

    int i;
    lst->index++;

    if(lst->list[lst->index].lex != identsym) {
      // error(0, 29);
    }

    i = position(lst->list[lst->index].words, table, tx);

    if(i == 0) {
      // error(0, 11);
    }
    else if(table[i].kind != 2) {
      // error(0, 12);
    }

    emit(3, 0, 0, 0, code);

  }
}

void condition(stack* reg, instruction* code, symbol* table, listy* lst) {
  if(lst->list[lst->index].lex == oddsym) {
    lst->index++;
    expression(reg, code, table, lst);
    emit(2, 0, 6, 0, code);
  }
  else {
    expression(reg, code, table, lst);

    if (lst->list[lst->index].lex != eqlsym && lst->list[lst->index].lex != neqsym &&
  			lst->list[lst->index].lex != lessym && lst->list[lst->index].lex != leqsym &&
  			lst->list[lst->index].lex != gtrsym && lst->list[lst->index].lex != geqsym) {
          // error(0,30);
        }

    lst->index++;
    expression(reg, code, table, lst);

    // op code 2
    if (lst->list[lst->index].lex == eqlsym) {
      emit(19, 0 , 0, 0, code);
    }
  	else if (lst->list[lst->index].lex == neqsym) {
      emit(20, 0 , 0, 0, code);
    }
  	else if (lst->list[lst->index].lex == lessym) {
      emit(21, 0 , 0, 0, code);
    }
  	else if (lst->list[lst->index].lex == leqsym) {
      emit(22, 0 , 0, 0, code);
    }
  	else if (lst->list[lst->index].lex == gtrsym) {
      emit(23, 0 , 0, 0, code);
    }
  	else {
      emit(24, 0, 0, 0, code);
    }
  }
}

void expression(stack* reg, instruction* code, symbol* table, listy* lst) {


  if(lst->list[lst->index].lex == plussym || lst->list[lst->index].lex == minussym) {
    lst->index++;

    term(reg, code, table, lst);

    if(lst->list[lst->index].lex == minussym) {
       emit(2, 0, 1, 0, code);
    }
  }
  else {
    term(reg, code, table, lst);
  }



  while(lst->list[lst->index].lex == plussym || lst->list[lst->index].lex == minussym) {
    lst->index++;
    term(reg, code, table, lst);
    if(lst->list[lst->index].lex == plussym) {
      emit(2, 0, 2, 0, code);
    }
    else {
      emit(2, 0, 3, 0, code);
    }
  }
}

void term(stack* reg, instruction* code, symbol* table, listy* lst) {

  factor(reg, code, table, lst);

  while(lst->list[lst->index].lex == multsym || lst->list[lst->index].lex == slashsym) {
    lst->index++;
    factor(reg, code, table, lst);

    if(lst->list[lst->index].lex == multsym) {
      emit(2, 0, 4, 0, code);
    }
    else{
      emit(2, 0, 4, 0, code);
    }
  }
}

// nver calling factor
void factor(stack* reg, instruction* code, symbol* table, listy* lst) {
  int i;


  if(lst->list[lst->index].lex == identsym) {
    lst->index++;
    i = position(lst->list[lst->index].words, table, tx);

    if(i == 0) {
      // error(0, 11);
    }
    //print out whats here
    // printf("what is the kind %d\n", table[i].kind);

    if(table[i].kind == 2) {

      emit(3, 0, addr, 0, code);
    }
    else if(table[i].kind == 1) {
     emit(1, 0, table[i].val, 0, code);
    }
    else {
      // error(0, 12);
    }

  }
  else if(lst->list[lst->index].lex == numbersym) {
    lst->index++;
    emit(1, 0, table[i].val, 0, code);
  }
  else if(lst->list[lst->index].lex == lparentsym) {
    lst->index++;
    expression(reg, code, table, lst);

    if(lst->list[lst->index].lex == rparentsym) {
      lst->index++;
    }
    else {
      // error(0, 22);
    }
  }
}

int position(char* id, symbol* table, int tx) {
  strcpy(table[0].name, id);
  int i = tx - 1;
  int pos;

  while(i == 0) {
    if(strcmp(table[i].name, id) == 0) {
      break;
    }
    else{
      i--;
    }
  }

  // printf("kind: %d ", table[i].kind);
  // printf("name: %s ", table[i].name);
  // printf("val: %d ", table[i].val);
  // printf("level: %d ", table[i].level);
  // printf("addr: %d ", table[i].addr);
  // printf("\n");
  return i;
}

// void emit(int op, int l, int m, int r, instruction* code) {
//   if(cx > CODE_SIZE) {
//     // error(0, 25);
//   }
//   else {
//     code[cx].op = op; 	// opcode
//     code[cx].l = l;	    // lexicographical level
//     code[cx].m = m;	    // modifier
//     //code[cx].r =
//     cx++;
//   }
// }

// Recommended data structure for the symbol.
// typedef struct {
// 	int kind; 		  // const = 1, var = 2, proc = 3
// 	char name[12];	// name up to 11 chars
// 	int val; 		    // number (ASCII value)
// 	int level; 		  // L level
// 	int addr; 		  // M address
// } symbol;

// symbol* searchTable(char* id, int l, symbol* table) {
//   strcpy(table[0].name, id);
//   int i = ;
//
//   while(strcmp(table[i].name, id) != 0) {
//
//   }
//
//   return
// }
void procDeclaration(stack* reg, instruction* code, symbol* table, listy* lst) {
  while(lst->list[lst->index].lex != procsym) {
    // temp = code->codeeSize
    // emit

    lst->index++;
    if(lst->list[lst->index].lex != identsym) {
      printf("proc\n");
      // error(0, 4);
    }

    table[tx].kind = 3;
    strcpy(table[tx].name, lst->list[lst->index].words);
    // table[tx].level = trueL++;
    // table[tx].addr = code->codeeSize;

    lst->index++;
    if(lst->list[lst->index].lex != semicolonsym) {
      // error(0, 5);
    }

    // emit
    // block()
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

}
