/*------------------------------------------------------------------------
--YOUR GROUP INFO SHOULD GO HERE--

  main.c
This is the main driver program for the CSC467F course project compiler.
It handles compiler command line options and initialization, calls the
parser to run the compilation and then invokes the pseudo machine
interpreter to execute the compiled program.
------------------------------------------------------------------------*/

/*------------------------------------------------------------------------
  The compiler has the following parts:
global definitions             common.h
global variable declarations   globalvars.c
scanner module                 scanner.c
parser module                  parser.c, parser.tab.h
abstract syntax tree module    ast.c
symbol table module            symbol.c
semantics analysis module      semantics.c
code generator module          codegen.c
machine interpreter module     machineDef.h, machine.c
------------------------------------------------------------------------*/

#include "common.h"

/* Phases 3,4: Uncomment following includes as needed */
/* #include "ast.h" */
/* #include "codegen.h" */
/* #include "machine.h" */

/*------------------------------------------------------------------------
Default values for various files. Note assumption that default files are
not closed at the end of compilation.
------------------------------------------------------------------------*/

#define DEFAULT_INPUT_FILE     fopen ("lex_test.in" , "r")
#define DEFAULT_OUTPUT_FILE    fopen ("lex_test.out" , "w")
#define DEFAULT_ERROR_FILE     stderr
#define DEFAULT_DUMP_FILE      fopen ("lex_test.dump" , "w")
#define DEFAULT_TRACE_FILE     fopen ("lex_test.trace" , "w")
#define DEFAULT_RUN_INPUT_FILE stdin

void getOpts (int numargs, char **argstr);
FILE *fileOpen (char *fileName, char *fileMode, FILE *defaultFile);
void sourceDump(void);

/*------------------------------------------------------------------------
Include interface definitions for external procedures that we call here.
------------------------------------------------------------------------*/

/* Phase 1: Scanner Interface. For phase 2 and after these declarations
   are removed */
extern int yylex(void);
extern char *yytext;
extern int yyline;

/* Phase 2: Parser Interface. Merely uncomment the following line */
/* extern int yyparse(void); */

/*------------------------------------------------------------------------
Main program for the Compiler
------------------------------------------------------------------------*/

int main (int argc, char *argv[]) {
    
        /* Set up and apply command line options */
    getOpts (argc, argv);

/*------------------------------------------------------------------------
  Compiler Initialization.
If explicit initialization of any phase of the compilation is needed,
calls to initialization routines in the applicable modules are placed
here.
------------------------------------------------------------------------*/

    errorOccurred = FALSE;

/*------------------------------------------------------------------------
  Start the Compilation
------------------------------------------------------------------------*/
    if (dumpSource) {
        sourceDump();
        }

/* Phase 1: Scanner. In phase 2 and after the following code should be
    removed */
    while (yylex()) {
        if (errorOccurred) {
            break;
            }
        }

/* Phase 2: Parser. Uncomment the following call to yyparse */
/*
    yyparse();
*/

/* Phase 3: Add code to call the AST dumping routine if requested */

/* Phase 4: Add code to call the code generation routine */

/*------------------------------------------------------------------------
  Post Compilation Cleanup
------------------------------------------------------------------------*/

  /* Make calls to any cleanup or finalization routines here */

/*------------------------------------------------------------------------
Uncommenting the following block of code will make it possible to execute
the program in machine memory. machineExecute handles suppressExecution
flag so it can dump the compiled code if requested.
------------------------------------------------------------------------*/

/*
    if (errorOccurred) {
        fprintf(outputFile,
                 "Execution suppressed due to compilation errors\n");
        }
    else {
        machineExecute();
        }
*/

        /* Clean up files if necessary */
    if (inputFile != DEFAULT_INPUT_FILE)
        fclose (inputFile);
    if (errorFile != DEFAULT_ERROR_FILE)
        fclose (errorFile);
    if (dumpFile != DEFAULT_DUMP_FILE)
        fclose (dumpFile);
    if (traceFile != DEFAULT_TRACE_FILE)
        fclose (traceFile);
    if (outputFile != DEFAULT_OUTPUT_FILE)
        fclose (outputFile);
    if (runInputFile != DEFAULT_RUN_INPUT_FILE)
        fclose (runInputFile);

    return 0;
    }

/*------------------------------------------------------------------------
Internal Subroutines.
------------------------------------------------------------------------*/

