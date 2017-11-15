#ifndef LEX
#define LEX

#include <unistd.h>
#include <string.h>
#include <stdio.h>

typedef enum {
	nulsym = 1, identsym, numbersym, plussym, minussym,
	multsym, slashsym, oddsym, eqlsym, neqsym, lessym,
	leqsym, gtrsym, geqsym, lparentsym, rparentsym,
	commasym, semicolonsym, periodsym, becomessym,
	beginsym, endsym, ifsym, thensym, whilesym, dosym,
	callsym, constsym, varsym, procsym, writesym,
	readsym , elsesym
} token_type;

// lexeme list
typedef struct {
	int lex;
	char words[11];
  int type;
	int isProc;
} lexList;

// wrapper so we can keep the length
typedef struct {
	lexList list[1000];
	int size;
	int index;
} listy;

void resetWord(char *word);
int issymbol(char letter);
listy lexy();

#endif
