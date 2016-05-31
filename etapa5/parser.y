/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 4
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "hash.h"
#include "tree.h"
#include "semantics.h"
#include "tac.h"
#include "code-gen.h"

extern FILE *yyin;
TREE *ast_program = NULL;
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
%token <symbol> TK_IDENTIFIER
%token <symbol> LIT_INTEGER
%token <symbol> LIT_FALSE
%token <symbol> LIT_TRUE
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING
%token TOKEN_ERROR
%token ';'

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
  TREE *ast;
}

%type <ast> beginning program declaration listInt listCharInt arguments command listCommand simpleCommand expression listExpression listIdentifier listOutput aritmeticExpression booleanExpression


%%
	beginning: program			{ ast_program = $1;}
      |                   {ast_program = NULL;}   /* Programa vazio*/
		  ;

	program: declaration                {$$ = create_tree(TREE_PROGRAM, 0, $1, 0, 0, 0);}
      | declaration program           {$$ = create_tree(TREE_PROGRAM, 0, $1, $2, 0, 0);}
			;

	declaration: KW_INT TK_IDENTIFIER ':' LIT_INTEGER ';'                          {$$ = create_tree(TREE_DECL_SINGLE, 0, create_leaf(TREE_TYPE_INT), create_leaf_symbol($2), create_leaf_symbol($4), NULL);}
			|	 KW_BOOL TK_IDENTIFIER ':' LIT_INTEGER ';'                               {$$ = create_tree(TREE_DECL_SINGLE, 0, create_leaf(TREE_TYPE_BOOL), create_leaf_symbol($2), create_leaf_symbol($4), NULL);}
			|	 KW_CHAR TK_IDENTIFIER ':' LIT_INTEGER ';'                               {$$ = create_tree(TREE_DECL_SINGLE, 0, create_leaf(TREE_TYPE_CHAR), create_leaf_symbol($2), create_leaf_symbol($4), NULL);}
			|	 KW_CHAR TK_IDENTIFIER ':' LIT_CHAR ';'                                  {$$ = create_tree(TREE_DECL_SINGLE, 0, create_leaf(TREE_TYPE_CHAR), create_leaf_symbol($2), create_leaf_symbol($4), NULL);}
			|  KW_REAL TK_IDENTIFIER ':' LIT_INTEGER ';'                               {$$ = create_tree(TREE_DECL_SINGLE, 0, create_leaf(TREE_TYPE_REAL), create_leaf_symbol($2), create_leaf_symbol($4), NULL);}
			|	 KW_REAL TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                           {$$ = create_tree(TREE_DECL_VECT, 0, create_leaf(TREE_TYPE_REAL), create_leaf_symbol($2), create_leaf_symbol($4), NULL);}
			|	 KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                            {$$ = create_tree(TREE_DECL_VECT, 0, create_leaf(TREE_TYPE_INT), create_leaf_symbol($2), create_leaf_symbol($4), NULL);}
			|	 KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                           {$$ = create_tree(TREE_DECL_VECT, 0, create_leaf(TREE_TYPE_CHAR), create_leaf_symbol($2), create_leaf_symbol($4), NULL);}
			|	 KW_BOOL TK_IDENTIFIER '[' LIT_INTEGER ']' ';'                           {$$ = create_tree(TREE_DECL_VECT, 0, create_leaf(TREE_TYPE_BOOL), create_leaf_symbol($2), create_leaf_symbol($4), NULL);}
			|	 KW_REAL TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listCharInt ';'               {$$ = create_tree(TREE_DECL_VECT, 0, create_leaf(TREE_TYPE_REAL), create_leaf_symbol($2), create_leaf_symbol($4), $7);}
			|	 KW_INT TK_IDENTIFIER '[' LIT_INTEGER ']' ':'  listCharInt ';'               {$$ = create_tree(TREE_DECL_VECT, 0, create_leaf(TREE_TYPE_INT), create_leaf_symbol($2), create_leaf_symbol($4), $7);}
			|	 KW_CHAR TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listCharInt ';'           {$$ = create_tree(TREE_DECL_VECT, 0, create_leaf(TREE_TYPE_CHAR), create_leaf_symbol($2), create_leaf_symbol($4), $7);}
			|	 KW_BOOL TK_IDENTIFIER '[' LIT_INTEGER ']' ':' listInt ';'               {$$ = create_tree(TREE_DECL_VECT, 0, create_leaf(TREE_TYPE_BOOL), create_leaf_symbol($2), create_leaf_symbol($4), $7);}
			|	 KW_INT	TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = create_tree(TREE_DECL_FUNC, 0, create_leaf(TREE_TYPE_INT), create_leaf_symbol($2), $4, $6);}
			|	 KW_REAL TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = create_tree(TREE_DECL_FUNC, 0, create_leaf(TREE_TYPE_REAL), create_leaf_symbol($2), $4, $6);}
			|	 KW_CHAR TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = create_tree(TREE_DECL_FUNC, 0, create_leaf(TREE_TYPE_CHAR), create_leaf_symbol($2), $4, $6);}
			|	 KW_BOOL TK_IDENTIFIER 	'(' arguments ')' command ';'                    {$$ = create_tree(TREE_DECL_FUNC, 0, create_leaf(TREE_TYPE_BOOL), create_leaf_symbol($2), $4, $6);}
			|	 KW_INT	TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = create_tree(TREE_DECL_FUNC, 0, create_leaf(TREE_TYPE_INT), create_leaf_symbol($2), NULL, $5);}
			|	 KW_REAL TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = create_tree(TREE_DECL_FUNC, 0, create_leaf(TREE_TYPE_REAL), create_leaf_symbol($2), NULL, $5);}
			|	 KW_CHAR TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = create_tree(TREE_DECL_FUNC, 0, create_leaf(TREE_TYPE_CHAR), create_leaf_symbol($2), NULL, $5);}
			|	 KW_BOOL TK_IDENTIFIER 	'('  ')' command ';'                             {$$ = create_tree(TREE_DECL_FUNC, 0, create_leaf(TREE_TYPE_BOOL), create_leaf_symbol($2), NULL, $5);}
			;

	listInt:	LIT_INTEGER                                                          {$$ = create_tree(TREE_LIST_SYM, 0, create_leaf_symbol($1), NULL, 0, 0);}
			|	LIT_INTEGER listInt                                                      {$$ = create_tree(TREE_LIST_SYM, 0, create_leaf_symbol($1), $2, 0, 0);}
			;

	listCharInt:	LIT_INTEGER                                                      {$$ = create_tree(TREE_LIST_SYM, 0, create_leaf_symbol($1), NULL, 0, 0);}
			| LIT_CHAR                                                                 {$$ = create_tree(TREE_LIST_SYM, 0, create_leaf_symbol($1), NULL, 0, 0);}
			| LIT_CHAR listCharInt                                                     {$$ = create_tree(TREE_LIST_SYM, 0, create_leaf_symbol($1), $2, 0, 0);}
			| LIT_INTEGER listCharInt                                                  {$$ = create_tree(TREE_LIST_SYM, 0, create_leaf_symbol($1), $2, 0, 0);}
			;

	arguments:  KW_INT TK_IDENTIFIER                                               {$$ = create_tree(TREE_LIST_ARG, 0, create_leaf(TREE_TYPE_INT), create_leaf_symbol($2), NULL, 0);}
			|	KW_REAL TK_IDENTIFIER                                                    {$$ = create_tree(TREE_LIST_ARG, 0, create_leaf(TREE_TYPE_REAL), create_leaf_symbol($2), NULL, 0);}
			|	KW_CHAR	TK_IDENTIFIER                                                    {$$ = create_tree(TREE_LIST_ARG, 0, create_leaf(TREE_TYPE_CHAR), create_leaf_symbol($2), NULL, 0);}
			|	KW_BOOL TK_IDENTIFIER                                                    {$$ = create_tree(TREE_LIST_ARG, 0, create_leaf(TREE_TYPE_BOOL), create_leaf_symbol($2), NULL, 0);}
			|	KW_INT TK_IDENTIFIER ',' arguments                                       {$$ = create_tree(TREE_LIST_ARG, 0, create_leaf(TREE_TYPE_INT), create_leaf_symbol($2), $4, 0);}
			|	KW_REAL TK_IDENTIFIER ',' arguments                                      {$$ = create_tree(TREE_LIST_ARG, 0, create_leaf(TREE_TYPE_REAL), create_leaf_symbol($2), $4, 0);}
			|	KW_CHAR TK_IDENTIFIER ',' arguments                                      {$$ = create_tree(TREE_LIST_ARG, 0, create_leaf(TREE_TYPE_CHAR), create_leaf_symbol($2), $4, 0);}
			|	KW_BOOL TK_IDENTIFIER ',' arguments                                      {$$ = create_tree(TREE_LIST_ARG, 0, create_leaf(TREE_TYPE_BOOL), create_leaf_symbol($2), $4, 0);}
			;

	command: simpleCommand                                                         {$$ = create_tree(TREE_LIST_COMM, 0, $1, NULL, 0, 0);}
  		|   '{' listCommand '}'                                                    {$$ = $2;}
  		;

 	listCommand: command                                                           {$$ = create_tree(TREE_LIST_COMM, 0, $1, NULL, 0, 0);}
   		| 	command listCommand                                                    {$$ = create_tree(TREE_LIST_COMM, 0, $1, $2, 0, 0);}
  		;

	simpleCommand: ';' /*Comando vazio*/                                           {$$ = create_leaf(TREE_COMM_NOP);}
	    | 	KW_INPUT listIdentifier                                                {$$ = create_tree(TREE_COMM_IN, 0, $2, 0, 0, 0);}
	    | 	KW_OUTPUT listOutput                                                   {$$ = create_tree(TREE_COMM_OUT, 0, $2, 0, 0, 0);}
	    | 	KW_RETURN expression                                                   {$$ = create_tree(TREE_COMM_RETURN, 0, $2, 0, 0, 0);} /*TREE_COMM_RETURN não havia no tree.h, pus depois*/
	    | 	TK_IDENTIFIER '=' expression                                           {$$ = create_tree(TREE_COMM_ASSIG, 0, create_leaf_symbol($1), $3, 0, 0);}
 	   	| 	TK_IDENTIFIER '[' expression ']' '=' expression                        {$$ = create_tree(TREE_COMM_ASSIG_VEC, 0, create_leaf_symbol($1), $3, $6, 0);}
			/*|   expression === Não se pode chamar uma função fora de atribuições */
	    | 	KW_IF '(' expression ')' command                                       {$$ = create_tree(TREE_COMM_IF_ELSE, 0, $3, $5, NULL, 0);}
 	    | 	KW_IF '(' expression ')' command KW_ELSE command                       {$$ = create_tree(TREE_COMM_IF_ELSE, 0, $3, $5, $7, 0);}
	    | 	KW_WHILE '(' expression ')' command                                    {$$ = create_tree(TREE_COMM_WHILE, 0, $3, $5, 0, 0);}
	    ;

  expression: aritmeticExpression                                                {$$ = $1;}
			| 	booleanExpression                                                      {$$ = $1;}
			;

	listExpression: expression                                                     {$$ = create_tree(TREE_LIST_EXPR, 0, $1, NULL, 0, 0);}
  		| 	expression ',' listExpression                                          {$$ = create_tree(TREE_LIST_EXPR, 0, $1, $3, 0, 0);}
  		;

	listIdentifier: TK_IDENTIFIER                                                  {$$ = create_tree(TREE_LIST_EXPR, 0, create_leaf_symbol($1), NULL, 0, 0);}
   		| 	TK_IDENTIFIER ',' listIdentifier                                       {$$ = create_tree(TREE_LIST_EXPR, 0, create_leaf_symbol($1), $3, 0, 0);}
   		;

	listOutput: aritmeticExpression                                                {$$ = create_tree(TREE_LIST_OUT, 0, $1, NULL, 0, 0);}
			| 	LIT_STRING                                                             {$$ = create_tree(TREE_LIST_OUT, 0, create_leaf_symbol($1), NULL, 0, 0);}
			| 	aritmeticExpression ',' listOutput                                     {$$ = create_tree(TREE_LIST_OUT, 0, $1, $3, 0, 0);}
			| 	LIT_STRING ',' listOutput                                              {$$ = create_tree(TREE_LIST_OUT, 0, create_leaf_symbol($1), $3, 0, 0);}
			;

	aritmeticExpression: TK_IDENTIFIER                                             {$$ = create_leaf_symbol($1);}
			| 	TK_IDENTIFIER '[' aritmeticExpression ']'                              {$$ = create_tree(TREE_EXPR_ARIT_VEC_READ, 0, create_leaf_symbol($1), $3, 0, 0);}
			| 	LIT_INTEGER                                                            {$$ = create_leaf_symbol($1);}
			|		LIT_CHAR                                                               {$$ = create_leaf_symbol($1);}
			| 	'(' aritmeticExpression ')'                                            {$$ = $2;}
			|		TK_IDENTIFIER '(' listExpression ')'                                   {$$ = create_tree(TREE_EXPR_ARIT_FUNCALL, 0, create_leaf_symbol($1), $3, 0, 0);}
			/*| 	'-' aritmeticExpression*/
			| 	aritmeticExpression '+' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_ARIT_ADD, 0, $1, $3, 0, 0);}
			| 	aritmeticExpression '-' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_ARIT_SUB, 0, $1, $3, 0, 0);}
			| 	aritmeticExpression '*' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_ARIT_MUL, 0, $1, $3, 0, 0);}
			| 	aritmeticExpression '/' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_ARIT_DIV, 0, $1, $3, 0, 0);}
			;

	booleanExpression: LIT_TRUE                                                    {$$ = create_leaf(TREE_VAL_TRUE);}
			| 	LIT_FALSE                                                          	   {$$ = create_leaf(TREE_VAL_FALSE);}
      |   '(' booleanExpression ')'                                              {$$ = $2;}
			| 	aritmeticExpression '<' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_BOOL_LT, 0, $1, $3, 0, 0);}
			| 	aritmeticExpression '>' aritmeticExpression                            {$$ = create_tree(TREE_EXPR_BOOL_GT, 0, $1, $3, 0, 0);}
			| 	aritmeticExpression OPERATOR_LE aritmeticExpression                    {$$ = create_tree(TREE_EXPR_BOOL_LE, 0, $1, $3, 0, 0);}
			| 	aritmeticExpression OPERATOR_GE aritmeticExpression                    {$$ = create_tree(TREE_EXPR_BOOL_GE, 0, $1, $3, 0, 0);}
			| 	aritmeticExpression OPERATOR_EQ aritmeticExpression                    {$$ = create_tree(TREE_EXPR_BOOL_EQ, 0, $1, $3, 0, 0);}
			| 	aritmeticExpression OPERATOR_NE aritmeticExpression                    {$$ = create_tree(TREE_EXPR_BOOL_NE, 0, $1, $3, 0, 0);}
			| 	booleanExpression OPERATOR_AND booleanExpression                       {$$ = create_tree(TREE_EXPR_BOOL_AND, 0, $1, $3, 0, 0);}
			| 	booleanExpression OPERATOR_OR booleanExpression                        {$$ = create_tree(TREE_EXPR_BOOL_OR, 0, $1, $3, 0, 0);}
			;


