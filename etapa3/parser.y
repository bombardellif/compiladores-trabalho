/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 3
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "scanner.h"

extern FILE *yyin;
FILE *outfile;
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

%left ','
%left '='
%left OPERATOR_AND OPERATOR_OR
%left OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%left '+' '-'
%left '*' '/'

%union
{
  HASH *symbol;
  TREE *ast_program;
}

%type <ast_program> beginnig program declaration listInt listCharInt arguments command listCommand simpleCommand expression listExpression listIdentifier listOutput aritmeticExpression booleanExpression OPERATOR_LE OPERATOR_GE OPERATOR_NE OPERATOR_EQ OPERATOR_AND OPERATOR_OR TOKEN_ERROR

%type <symbol> TK_IDENTIFIER LIT_INTEGER LIT_FALSE LIT_TRUE LIT_CHAR LIT_STRING


%%

  beginnig: program    																{ast_program = $1;} 
      ;

	program: declaration program
			|
			;

	declaration: KW_INT TK_IDENTIFIER ':' LIT_INTEGER ';'                          		 {$$ = 0;}
			|	 KW_BOOL TK_IDENTIFIER ':' LIT_INTEGER ';'                               {$$ = 0;}
			|	 KW_CHAR TK_IDENTIFIER ':' LIT_INTEGER ';'                               {$$ = 0;}
			|	 KW_CHAR TK_IDENTIFIER ':' LIT_CHAR ';'                                  {$$ = 0;}
			|  	 KW_REAL TK_IDENTIFIER ':' LIT_INTEGER ';'                               {$$ = 0;}
			|	 KW_REAL TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                           {$$ = 0;}
			|	 KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                            {$$ = 0;}
			|	 KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                           {$$ = 0;}
			|	 KW_BOOL TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                           {$$ = 0;}
			|	 KW_REAL TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listInt ';'               {$$ = 0;}
			|	 KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':'  listInt ';'               {$$ = 0;}
			|	 KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listCharInt ';'           {$$ = 0;}
			|	 KW_BOOL TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listInt ';'               {$$ = 0;}
			|	 KW_INT	TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = 0;}
			|	 KW_REAL TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = 0;}
			|	 KW_CHAR TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = 0;}
			|	 KW_BOOL TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = 0;}
			|	 KW_INT	TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = 0;}
			|	 KW_REAL TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = 0;}
			|	 KW_CHAR TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = 0;}
			|	 KW_BOOL TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = 0;}
			;

	listInt:	LIT_INTEGER                                                          {$$ = 0;}
			|	listInt LIT_INTEGER                                                      {$$ = 0;}
			;

	listCharInt:	LIT_INTEGER                                                      {$$ = 0;}
			| LIT_CHAR                                                                 {$$ = 0;}
			| listCharInt LIT_CHAR                                                     {$$ = 0;}
			| listCharInt LIT_INTEGER                                                  {$$ = 0;}
			;

	arguments:  KW_INT TK_IDENTIFIER                                               {$$ = 0;}
			|	KW_CHAR TK_IDENTIFIER                                                    {$$ = 0;}
			|	KW_REAL	TK_IDENTIFIER                                                    {$$ = 0;}
			|	KW_BOOL TK_IDENTIFIER                                                    {$$ = 0;}
			|	arguments ',' KW_CHAR TK_IDENTIFIER                                      {$$ = 0;}
			|	arguments ',' KW_REAL TK_IDENTIFIER                                      {$$ = 0;}
			|	arguments ',' KW_INT TK_IDENTIFIER                                       {$$ = 0;}
			|	arguments ',' KW_BOOL TK_IDENTIFIER                                      {$$ = 0;}
			;

	command: simpleCommand                                                         {$$ = 0;}
  		|    '{' listCommand '}'                                                   {$$ = 0;}
  		;

 	listCommand: command                                                           {$$ = 0;}
   		| 	command listCommand                                                    {$$ = 0;}
  		;

	simpleCommand: ';' /*Comando vazio*/                                           {$$ = 0;}
	    | 	KW_INPUT listIdentifier                                                {$$ = 0;}
	    | 	KW_OUTPUT listOutput                                                   {$$ = 0;}
	    | 	KW_RETURN expression                                                   {$$ = 0;}
	    | 	TK_IDENTIFIER '=' expression                                           {$$ = 0;}
 	   	| 	TK_IDENTIFIER '[' expression ']' '=' expression                        {$$ = 0;}
			/*|   expression === Não se pode chamar uma função fora de atribuições */
	    | 	KW_IF '(' expression ')' command                                       {$$ = 0;}
 	    | 	KW_IF '(' expression ')' command KW_ELSE command                       {$$ = 0;}
	    | 	KW_WHILE '(' expression ')' command                                    {$$ = 0;}
	    ;

  expression: aritmeticExpression                                                {$$ = 0;}
			| 	booleanExpression                                                      {$$ = 0;}
			;

	listExpression: expression                                                     {$$ = 0;}
  		| 	listExpression ',' expression                                          {$$ = 0;}
  		;

	listIdentifier: TK_IDENTIFIER                                                  {$$ = 0;}
   		| 	listIdentifier  ',' TK_IDENTIFIER                                      {$$ = 0;}
   		;

	listOutput: aritmeticExpression                                                {$$ = 0;}
			| 	LIT_STRING                                                             {$$ = 0;}
			| 	listOutput ',' aritmeticExpression                                     {$$ = 0;}
			| 	listOutput ',' LIT_STRING                                              {$$ = 0;}
			;

	aritmeticExpression: TK_IDENTIFIER                                             {$$ = 0;}
			| 	TK_IDENTIFIER '[' aritmeticExpression ']'                              {$$ = 0;}
			| 	LIT_INTEGER                                                            {$$ = 0;}
			|		LIT_CHAR                                                               {$$ = 0;}
			| 	'(' aritmeticExpression ')'                                            {$$ = 0;}
			|		TK_IDENTIFIER '(' listExpression ')'                                   {$$ = 0;}
			/*| 	'-' aritmeticExpression*/
			| 	aritmeticExpression '+' aritmeticExpression                            {$$ = 0;}
			| 	aritmeticExpression '-' aritmeticExpression                            {$$ = 0;}
			| 	aritmeticExpression '*' aritmeticExpression                            {$$ = 0;}
			| 	aritmeticExpression '/' aritmeticExpression                            {$$ = 0;}
			;

	booleanExpression: LIT_TRUE                                                    {$$ = 0;}
			| 	LIT_FALSE                                                              {$$ = 0;}
			| 	aritmeticExpression '<' aritmeticExpression                            {$$ = 0;}
			| 	aritmeticExpression '>' aritmeticExpression                            {$$ = 0;}
			| 	aritmeticExpression OPERATOR_LE aritmeticExpression                    {$$ = 0;}
			| 	aritmeticExpression OPERATOR_GE aritmeticExpression                    {$$ = 0;}
			| 	aritmeticExpression OPERATOR_EQ aritmeticExpression                    {$$ = 0;}
			| 	aritmeticExpression OPERATOR_NE aritmeticExpression                    {$$ = 0;}
			| 	booleanExpression OPERATOR_AND booleanExpression                       {$$ = 0;}
			| 	booleanExpression OPERATOR_OR booleanExpression                        {$$ = 0;}
			;


%%
	int write_to_file(const char* text)
	{
		return fprintf(outfile, text);
	}
	

	int main(int argc, char* argv[])
	{
		if (argc > 2 && (yyin = fopen(argv[1], "r")) && (outfile = fopen(argv[2], "w")))
    {
      initMe();
  		if(yyparse() == 0)
  		{
  			printf("Sucess, this is a program!\nLines: %d\n", getLineNumber());
        printf("##### HASH #####\n");
        print_hash();
        printf("###############\n");
		// Descompila
		decompile(ast_program, write_to_file);
  		}
    } else {
      printf("Usage: ./etapa3 input_filepath output_filepath\n");
    }
    exit(0);
	}

  int yyerror(char *s)
  {
    fprintf(stderr, "line %d: %s\n", getLineNumber(), s);
    print_hash();
    exit(3);
  }
