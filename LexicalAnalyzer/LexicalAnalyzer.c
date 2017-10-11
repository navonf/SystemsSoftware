// Navon Francis
// Lexical Anallyzer
// Euripides Montagne
// 10/13/2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
	nulsym = 1, identsym, numbersym, plussym, minussym,
	multsym, slashsym, oddsym, eqlsym, neqsym, lessym,
	leqsym, gtrsym, geqsym, lparentsym, rparentsym,
	commasym, semicolonsym, periodsym, becomessym,
	beginsym, endsym, ifsym, thensym, whilesym, dosym,
	callsym, constsym, varsym, procsym, writesym,
	readsym , elsesym
} token_type;

// The Lexeme list
char lexem[1000];

int main() {
  // Data structure declarations
  int curr = 0;
  char c;
  char word[11];
  char number[5];
  FILE *ifp;

  // Scan in input file
  ifp = fopen("input.txt", "r");

  printf("Source Program: \n");

  while(fscanf(ifp, "%c", &c) != EOF) {
    printf("%c", c);
  }

  printf("\n");
  printf("Lexeme Table: \n");
  printf("Lexeme\t\tToken Type\n");

  // Start lexical analysis
  while(fscanf(ifp, "%c", &c) != EOF) {

    // Handling comments
    if(c == '/') {
      if(fscanf(ifp, "%c", &c) == '*') {
        while(1) {
          // Check for an asterisk, could be apart of the comment, or not
          if(fscanf(ifp, "%c", &c) == '*') {
            // This will find the ending character for comments
            if(fscanf(ifp, "%c", &c) == '/') {
              break;
            }
          }
        }
      }
    }
    // Handling Identifiers and Keywords
    // first char has to be alphabetic
    else if(isalpha(c)) {
      // flag to see if the word is a key
      int key = 0;
      int length = 0;
      // Continue if there alphas or digits
      while(isalpha(c) || isdigit(c)) {
        length++;

        // finally, if there are spaces
        if (c == 9 || c == 10 || c == 32){
          break;
        }
      }
    }
  }

  return 0;
}
