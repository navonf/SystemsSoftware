// Navon Francis
// Parser
// Euripides Montagne
// 11/03/2017

#include "./Parser.h"

int isCorrect = 0;
int trueL = 0;
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

void parse(listy lst, int* reg, instruction* code) {
  symbol table[1000];
  // pointers for symbol table
  int l = 0; // level
  int d = 0; // data index
  int t = 0; // tables index
  lst.index = 0;

  block(lst, reg, code, table);


  if(lst.list[lst.index].lex != periodsym) {
    error(0, 9);
  }

  if(isCorrect == 0) {
    printf("\nThe program is syntactically correct!\n");
  }

}

void block(listy lst, int* reg, instruction* code, symbol* table) {
  int addr = 4;

  constDeclaration(lst , reg, code, table);
	varDeclaration(lst, reg, code, &addr, table);
	procDeclaration(lst, reg, code, table);
}

void constDeclaration(listy lst, int* reg, instruction* code, symbol* table) {

  if(lst.list[lst.index].lex != constsym)
    return;

  do { // enter, we have a comma or terminal

    // terminal indent
    lst.index++;
    if(lst.list[lst.index].type != identsym) {
      error(0, 4);
    }
    strcpy(table->name, lst.list[lst.index].words);

    lst.index++;
    if(lst.list[lst.index].lex != eqlsym) {
      error(0, 0);
    }

    lst.index++;
    if(lst.list[lst.index].lex != numbersym) {
      error(0, 2);
    }

    table->kind = 1;
    table->level = 0;
    table->val = lst.list[lst.index].lex;



  } while (lst.list[lst.index].lex == commasym);

  lst.index++;

  if(lst.list[lst.index].lex != semicolonsym) {
    error(0, 5);
  }
}

void varDeclaration(listy lst, int* reg, instruction* code, int* addrPos, symbol* table) {

  if(lst.list[lst.index].lex != varsym)
    return;


  do { // enter, we have a comma or terminal

    // terminal ident
    lst.index++;
    if(lst.list[lst.index].type != identsym) {
      error(0, 4);
    }
    table->kind = 2;
    strcpy(table->name, lst.list[lst.index].words);
    (*addrPos)++;
    table->level = 0;
    table->addr = *addrPos;

  } while (lst.list[lst.index].lex == commasym);

  lst.index++;

  if(lst.list[lst.index].lex != semicolonsym) {
    error(0, 5);
  }

  // gen
}

void procDeclaration(listy lst, int* reg, instruction* code, symbol* table) {
  while(lst.list[lst.index].lex != procsym) {
    // temp = code->codeeSize
    // gen

    lst.index++;
    if(lst.list[lst.index].lex != identsym) {
      error(0, 4);
    }

    table->kind = 3;
    strcpy(table->name, lst.list[lst.index].words);
    table->level = trueL++;
    // table->addr = code->codeeSize;

    lst.index++;
    if(lst.list[lst.index].lex != semicolonsym) {
      error(0, 5);
    }

    // gen
    block(lst, )
  }
}

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
		default:
			printf("Undeclared error.\n");
			break;
	}

  if (!recovery) {
		exit(1);
  }
}
