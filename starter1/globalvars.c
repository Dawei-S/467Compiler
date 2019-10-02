/*------------------------------------------------------------------------
--YOUR GROUP INFO SHOULD GO HERE--

  globalvars.c
  CSC467F Project Compiler Shared Global Variables
  
This file contains the definition of global variables that are used for
communication among the various compiler modules
------------------------------------------------------------------------*/

/*------------------------------------------------------------------------
  FILE global variables.
Used to specify sinks for compiler output and sources for compiler input
------------------------------------------------------------------------*/
#include <stdio.h>

FILE * inputFile;
FILE * outputFile;
FILE * errorFile;
FILE * dumpFile;
FILE * traceFile;
FILE * runInputFile;

/*------------------------------------------------------------------------
Control flags, set by main.c, used to cause various optional compiler
actions to take place. 
------------------------------------------------------------------------*/

int errorOccurred;
int suppressExecution;

int traceScanner;
int traceParser;
int traceExecution;

int dumpSource;
int dumpAST;
int dumpSymbols;
int dumpInstructions;

/*------------------------------------------------------------------------
  Scanner/Parser/AST/Semantics global variables.

--NOTE--If you need to add global variables for phases 1 to 3, add them
below this comment.
------------------------------------------------------------------------*/


/*------------------------------------------------------------------------
  Code generator global variables

Global variables used by the code generator module. The three given are
used to communicate the initial value of the machine state to the pseudo
machine interpreter.
--NOTE--Any other global variables you add for phase 4 should go below
this comment as well.
------------------------------------------------------------------------*/

int startPC;  /* address of first instruction in the compiled program */
int startMSP; /* initial value for memory stack pointer (msp) */
int startMLP; /* initial value for memory limit pointer (mlp) */

