%{
/*----------------------------------------------------------------------
--YOUR GROUP INFO SHOULD GO HERE--

  Interface to the scanner module for CSC467 course project
----------------------------------------------------------------------*/

#include "common.h"

/*
Phase 1: Use the following emum statement to define constants for the
scanner's return values (one per token). In phase 2 this enum statement
should be removed since bison will automatically generate #defines for
each token and place them in parser.tab.h. Note: since TRUE and FALSE
are already defined in common.h you will have to use alternate names for
the constants denoting the "true" and "false" tokens.
*/

/* enum {REMOVE_THIS_EXAMPLE = 1};*/
enum {
    CONST = 1,
    IF,
    ELSE,
    WHILE,
    VOID_T,
    INT_T,
    BOOL_T,
    FLOAT_T,
    VEC2_T,
    VEC3_T,
    VEC4_T,
    BVEC2_T,
    BVEC3_T,
    BVEC4_T,
    IVEC2_T,
    IVEC3_T,
    IVEC4_T,
    DP3_F,
    LIT_F,
    RSQ_F,
    GL_FRAGCOLOR_V,
    GL_FRAGDEPTH_V,
    GL_FRAGCOORD_V,
    GL_TEXCOORD_V,
    GL_COLOR_V,
    GL_SECONDARY_V,
    GL_FOGFRAGCOORD_V,
    GL_LIGHT_HALF_V,
    GL_LIGHT_AMBIENT_V,
    GL_MATERIAL_SHININESS_V,
    ENV1_V,
    ENV2_V,
    ENV3_V,
    LBRAC,
    RBRAC,
    LSBRAC,
    RSBRAC,
    LSCOPE,
    RSCOPE,
    COMMA,
    SEMICOLON,
    PLUS,
    MINUS,
    MUL,
    DIV,
    POWER,
    ASSIGN,
    NOT,
    AND,
    OR,
    EQ,
    NEQ,
    LT,
    LE,
    GT,
    GE,
};


#define yTRACE(x)    { if (traceScanner) fprintf(traceFile, "TOKEN %3d : %s\n", x, yytext); }

/*
Phase 2: This is parser generated h-file with definitions needed to sync
the activities of the scanner and the parser.

#include "parser.tab.h"
*/


/*
Phase 3: Will be needed if some of the types defined in the parser.tab.h's 
yylval union are defined in your AST module.

#include "ast.h"
*/

#define YY_USER_INIT  {yyin = inputFile;}
#define	yyinput input

int yyline = 1;

%}
%option noyywrap

WS          [ \t\n]
DELIM	    [ \t\n\(\)\[\]\{\},;\+\-\*\/\^=!\<\>]|&&|"||"|==|!=|"<"=|">"=

%%

const/{DELIM}	{yTRACE(CONST); return CONST;}

if/{DELIM}	{yTRACE(IF); return IF;}
else/{DELIM}	{yTRACE(ELSE); return ELSE;}
while/{DELIM}	{yTRACE(WHILE); return WHILE;}

void/{DELIM}	{yTRACE(VOID_T); return VOID_T;}
int/{DELIM}	{yTRACE(INT_T); return INT_T;}
bool/{DELIM}	{yTRACE(BOOL_T); return BOOL_T;}
float/{DELIM}	{yTRACE(FLOAT_T); return FLOAT_T;}
vec2/{DELIM}	{yTRACE(VEC2_T); return VEC2_T;}
vec3/{DELIM}	{yTRACE(VEC3_T); return VEC3_T;}
vec4/{DELIM}	{yTRACE(VEC4_T); return VEC4_T;}
bvec2/{DELIM}	{yTRACE(BVEC2_T); return BVEC2_T;}
bvec3/{DELIM}	{yTRACE(BVEC3_T); return BVEC3_T;}
bvec4/{DELIM}	{yTRACE(BVEC4_T); return BVEC4_T;}
ivec2/{DELIM}	{yTRACE(IVEC2_T); return IVEC2_T;}
ivec3/{DELIM}	{yTRACE(IVEC3_T); return IVEC3_T;}
ivec4/{DELIM}	{yTRACE(IVEC4_T); return IVEC4_T;}

dp3/{DELIM}	{yTRACE(DP3_F); return DP3_F;}
lit/{DELIM}	{yTRACE(LIT_F); return LIT_F;}
rsq/{DELIM}	{yTRACE(RSQ_F); return RSQ_F;}

"/*"        {
            int c1 = 0; int c2 = yyinput(); int curline = yyline;
            for(;;) {
                if (c2 == EOF) {
                    fprintf(errorFile,
                            "\nLEXICAL ERROR, LINE %d: Unmatched /*\n",
                            curline);
                    errorOccurred = TRUE;
                    yyterminate();
                    }
                if (c1 == '*' && c2== '/')
                    break;
                c1 = c2;
                c2 = yyinput();
                if (c1 == '\n' && c2 != EOF) {
                    yyline++;
                    }
                }
            }
\n          {yyline++;}

{WS}        { /* Your rules go below this rule and above EOF */ }







<<EOF>>     {yyterminate();}

%%
/* Put your own helper functions here */
