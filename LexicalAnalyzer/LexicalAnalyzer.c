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

int main() {
  // Data structure declarations
  char c;
  FILE *ifp;

  // Scan in input file
  ifp = fopen("input.txt", "r");

  // Start lexical analysis
  while(fscanf(ifp, "%c", &c) != EOF) {

    printf("%c", c);
  }

  return 0;
}
