 ###########################################################################
#	
#	Makefile
#
#	makefile for compiler  - CSC467F course project compiler
#
###########################################################################
###########################################################################
#	
#	This make file provides the following targets
#
#	make	compiler467 	Build the complete compiler
#	make	lex.yy.c	Build the scanner
#	make	parser.c:	Build the parser C code 
#	make	parser.tab.h:	Build the parser parser.tab.h header
#       make    ast             Build the AST module
#	make	semantics	Build the semantics module
#	make	codegen		Build the code generator module
#	make	symbol		Build the symbol table module
#	make	machine		Build the machine interpreter module

###########################################################################

#   Manual processing commands and flags -- Usefull to automate manual 
#   generation at compile time. For this purpose, you should create a 
#   target in the target list.  
PSROFF	= psroff
PSFLAGS = -man -t
NROFF	= nroff
NFLAGS	= -man

###########################################################################
# 	Compiler and Compiler Flags
#	Compiler REQUIRES ANSI C compiler
# Note: on local system LIBS should be set to -lfl for flex library
###########################################################################

CC = gcc
CFLAGS = -g -Wall
LIBS =  -ll

###########################################################################
#	
#	Some define files that make up the compiler source.
#	Add more object files here for the subsequent modules of 
#	the compiler that you will program.
###########################################################################

OBJs = main.o globalvars.o lex.yy.o
# TO BE ADDED parser.tab.o ast.o semantic.o symbol.o codegen.o machine.o

###########################################################################
#	
#	Dependencies for the compiler
#	
###########################################################################
compiler467: ${OBJs}
	${CC} ${CFLAGS} ${OBJs} ${LIBS} -o compiler467

main.o: main.c common.h
	${CC} ${CFLAGS} -c main.c -o main.o

globalvars.o: globalvars.c common.h
	${CC} ${CFLAGS} -c globalvars.c -o globalvars.o

lex.yy.o: lex.yy.c common.h
	${CC} ${CFLAGS} -c lex.yy.c -o lex.yy.o
lex.yy.c: scanner.l common.h
	flex -i scanner.l

# parser.tab.o: parser.tab.c
#	${CC} ${CFLAGS} -c parser.tab.c -o parser.tab.o
# parser.tab.c: parser.y common.h ast.h
#	bison -dv --debug parser.y
# parser.tab.h: parser.tab.c ast.h

# ast.o: ast.c common.h
# 	${CC} ${CFLAGS} -c ast.c -o ast.o
# semantics.o: semantics.c common.h ast.h symbol.h
# 	${CC} ${CFLAGS} -c semantic.c -o semantic.o
# symbol.o: symbol.c common.h ast.h
# 	${CC} ${CFLAGS} -c symbol.c -o symbol.o

# codegen.o: codegen.c common.h ast.h symbol.h machine.h machineDef.h
# 	${CC} ${CFLAGS} -c codegen.c -o codegen.o
# machine.o: machine.c machineDef.h common.h
# 	${CC} ${CFLAGS} -c machine.c -o machine.o

clean:
	rm -f compiler467 lex.yy.c *.o parser.tab.[ch] parser.output

