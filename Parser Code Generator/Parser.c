// Navon Francis
// Parser
// Eurip`id`es Montagne
// 11/03/2017

#include "./Parser.h"

int isCorrect = 0;
int trueL = 0;
int tx = 1;
int cx = 0;

// here for reference
// // lexeme list
// typedef struct {
// 	int lex;
// 	char words[11];
//   int type;
// } lexList;
//
// // wrapper so we can keep the length
// typedef struct {
// 	lexList list[1000];
// 	int size;
// 	int index;
// } listy;

void parse(listy lst, stack* reg, instruction* code) {

  symbol table[1000];
  // pointers for symbol table
  int l = 0; // level
  int d = 0; // data index
  int t = 0; // tables index
  lst.index = 0;

  int i = 0;

  // emit(6, 0, 3, reg, code);
  block(lst, reg, code, table);

  // complete rest of stuff here

  if(lst.list[lst.index].lex != periodsym) {
    error(0, 9);
  }

  if(isCorrect == 0) {
    printf("\nThe program is syntactically correct!\n");
  }

}

void block(listy lst, stack* reg, instruction* code, symbol* table) {
  int addr = 4;

  constDeclaration(lst , reg, code, table);
	varDeclaration(lst, reg, code, &addr, table);


  statement(lst, reg, code, table);


}

void constDeclaration(listy lst, stack* reg, instruction* code, symbol* table) {
  if(lst.list[lst.index].lex != constsym)
    return;

  do { // enter, we have a comma or terminal

    // terminal indent
    lst.index++;
    if(lst.list[lst.index].type != identsym) {
      error(0, 4);
    }

    strcpy(table[tx].name, lst.list[lst.index].words);

    lst.index++;
    if(lst.list[lst.index].lex != eqlsym) {
      error(0, 0);
    }

    lst.index++;
    if(lst.list[lst.index].lex != numbersym) {
      error(0, 2);
    }

    table[tx].kind = 1;
    table[tx].level = 0;
    table[tx].val = lst.list[lst.index].lex;
    tx++;



  } while (lst.list[lst.index].lex == commasym);

  lst.index++;

  if(lst.list[lst.index].lex != semicolonsym) {
    error(0, 5);
  }
}

void varDeclaration(listy lst, stack* reg, instruction* code, int* addrPos, symbol* table) {
  printf("list index:: %d\n", lst.index);

  int i = 0;

  printf("this is my shit: %d and %d\n", lst.list[lst.index].lex, varsym);

  if(lst.list[lst.index].lex != varsym)
    return;


  do { // enter, we have a comma or terminal

    // terminal ident
    lst.index++;
    if(lst.list[lst.index].type != identsym) {
      printf("tx: %d\n", tx);

      error(0, 4);
    }

    // printf("tx dos: %d\n", tx);
    //
    //
    // printf("yess!!:%s\n", lst.list[2].words);
    // printf("list index??? %d\n", lst.index);

    lst.index++;
    table[tx].kind = 2;
    strcpy(table[tx].name, lst.list[lst.index].words);
    (*addrPos)++;
    table[tx].level = 0;
    table[tx].addr = *addrPos;
    tx++;
    i++;


  } while (lst.list[lst.index].lex == commasym);

  lst.index++;

  if(lst.list[lst.index].lex != semicolonsym) {
    error(0, 5);
  }

  // emit(6, 0, i, reg, code);
}

void statement(listy lst, stack* reg, instruction* code, symbol* table) {
  int i;

  lst.index++;
  // printf("-------: %d\n", lst.list[lst.index].lex);

  if(lst.list[lst.index].lex == identsym) {

    lst.index++;

    i = position(lst.list[lst.index].words, table, tx);

    if(lst.list[lst.index].type != becomessym) {
      error(0, 3);
    }
  }
  lst.index++;
  expression();

}

void expression(listy lst, stack* reg, instruction* code, symbol* table) {

}
int position(char* id, symbol* table, int tx) {
  strcpy(table[0].name, id);
  int i = tx - 1;
  int pos;

  // printf("Hi you made it\n");
  // printf("%d\n", table[1].kind);
  // printf("the one we want %s, the one in the index %s\n", table[0].name, table[1].name);
  // printf("%d\n", table[1].val);
  // printf("%d\n", table[1].level);
  // printf("%d\n", table[1].addr);

  while(i == 0) {
    if(strcmp(table[i].name, id) == 0) {
      break;
    }
    else{
      i--;
    }
  }

  return i;
}

// void emit(int op, int l, int m, int r, instruction* code) {
//   if(cx > CODE_SIZE) {
//     error(25);
//   }
//   else {
//     code[cx].op = op; 	//opcode
//     code[cx].l = l;	// lexicographical level
//     code[cx].m = m;	// modifier
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
// void procDeclaration(listy lst, stack* reg, instruction* code, symbol* table) {
//   while(lst.list[lst.index].lex != procsym) {
//     // temp = code->codeeSize
//     // gen
//
//     lst.index++;
//     if(lst.list[lst.index].lex != identsym) {
//       error(0, 4);
//     }
//
//     table[tx].kind = 3;
//     strcpy(table[tx].name, lst.list[lst.index].words);
//     table[tx].level = trueL++;
//     // table[tx].addr = code->codeeSize;
//
//     lst.index++;
//     if(lst.list[lst.index].lex != semicolonsym) {
//       error(0, 5);
//     }
//
//     // gen
//     // block(lst, )
//   }
// }


void error (int recovery, int n) {
	isCorrect = 1;

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
			printf(") expected.\n");
			break;
    case 32:
      printf("procedure found, exit.");
      break;
		default:
			printf("Undeclared error.\n");
			break;
	}

  // if (!recovery) {
	// 	exit(1);
  // }
}
