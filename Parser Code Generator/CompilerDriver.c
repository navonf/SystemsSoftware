// Navon Francis
// Compiler Driver
// Euripides Montagne
// 11/03/2017

#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./LexicalAnalyzer.h"
#include "./Parser.h"
#include "./Stack.h"


void printSymbols(int num);

int main(int argc, char* argv[]) {

  // flags for each case
  int cmd;
  int runLexer = 0;
  int runVM = 0;
  int runParser = 0;

  listy myListy;
  instruction code;
  stack* reg = stackInit();


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
    myListy = lexy();

    printf("Lexeme List:\n");
    int i = 0;

    for(i = 0; i < myListy.size; i++) {
      if(myListy.list[i].type == 2) {
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
      else {
        printSymbols(myListy.list[i].lex);
      }
    }
    printf("\n\n");
  }


  printf("\nout:\n");
  if(runParser == 1) {
    //myListy = lexy();
    parse(reg, &code);
  }

  if(runVM == 1) {
    //pMachine();
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
