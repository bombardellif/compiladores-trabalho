%{
#include<stdio.h>
#include<stdlib.h>
#include "hash.h"
extern FILE *yyin;
%}

/*Tokens e declaracao de tipos*/
%token KW_INT
%token KW_REAL
%token KW_BOOL
%token KW_CHAR
%token KW_IF
%token KW_ELSE
%token KW_WHILE
%token KW_INPUT
%token KW_RETURN
%token KW_OUTPUT
%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR
%token KW_IDENTIFIER
%token LIT_INTEGER
%token LIT_FALSE
%token LIT_TRUE
%token LIT_CHAR
%token LIT_STRING
%token TOKEN_ERROR


%%
	program: declaration ';' program
			|
			;
	declaration: KW_INT ':' KW_IDENTIFIER		/*INT a : 5 */
			|	 KW_INT '(' ')' KW_IDENTIFIER		/* int main () */
			;		
   

%%
	int main(int argc, char* argv[])
	{
		yyin = fopen(argv[1], "r");
		exit (yyparse());
	}
	
	int yyerror() 
    {
   	  	 fprintf(stderr, "Syntax error.\n");
		 exit(3);
    }
