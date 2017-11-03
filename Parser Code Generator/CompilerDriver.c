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


int main(int argc, char* argv[]) {

  // flags for each case
  int cmd;
  int runLexer = 0;
  int runVM = 0;
  int runParser = 0;

  listy myListy;
  instruction code;
  int reg[100];

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

  // printf(" run lexx:  %d\nrun VM %d\n runParser: %d\n", runLexer, runVM, runParser);
  if(runLexer == 1) {
    myListy = lexy();

    // printf("list size: %d\n", myListy.size);
    // int i = 0;
    //
    // for(i = 0; i < myListy.size; i++) {
    //   if(myListy.list[i].type == 2) {
    //     printf("%s ", myListy.list[i].words);
    //   }
    //   else {
    //     printf("%d ", myListy.list[i].lex);
    //   }
    // }
  }

  if(runParser == 1) {
    parse(myListy, reg, &code);
  }

  if(runVM == 1) {
    //pMachine();
  }


  return 0;
}
