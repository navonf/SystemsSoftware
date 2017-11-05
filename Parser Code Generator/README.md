# Parser - Code Generator
Scans in a PL/0 program and parses it for Lexical Analysis, Generates Intermediate code, and the stack trace.

- Have a file named "input.txt" in the same folder as all of the zip files.

- Now, run the commands below

$ gcc -o compiler LexicalAnalyzer.c Parser.c CompilerDriver.c Stack.c pMachine.c

$ ./compiler -l -a -v

- Unfortunately, I did not have sufficient time to complete and debug the parser and implement my pMachine. It finds the correct Lexeme List, Symbols, some errors, and a partial amount of generated code. Thank you.