/*------------------------------------------------------------------------
Subroutines for reading command line input and initializing IO files.
------------------------------------------------------------------------*/
void getOpts (int numargs, char **argstr) {
    char *optarg, *subarg;
    int i;
    char optch;

        /* Initialize global variables to default values */
    inputFile = DEFAULT_INPUT_FILE;
    outputFile = DEFAULT_OUTPUT_FILE;
    errorFile = DEFAULT_ERROR_FILE;
    dumpFile = DEFAULT_DUMP_FILE;
    traceFile = DEFAULT_TRACE_FILE;
    runInputFile = DEFAULT_RUN_INPUT_FILE;

        /* Initialize control flags */
    suppressExecution = FALSE;

    traceScanner = TRUE;
    traceParser = FALSE;
    traceExecution = FALSE;

    dumpSource = FALSE;
    dumpAST = FALSE;
    dumpSymbols = FALSE;
    dumpInstructions = FALSE;

        /* Process command line input */
    for (i=1; i<numargs; i++) {
        optarg = argstr[i];
        if (optarg[0] == '-') { /* Compiler option */
            subarg = optarg + 2;
            switch (optarg[1]) {
                case 'D': /* Dump options -Dasxy */
                    optch = *(subarg++);
                    while (optch){
                        switch (optch) {
                            case 'a': dumpAST = TRUE; break;
                            case 's': dumpSource = TRUE; break;
                            case 'x': dumpInstructions = TRUE; break;
                            case 'y': dumpSymbols = TRUE; break;
                            default: fprintf(errorFile,
                                "Invalid dump option %c ignored\n", optch);
                                    break ;
                            }
                        optch = *(subarg++);
                        }
                    break;
                case 'T': /* Trace options -Tacnpsxy */
                    optch = *(subarg++);
                    while (optch){
                        switch (optch) {
                            case 'n': traceScanner = TRUE; break;
                            case 'p': traceParser = TRUE; break;
                            case 'x': traceExecution = TRUE; break;
                            default: fprintf(errorFile,
                                "Invalid trace option %c ignored\n", optch);
                                break;
                            }
                        optch = *(subarg++);
                        }
                    break;
                case 'O': /* Alternative output file */
                    if (optarg[2] == 0) {
                        i += 1;
                        outputFile = fileOpen (argstr[i], "w",
                                DEFAULT_OUTPUT_FILE);
                        }
                    else {
                        outputFile = fileOpen (&optarg[2], "w",
                                DEFAULT_OUTPUT_FILE);
                        }
                    break;
                case 'E': /* Alternative error message file */
                    if (optarg[2] == 0) {
                        i += 1;
                        errorFile = fileOpen (argstr[i], "w",
                                DEFAULT_OUTPUT_FILE);
                        }
                    else {
                        errorFile = fileOpen (&optarg[2], "w",
                                DEFAULT_ERROR_FILE);
                        }
                    break;
                case 'R': /* Alternative sink for traces */
                    if (optarg[2] == 0) {
                        i += 1;
                        traceFile = fileOpen (argstr[i], "w",
                                DEFAULT_TRACE_FILE);
                        }
                    else {
                        traceFile = fileOpen (&optarg[2], "w",
                                DEFAULT_TRACE_FILE);
                        }
                    break;
                case 'U': /* Alternative sink for dumps */
                    if (optarg[2] == 0) {
                        i += 1;
                        dumpFile = fileOpen (argstr[i], "w",
                                DEFAULT_DUMP_FILE);
                        }
                    else {
                        dumpFile = fileOpen (&optarg[2], "w",
                                DEFAULT_DUMP_FILE);
                        }
                    break;
                case 'I': /* Alternative input during execution */
                    if (optarg[2] == 0) {
                        i += 1;
                        runInputFile = fileOpen (argstr[i], "r",
                                DEFAULT_RUN_INPUT_FILE);
                        }
                    else {
                        runInputFile = fileOpen (&optarg[2], "r",
                                DEFAULT_RUN_INPUT_FILE);
                        }
                    break;
                case 'X': /* supress execution flag */
                    suppressExecution = TRUE; break;
                default: /* Anything else */
                    fprintf(stderr,"Unknown option character %c (ignored)\n",
                        optch);
                    break;
                }
            }

        else { /* Source file */
            inputFile = fileOpen(optarg , "r", DEFAULT_INPUT_FILE);
            }
        }

    return;
    }

/*------------------------------------------------------------------------
  Utility for opening files 
------------------------------------------------------------------------*/

FILE *fileOpen (char *fileName, char *fileMode, FILE *defaultFile) {
    FILE * fTemp;

    if ((fTemp = fopen (fileName, fileMode)) != NULL) {
        return fTemp;
        }
    else {
        fprintf (errorFile, "Unable to open file %s\n", fileName);
        return defaultFile;
        }
    }

/*------------------------------------------------------------------------
   Dump source file, with line numbers.
------------------------------------------------------------------------*/

void sourceDump (void) {
    char srcbuf[MAX_TEXT];
    int i = 0;

    while (fgets(srcbuf, MAX_TEXT, inputFile)) {
        i += 1;
        fprintf(dumpFile, "%3d: %s", i, srcbuf);
        }
    rewind(inputFile);

    return;
    }