%%

	int main(int argc, char* argv[])
	{
		  if (argc > 1)
      {
          if(yyin = fopen(argv[1], "r"))
          {
              initMe();
          		if(yyparse() == 0)
          		{
          			printf("Syntax is correct!\nLines: %d\n", getLineNumber());
                printf("############### HASH ###############\n");
                print_hash();
                printf("############### TREE ###############\n");
                print_tree(ast_program,0);
                printf("############### SEMANTICS ###############\n");
                semanticsCheckVariables(ast_program);
                semanticsCheckType(ast_program);

                if(semanticFailure) {
                    printf("Compilation failed due to semantic errors.\n");
                    exit(4);
                } else
                	printf("No semantic errors.\n");

                printf("#### GERAÇÃO DE CÓDIGO INTERMEDIÁRIO ####\n");
                initSymbolTable();
                TAC* tac_program = generateCode(ast_program);
                tacPrintListNext(tacReverse(tac_program));

                /*
                printf("###########################################################################\n");
              	Descompila
              	decompile(ast_program, outfile);
                */
          		}
          }
          else
          {
              printf("File does not exist!\n");
              exit(2);
          }
    }
    else {
        printf("File not informed!\nUsage: ./etapa5 input_filepath\n");
        exit(1);
        }
    exit(0);
	}

  int yyerror(char *s)
  {
    fprintf(stderr, "line %d: %s\n", getLineNumber(), s);
    print_hash();
    exit(3);
  }
