// Navon Francis
// Lexical Anallyzer
// Euripides Montagne
// 10/13/2017

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "./LexicalAnalyzer.h"


// The Lexeme list
int lex[1000];

// The Identifier list
char id[1000][11];

// Function declaritions
void resetWord(char *word);
int issymbol(char letter);
listy lexy();

listy lexy() {

  // Data structure declarations
  int i;
  int flag = -99;
  int idRow = 0;
  int lexPosition = 0;
  char c;
  char word[100]; // We handle size 11 limit later in code
  char number[100];
  char sym[100];
	int tokens[1000];
  FILE *ifp;

	listy myList;

  // Scan in input file
  ifp = fopen("input.txt", "r");

  printf("Source Program: \n");

  // Input
  while(fscanf(ifp, "%c", &c) != EOF) {
    printf("%c", c);
  }
  printf("\n");
  // Reset ifp
  fseek(ifp, 0, SEEK_SET);

  // Set up table
  // printf("\n");
  // printf("Lexeme Table: \n");
  // printf("Lexeme:\t\tToken Type:\n");

  // Start lexical analysis --------------------------------------------------->
  while(fscanf(ifp, "%c", &c) != EOF) {
    // Clear our word for iteration of loop
    resetWord(word);
    resetWord(number);
    resetWord(sym);

    // Handling comments, ignore them
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
			int flag = 0;
      // Continue if there alphas or digits
      while(isalpha(c) || isdigit(c)) {
        // Start building the word
        word[pos] = c;
        pos++;

        // Error if identifier is too long
        if(pos > 11) {
          printf("Identifier name has exceeded size limit of 11.\n");
					exit(1);
        }

        fscanf(ifp, "%c", &c);
      }

      // We currently need to rewind the ifp 1 unit back, or we will not
      // be able to scan another symbol in.
      fseek(ifp, -1, SEEK_CUR);

      // String compare to add tokens
      if(strcmp(word, "if") == 0) {
        lex[lexPosition] = ifsym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, ifsym);
      }
      else if(strcmp(word, "do") == 0) {
        lex[lexPosition] = dosym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, dosym);
      }
      else if(strcmp(word, "var") == 0) {
        lex[lexPosition] = varsym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, varsym);
      }
      else if(strcmp(word, "end") == 0) {
        lex[lexPosition] = endsym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, endsym);
      }
      else if(strcmp(word, "odd") == 0) {
        lex[lexPosition] = oddsym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, oddsym);
      }
      else if(strcmp(word, "else") == 0) {
        lex[lexPosition] = elsesym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, elsesym);
      }
      else if(strcmp(word, "call") == 0) {
        lex[lexPosition] = callsym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, callsym);
      }
      else if(strcmp(word, "read") == 0) {
        lex[lexPosition] = readsym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, readsym);
      }
      else if(strcmp(word, "null") == 0) {
        lex[lexPosition] = nulsym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, nulsym);
      }
      else if(strcmp(word, "then") == 0) {
        lex[lexPosition] = thensym;
        lexPosition++;

        printf("%s\t\t%d\n", word, thensym);
      }
      else if(strcmp(word, "begin") == 0) {
        lex[lexPosition] = beginsym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, beginsym);
      }
      else if(strcmp(word, "const") == 0) {
        lex[lexPosition] = constsym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, constsym);
      }
      else if(strcmp(word, "write") == 0) {
        lex[lexPosition] = writesym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, writesym);
      }
      else if(strcmp(word, "while") == 0) {
        lex[lexPosition] = whilesym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, whilesym);
      }
      else if(strcmp(word, "null") == 0) {
        lex[lexPosition] = nulsym;
        lexPosition++;

        // printf("%s\t\t%d\n", word, nulsym);
      }
      else if(strcmp(word, "procedure") == 0) {
        lex[lexPosition] = procsym;
        lexPosition++;

				// only one tab because procedure is a long word
        // printf("%s\t%d\n", word, nulsym);
      }
      else {
					lex[lexPosition] = identsym;
	        lexPosition++;

	        // Add word to Lexeme List
	        // printf("%s\t\t%d\n", word, identsym);
	        strcpy(id[idRow], word);
	        idRow++;
      }
    }
    // Handling numbers
    else if(isdigit(c)) {
      int pos = 0;

      while(isdigit(c)) {
        // Build the number
        number[pos] = c;
        pos++;

        // Handling lex error for size
        if(pos > 5) {
          printf("Number has exceeded size limit of 5.\n");
          exit(1);
        }

        fscanf(ifp, "%c", &c);
      }

      lex[lexPosition] = numbersym;
      lexPosition++;

      // Add the number to our Lexeme List
      strcpy(id[idRow], number);
      // printf("bruh check this: ----%s\t\t%d\n", id[idRow], numbersym);
      idRow++;


      fseek(ifp, -1, SEEK_CUR);
    }
    // Here we are handling symbols, rel-ops
    // 2 char symbols include:
    // ":="  "<="  "<>"  ">="
    else if(!isalpha(c) || !isdigit(c)) {
      int pos = 0;
      sym[pos] = c;

      // Equal sign
      if(c == ':') {
        fscanf(ifp, "%c", &c);

        // handles ":="
        if(c == '=') {
          pos++;
          sym[pos] = c;
          lex[lexPosition] = becomessym;
          lexPosition++;

          // printf("%s\t\t%d\n", sym, becomessym);
        } // handles single ':'
        else {
          fseek(ifp, -1, SEEK_CUR);
          // printf("This is an invalid symbol ':'\n");
          exit(1);
        }
      }
      else if(c == '<') {
        fscanf(ifp, "%c", &c);

        //handles "<="
        if(c == '=') {
          pos++;
          sym[pos] = c;
          lex[lexPosition] = leqsym;
          lexPosition++;

          // printf("%s\t\t%d\n", sym, leqsym);
        } // handles "<>"
        else if(c == '>') {
          pos++;
          sym[pos] = c;
          lex[lexPosition] = neqsym;
          lexPosition++;

          // printf("%s\t\t%d\n", sym, neqsym);
        }
        else {
          fseek(ifp, -1, SEEK_CUR);
          lex[lexPosition] = lessym;
          lexPosition++;

          // printf("%s\t\t%d\n", sym, lessym);
        }
      }
      else if(c == '>') {
        fscanf(ifp, "%c", &c);

        // handles ":="
        if(c == '=') {
          pos++;
          sym[pos] = c;
          lex[lexPosition] = geqsym;
          lexPosition++;

          // printf("%s\t\t%d\n", sym, geqsym);
        } // handles single ':'
        else {
          fseek(ifp, -1, SEEK_CUR);
          lex[lexPosition] = gtrsym;
          lexPosition++;

          // printf("%s\t\t%d\n", sym, gtrsym);
        }
      } // continue with the rest of the single char symbols
      else if(c == '.') {
        lex[lexPosition] = periodsym;
        lexPosition++;

        // printf("%s\t\t%d\n", sym, periodsym);
      }
      else if(c == ';') {
        lex[lexPosition] = semicolonsym;
        lexPosition++;

        // printf("%s\t\t%d\n", sym, semicolonsym);
      }
      else if(c == ',') {
        lex[lexPosition] = commasym;
        lexPosition++;

        // printf("%s\t\t%d\n", sym, commasym);
      }
      else if(c == '=') {
        lex[lexPosition] = eqlsym;
        lexPosition++;

        // printf("%s\t\t%d\n", sym, eqlsym);
      }
      else if(c == ')') {
        lex[lexPosition] = rparentsym;
        lexPosition++;

        // printf("%s\t\t%d\n", sym, rparentsym);
      }
      else if(c == '(') {
        lex[lexPosition] = lparentsym;
        lexPosition++;

        // printf("%s\t\t%d\n", sym, lparentsym);
      }
      else if(c == '*') {
        lex[lexPosition] = multsym;
        lexPosition++;

        // printf("%s\t\t%d\n", sym, multsym);
      }
      else if(c == '-') {
        lex[lexPosition] = minussym;
        lexPosition++;

        // printf("%s\t\t%d\n", sym, minussym);
      }
      else if(c == '+') {
        lex[lexPosition] = plussym;
        lexPosition++;

        // printf("%s\t\t%d\n", sym, plussym);
      }
    }
  }

  // Print out Lexeme List ---------------------------------------------------->
  // printf("\n");
  // printf("Lexeme List:\n");
  int j = 0;
	int idx = 0;
	int s = 1;
  int procFlag = 0;
  printf("LEXXXLISTTTTT \n");

  while(lex[i] != periodsym) {
    procFlag = 0;
    printf("%d ", lex[i]);
		myList.list[idx].lex = lex[i];
		myList.size = s++;

    if(lex[i] == constsym) {
      // Print each var name or number
      printf("%s ", id[j]);
			strcpy(myList.list[idx].words, id[j]);
			myList.list[idx].type = 1;
      j++;
    }

    if(lex[i] == identsym) {
      // Print each var name or number
      printf("%s ", id[j]);
			strcpy(myList.list[idx].words, id[j]);
			myList.list[idx].type = 2;
      j++;
    }

    if(lex[i] == numbersym) {
      /// for numbers
      printf("%s ", id[j]);
      strcpy(myList.list[idx].words, id[j]);
      myList.list[idx].type = 4;
      j++;
    }

    // handle procedure
    if(lex[i] == procsym) {
      procFlag = 1;
      myList.list[idx].isProc = 1;
      while(lex[i] != endsym) {
        if(lex[i] != procsym && lex[i] != constsym && lex[i] != identsym && lex[i] != numbersym) {
          printf("%d ", lex[i]);
      		myList.list[idx].lex = lex[i];
          myList.list[idx].isProc = 1;
        }

        if(lex[i] == constsym) {
          // Print each var name or number
          printf("%d ", lex[i]);
          myList.list[idx].lex = lex[i];
          printf("%s ", id[j]);
    			strcpy(myList.list[idx].words, id[j]);
    			myList.list[idx].type = 1;
          myList.list[idx].isProc = 1;
          j++;
        }

        if(lex[i] == identsym) {
          // Print each var name or number
          printf("%d ", lex[i]);
          myList.list[idx].lex = lex[i];
          printf("%s ", id[j]);
    			strcpy(myList.list[idx].words, id[j]);
    			myList.list[idx].type = 2;
          myList.list[idx].isProc = 1;
          j++;
        }

        if(lex[i] == numbersym) {
          /// for numbers
          printf("%d ", lex[i]);
          myList.list[idx].lex = lex[i];
          printf("%s ", id[j]);
          strcpy(myList.list[idx].words, id[j]);
          myList.list[idx].type = 4;
          myList.list[idx].isProc = 1;
          j++;
        }

        myList.size = s++;
        i++;
        idx++;
      }
    }

    if(procFlag == 0) {
      idx++;
      i++;
    }
  }
  if(lex[i] == periodsym) {
    myList.size = s++;
    printf("%d ", lex[i]);
    myList.list[idx].lex = lex[i];
  }
  printf("\n");

  // return tokens
	return myList;
}

// Function to clear out our strings, uhg, C
void resetWord(char *word) {
  int i;
  for(i = 0; i < 100; i++) {
    word[i] = '\0';
  }
}
