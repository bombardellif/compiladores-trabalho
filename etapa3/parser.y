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

%start beginning

%union
{
  HASH *symbol;
  TREE *ast_program;
}

%type <ast_program> beginning program declaration listInt listCharInt arguments command listCommand simpleCommand expression listExpression listIdentifier listOutput aritmeticExpression booleanExpression 


%%
	beginning: program			{ast_program = $1;}
		;

	program: declaration program								
			|
			;

	declaration: KW_INT TK_IDENTIFIER ':' LIT_INTEGER ';'                          		 {$$ = create_tree(TREE_DECL_SINGLE, 0, $1, $2, $4, 0);}
			|	 KW_BOOL TK_IDENTIFIER ':' LIT_INTEGER ';'                               {$$ = create_tree(TREE_DECL_SINGLE, 0, $1, $2, $4, 0);}
			|	 KW_CHAR TK_IDENTIFIER ':' LIT_INTEGER ';'                               {$$ = create_tree(TREE_DECL_SINGLE, 0, $1, $2, $4, 0);}
			|	 KW_CHAR TK_IDENTIFIER ':' LIT_CHAR ';'                                  {$$ = create_tree(TREE_DECL_SINGLE, 0, $1, $2, $4, 0);}
			|  	 KW_REAL TK_IDENTIFIER ':' LIT_INTEGER ';'                               {$$ = create_tree(TREE_DECL_SINGLE, 0, $1, $2, $4, 0);}
			|	 KW_REAL TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                           {$$ = create_tree(TREE_DECL_VECT, 0, $1, $2, $4, NULL);}
			|	 KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                            {$$ = create_tree(TREE_DECL_VECT, 0, $1, $2, $4, NULL);}
			|	 KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                           {$$ = create_tree(TREE_DECL_VECT, 0, $1, $2, $4, NULL);}
			|	 KW_BOOL TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                           {$$ = create_tree(TREE_DECL_VECT, 0, $1, $2, $4, NULL);}
			|	 KW_REAL TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listInt ';'               {$$ = create_tree(TREE_DECL_VECT, 0, $1, $2, $4, $7);}
			|	 KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':'  listInt ';'               {$$ = create_tree(TREE_DECL_VECT, 0, $1, $2, $4, $7);}
			|	 KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listCharInt ';'           {$$ = create_tree(TREE_DECL_VECT, 0, $1, $2, $4, $7);}
			|	 KW_BOOL TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listInt ';'               {$$ = create_tree(TREE_DECL_VECT, 0, $1, $2, $4, $7);}
			|	 KW_INT	TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = create_tree(TREE_DECL_FUNC, 0, $1, $2, $4, $6);}
			|	 KW_REAL TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = create_tree(TREE_DECL_FUNC, 0, $1, $2, $4, $6);}
			|	 KW_CHAR TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = create_tree(TREE_DECL_FUNC, 0, $1, $2, $4, $6);}
			|	 KW_BOOL TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = create_tree(TREE_DECL_FUNC, 0, $1, $2, $4, $6);}
			|	 KW_INT	TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = create_tree(TREE_DECL_FUNC, 0, $1, $2, NULL, $6);}
			|	 KW_REAL TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = create_tree(TREE_DECL_FUNC, 0, $1, $2, NULL, $6);}
			|	 KW_CHAR TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = create_tree(TREE_DECL_FUNC, 0, $1, $2, NULL, $6);}
			|	 KW_BOOL TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = create_tree(TREE_DECL_FUNC, 0, $1, $2, NULL, $6);}
			;

	listInt:	LIT_INTEGER                                                          {$$ = create_tree(TREE_TYPE_INT, $1, 0, 0, 0, 0);}
			|	listInt LIT_INTEGER                                                      {$$ = create_tree(TREE_LIST_SYM, 0, $2, $1, 0, 0);}
			;

	listCharInt:	LIT_INTEGER                                                      {$$ = create_tree(TREE_TYPE_INT, $1, 0, 0, 0, 0);}
			| LIT_CHAR                                                                 {$$ = create_tree(TREE_TYPE_CHAR, $1, 0, 0, 0, 0);}   
			| listCharInt LIT_CHAR                                                     	 {$$ = create_tree(TREE_LIST_SYM, 0, $2, $1, 0, 0);}
			| listCharInt LIT_INTEGER                                                  	 {$$ = create_tree(TREE_LIST_SYM, 0, $2, $1, 0, 0);}
			;

	arguments:  KW_INT TK_IDENTIFIER                                               		 {$$ = create_tree(TREE_LIST_ARG, 0, $3, $4, NULL, 0);}
			|	KW_CHAR TK_IDENTIFIER                                                    {$$ = create_tree(TREE_LIST_ARG, 0, $3, $4, NULL, 0);}
			|	KW_REAL	TK_IDENTIFIER                                                    {$$ = create_tree(TREE_LIST_ARG, 0, $3, $4, NULL, 0);}
			|	KW_BOOL TK_IDENTIFIER                                                    {$$ = create_tree(TREE_LIST_ARG, 0, $3, $4, NULL, 0);}
			|	arguments ',' KW_CHAR TK_IDENTIFIER                                      {$$ = create_tree(TREE_LIST_ARG, 0, $3, $4, $1, 0);}
			|	arguments ',' KW_REAL TK_IDENTIFIER                                      {$$ = create_tree(TREE_LIST_ARG, 0, $3, $4, $1, 0);}
			|	arguments ',' KW_INT TK_IDENTIFIER                                       {$$ = create_tree(TREE_LIST_ARG, 0, $3, $4, $1, 0);}
			|	arguments ',' KW_BOOL TK_IDENTIFIER                                      {$$ = create_tree(TREE_LIST_ARG, 0, $3, $4, $1, 0);}
			;

	command: simpleCommand                                                         {$$ = $1;}
  		|    '{' listCommand '}'                                                   {$$ = $2;}
  		;

 	listCommand: command                                                           {$$ = $1;}
   		| 	listCommand command                                                    {$$ = create_tree(TREE_LIST_COMM, 0, $3, $1, 0, 0);}
  		;

	simpleCommand: ';' /*Comando vazio*/                                           {$$ = create_tree(TREE_COMM_NOP, 0, $1, 0, 0, 0);}
	    | 	KW_INPUT listIdentifier                                                {$$ = create_tree(TREE_COMM_IN, 0, $1, 0, 0, 0);}
	    | 	KW_OUTPUT listOutput                                                   {$$ = create_tree(TREE_COMM_OU, 0, $1, 0, 0, 0);}
	    | 	KW_RETURN expression                                                   {$$ = create_tree(TREE_COMM_RETURN, 0, $1, 0, 0, 0);} /*TREE_COMM_RETURN não havia no tree.h, pus depois*/
	    | 	TK_IDENTIFIER '=' expression                                           {$$ = create_tree(TREE_COMM_ASSIG, 0, $1, $3, 0, 0);}
 	   	| 	TK_IDENTIFIER '[' expression ']' '=' expression                        {$$ = create_tree(TREE_COMM_ASSIG_VEC, $1, $3, $6, 0, 0);}
			/*|   expression === Não se pode chamar uma função fora de atribuições */
	    | 	KW_IF '(' expression ')' command                                       {$$ = create_tree(TREE_COMM_IF_ELSE, 0, $1, $3, $5, NULL);}
 	    | 	KW_IF '(' expression ')' command KW_ELSE command                       {$$ = create_tree(TREE_COMM_IF_ELSE, 0, $1, $3, $5, $6);}
	    | 	KW_WHILE '(' expression ')' command                                    {$$ = create_tree(TREE_COMM_WHILE, 0, $1, $3, $5, 0);}
	    ;

  expression: aritmeticExpression                                                {$$ = $1;}
			| 	booleanExpression                                                {$$ = $1;}
			;

	listExpression: expression                                                     {$$ = $1;}
  		| 	listExpression ',' expression                                          {$$ = create_tree(TREE_LIST_EXPR, 0, $3, $1, 0, 0);}
  		;

	listIdentifier: TK_IDENTIFIER                                                  {$$ = create_tree(TREE_SYMBOL, $1, 0, 0, 0, 0);}
   		| 	listIdentifier  ',' TK_IDENTIFIER                                      {$$ = create_tree(TREE_LIST_SYM, 0, $3, $1, 0, 0);}
   		;

	listOutput: aritmeticExpression                                                {$$ = $1;}
			| 	LIT_STRING                                                             {$$ = create_tree(TREE_TYPE_STRING, $1, 0, 0, 0, 0);}
			| 	listOutput ',' aritmeticExpression                                     {$$ = create_tree(TREE_LIST_OUT, 0, $3, $1, 0, 0);}
			| 	listOutput ',' LIT_STRING                                              {$$ = create_tree(TREE_LIST_OUT, 0, $3, $1, 0, 0, 0);}
			;

	aritmeticExpression: TK_IDENTIFIER                                             {$$ = create_tree(TREE_SYMBOL, $1, 0, 0, 0, 0);}
			| 	TK_IDENTIFIER '[' aritmeticExpression ']'                              {$$ = create_tree(TREE_DECL_VECT, 0, $1, $3, 0, 0);}
			| 	LIT_INTEGER                                                            {$$ = create_tree(TREE_TYPE_INT, $1, 0, 0, 0, 0);}
			|		LIT_CHAR                                                       {$$ = create_tree(TREE_TYPE_CHAR, $1, 0, 0, 0, 0);}
			| 	'(' aritmeticExpression ')'                                            {$$ = $2;}
			|		TK_IDENTIFIER '(' listExpression ')'                               {$$ = create_tree(TREE_DECL_FUNC, 0, $1, $3, 0, 0);}
			/*| 	'-' aritmeticExpression*/
			| 	aritmeticExpression '+' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_ARIT_ADD, 0, $1, 0, $3, 0);}
			| 	aritmeticExpression '-' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_ARIT_SUB, 0, $1, 0, $3, 0);}
			| 	aritmeticExpression '*' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_ARIT_MUL, 0, $1, 0, $3, 0);}
			| 	aritmeticExpression '/' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_ARIT_DIV, 0, $1, 0, $3, 0);}
			;

	booleanExpression: LIT_TRUE                                                    	   {$$ = create_tree(TREE_VAL_TRUE, $1, 0, 0, 0, 0);}
			| 	LIT_FALSE                                                          	   {$$ = create_tree(TREE_VAL_FALSE, $1, 0, 0, 0, 0);}
			| 	aritmeticExpression '<' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_ARIT_LT, 0, $1, 0, $3, 0);}
			| 	aritmeticExpression '>' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_ARIT_GT, 0, $1, 0, $3, 0);}
			| 	aritmeticExpression OPERATOR_LE aritmeticExpression                    {$$ = create_tree(TREE_EXPR_ARIT_LE, 0, $1, 0, $3, 0);}
			| 	aritmeticExpression OPERATOR_GE aritmeticExpression                    {$$ = create_tree(TREE_EXPR_ARIT_GE, 0, $1, 0, $3, 0);}
			| 	aritmeticExpression OPERATOR_EQ aritmeticExpression                    {$$ = create_tree(TREE_EXPR_ARIT_EQ, 0, $1, 0, $3, 0);}
			| 	aritmeticExpression OPERATOR_NE aritmeticExpression                    {$$ = create_tree(TREE_EXPR_ARIT_NE, 0, $1, 0, $3, 0);}
			| 	booleanExpression OPERATOR_AND booleanExpression                       {$$ = create_tree(TREE_EXPR_BOOL_AND, 0, $1, 0, $3, 0);}
			| 	booleanExpression OPERATOR_OR booleanExpression                        {$$ = create_tree(TREE_EXPR_BOOL_OR, 0, $1, 0, $3, 0);}
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
