/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 2
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

%{
#include<stdio.h>
#include<stdlib.h>
#include "hash.h"
#include "scanner.h"

extern FILE *yyin;
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
			|  KW_REAL TK_IDENTIFIER ':' LIT_INTEGER ';'
			|	 KW_REAL TK_IDENTIFIER '[' LIT_INTEGER ']' ';'
			|	 KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ';'
			|	 KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']' ';'
			|	 KW_BOOL TK_IDENTIFIER '[' LIT_INTEGER ']' ';'
			|	 KW_REAL TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listInt ';'
			|	 KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':'  listInt ';'
			|	 KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listChar ';'
			|	 KW_BOOL TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listBool ';'
			|	 KW_INT	TK_IDENTIFIER 	'(' arguments ')' command ';'		/*int main () */
			|	 KW_REAL TK_IDENTIFIER 	'(' arguments ')' command ';'
			|	 KW_CHAR TK_IDENTIFIER 	'(' arguments ')' command ';'
			|	 KW_BOOL TK_IDENTIFIER 	'(' arguments ')' command ';'
			|	 KW_INT	TK_IDENTIFIER 	'('  ')' command ';'
			|	 KW_REAL TK_IDENTIFIER 	'('  ')' command ';'
			|	 KW_CHAR TK_IDENTIFIER 	'('  ')' command ';'
			|	 KW_BOOL TK_IDENTIFIER 	'('  ')' command ';'
			;

	listInt:	LIT_INTEGER
			|	listInt LIT_INTEGER
			;

	listChar:	LIT_CHAR
			|	LIT_INTEGER
			|	listChar LIT_CHAR
			|	listChar LIT_INTEGER
			;

	listBool:	LIT_FALSE
			|	LIT_TRUE
			|	listBool LIT_FALSE
			|	listBool LIT_TRUE
			;

	arguments: KW_INT TK_IDENTIFIER
			|	KW_CHAR TK_IDENTIFIER
			|	KW_REAL	TK_IDENTIFIER
			|	KW_BOOL TK_IDENTIFIER
			|	arguments ',' KW_CHAR TK_IDENTIFIER
			|	arguments ',' KW_REAL TK_IDENTIFIER
			|	arguments ',' KW_INT TK_IDENTIFIER
			|	arguments ',' KW_BOOL TK_IDENTIFIER
			;

  command: simpleCommand
      | body
      ;

	body:	'{' listCommand '}'
		  ;

  listCommand: command
      | command listCommand
      ;

	simpleCommand: ';' /*Comando vazio*/
      | KW_INPUT listIdentifier ';'
      | KW_OUTPUT listOutput ';'
      | KW_RETURN expression ';'
      | TK_IDENTIFIER '=' expression ';'
      | TK_IDENTIFIER '[' expression ']' '=' expression ';'
      /*| expression ';' Seria permitido isso?? *TODO* */
      | "if" '(' expression ')' command elsestmt
      | "while" '(' expression ')' command
      ;

  elsestmt: "else" command
      |
      ;

  listIdentifier: TK_IDENTIFIER
      | TK_IDENTIFIER ',' listIdentifier
      ;

  listOutput: aritmeticExpression
      | LIT_STRING
      | aritmeticExpression ',' listOutput
      | LIT_STRING ',' listOutput
      ;

  aritmeticExpression: TK_IDENTIFIER
      | TK_IDENTIFIER '[' aritmeticExpression ']'
      | LIT_INTEGER
      | LIT_CHAR
      | '(' aritmeticExpression ')'
      | '-' aritmeticExpression
      | aritmeticExpression '+' aritmeticExpression
      | aritmeticExpression '-' aritmeticExpression
      | aritmeticExpression '*' aritmeticExpression
      | aritmeticExpression '/' aritmeticExpression
      ;

  booleanExpression: LIT_TRUE
      | LIT_FALSE
      | aritmeticExpression "<=" aritmeticExpression
      | aritmeticExpression ">=" aritmeticExpression
      | aritmeticExpression "==" aritmeticExpression
      | aritmeticExpression "!=" aritmeticExpression
      | booleanExpression "&&" booleanExpression
      | booleanExpression "||" booleanExpression
      ;

  expression: aritmeticExpression
      | booleanExpression
      | TK_IDENTIFIER '(' listExpression ')'
      ;

  listExpression: expression
      | expression ',' listExpression
      ;


%%
	int main(int argc, char* argv[])
	{
		if (argc > 1 && (yyin = fopen(argv[1], "r")))
    {
      initMe();
  		if(yyparse() == 0)
  		{
  			printf("Sucess, this is a program!\nLines: %d\n", getLineNumber());
  			print_hash();
  		}
    } else {
      printf("Usage: ./etapa2 input_filepath\n");
    }
    return 0;
	}

  int yyerror(char *s)
  {
    print_hash(); // So para debugging, apagar depois
    fprintf(stderr, "line %d: %s\n", getLineNumber(), s);
    exit(3);
  }
