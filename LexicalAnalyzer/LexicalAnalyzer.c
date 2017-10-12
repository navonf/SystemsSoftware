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
int lex[1000];

// Function declaritions
void resetWord(char *word);

int main() {
  // Data structure declarations
  int i;
  int lexPosition = 0;
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

  // Reset ifp
  rewind(ifp);

  printf("\n");
  printf("Lexeme Table: \n");
  printf("Lexeme:\t\tToken Type:\n");

  // Start lexical analysis --------------------------------------------------->
  while(fscanf(ifp, "%c", &c) != EOF) {
    // Clear our word for iteration of loop
    resetWord(word);

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
      int pos = 0; // word postion/length

      // Continue if there alphas or digits
      while(isalpha(c) || isdigit(c)) {
        // Start building the word
        word[pos] = c;
        pos++;

        // Error if identifier is too long
        if(pos > 11) {
          printf("Identifier name has exceeded size limit of 11.\n");
        }

        fscanf(ifp, "%c", &c);

        // Finally, break if there are tabs, new lines, or spaces
        if (c == 9 || c == 10 || c == 32) {
          break;
        }
      }
      // String compare to add tokens
      if(strcmp(word, "if") == 0) {
        lex[lexPosition] = ifsym;
        lexPosition++;

        printf("%s\t\t%d\n", word, ifsym);
      }
      else if(strcmp(word, "do") == 0) {
        lex[lexPosition] = dosym;
        lexPosition++;

        printf("%s\t\t%d\n", word, dosym);
      }
      else if(strcmp(word, "var") == 0) {
        lex[lexPosition] = varsym;
        lexPosition++;

        printf("%s\t\t%d\n", word, varsym);
        // scan in the var here add it to lex

      }
      else if(strcmp(word, "end") == 0) {
        lex[lexPosition] = endsym;
        lexPosition++;

        printf("%s\t\t%d\n", word, endsym);
      }
      else if(strcmp(word, "odd") == 0) {
        lex[lexPosition] = oddsym;
        lexPosition++;

        printf("%s\t\t%d\n", word, oddsym);
      }
      else if(strcmp(word, "else") == 0) {
        lex[lexPosition] = elsesym;
        lexPosition++;

        printf("%s\t\t%d\n", word, elsesym);
      }
      else if(strcmp(word, "call") == 0) {
        lex[lexPosition] = callsym;
        lexPosition++;

        printf("%s\t\t%d\n", word, callsym);
      }
      else if(strcmp(word, "read") == 0) {
        lex[lexPosition] = readsym;
        lexPosition++;

        printf("%s\t\t%d\n", word, readsym);
      }
      else if(strcmp(word, "null") == 0) {
        lex[lexPosition] = nulsym;
        lexPosition++;

        printf("%s\t\t%d\n", word, nulsym);
      }
      else if(strcmp(word, "then") == 0) {
        lex[lexPosition] = thensym;
        lexPosition++;

        printf("%s\t\t%d\n", word, thensym);
      }
      else if(strcmp(word, "begin") == 0) {
        lex[lexPosition] = beginsym;
        lexPosition++;

        printf("%s\t\t%d\n", word, beginsym);
      }
      else if(strcmp(word, "const") == 0) {
        lex[lexPosition] = constsym;
        lexPosition++;

        printf("%s\t\t%d\n", word, constsym);
      }
      else if(strcmp(word, "write") == 0) {
        lex[lexPosition] = writesym;
        lexPosition++;

        printf("%s\t\t%d\n", word, writesym);
      }
      else if(strcmp(word, "while") == 0) {
        lex[lexPosition] = whilesym;
        lexPosition++;

        printf("%s\t\t%d\n", word, whilesym);
      }
      else if(strcmp(word, "null") == 0) {
        lex[lexPosition] = nulsym;
        lexPosition++;

        printf("%s\t\t%d\n", word, nulsym);
      }


      // i might have to clear word
      // printf("%s \n", word);
    }
  }


  // Print out Lexeme List ---------------------------------------------------->
  printf("\n");
  printf("Lexeme List: Lex pos: %d\n", lexPosition);
  for(i = 0; i < lexPosition; i++) {
    printf("%d ", lex[i]);
  }
  printf("\n");
  printf("%d \n", lex[0]);

  return 0;
}

void resetWord(char *word) {
  int i;
  for(i = 0; i < 11; i++) {
    word[i] = '\0';
  }
}
