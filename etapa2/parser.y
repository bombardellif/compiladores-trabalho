/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 2
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */
 
%{
#include<stdio.h>
#include<stdlib.h>
#include "hash.h"
extern FILE *yyin;
int scanner_linenumber = 1;
%}


/*Tokens e declaração de tipos*/
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
%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_FALSE
%token LIT_TRUE
%token LIT_CHAR
%token LIT_STRING
%token TOKEN_ERROR

%union
{
	struct hash_node *symbol;
}


%%
	program: declaration program
			|
			;
			
	declaration: KW_INT TK_IDENTIFIER ':' LIT_INTEGER ';'	/*int a : 5 */
			|	 KW_BOOL TK_IDENTIFIER ':' LIT_FALSE ';'
			|	 KW_BOOL TK_IDENTIFIER ':' LIT_TRUE ';'
			|	 KW_CHAR TK_IDENTIFIER ':' LIT_CHAR ';'
			|	 KW_CHAR '*' TK_IDENTIFIER ':' LIT_STRING ';'
			|	 KW_CHAR TK_IDENTIFIER ':' LIT_INTEGER ';'
			| 	 KW_REAL TK_IDENTIFIER ':' LIT_INTEGER ';'
			|	 KW_REAL TK_IDENTIFIER '[' LIT_INTEGER ']'';'
			|	 KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']'';'
			|	 KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']'';'
			|	 KW_BOOL TK_IDENTIFIER '[' LIT_INTEGER ']'';'
			|	 KW_REAL TK_IDENTIFIER '[' LIT_INTEGER ']'':' listInt ';'
			|	 KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']'':'  listInt ';'
			|	 KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']'':' listChar ';'
			|	 KW_BOOL TK_IDENTIFIER '[' LIT_INTEGER ']'':' listBool ';'
			;		
	
	listInt:	' ' LIT_INTEGER listInt
			|
			;
			
	listChar:	' ' LIT_CHAR listChar
			|
			;
			
	listBool:	' ' LIT_FALSE listBool
			|	' ' LIT_TRUE listBool
			|
			;
   

%%
	int main(int argc, char* argv[])
	{
		yyin = fopen(argv[1], "r");
		if(yyparse() == 0)
		{
			printf("Sucess, this is a program!\nLines: %d\n", scanner_linenumber);
			print_hash();
			return 0;
		}
		
	}
	
	int yyerror(char *s) 
    {
    	 print_hash(); // So para debugging, apagar depois
   	  	 fprintf(stderr, "line %d: %s\n", scanner_linenumber, s);
		 exit(3);
    }
