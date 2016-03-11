/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 1
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 * Uso1:       ./a.out
 * Uso2:       ./a.out < file
 */

/* Definitions */
alpha   [A-Za-z]
digit   [0-9]
alphanum  [_0-9A-Za-z]
%{
#include "tokens.h"
#include "utils.h"
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
int scanner_running, scanner_linenumber = 0;

void addIdentifierToSymbolTable(char *text);
void addCharToSymbolTable(char *text);
void addIntegerToSymbolTable(char *text);
void addStringToSymbolTable(char *text);
%}

/* Ambiente para comentário - o ambiente padrão, implícito, é initial */
%x COMMENT

/* Rules */
%%
  /* Palavras reservadas */
"int"                 {return KW_INT;}
"real"                {return KW_REAL;}
"TRUE"                {return LIT_TRUE;}
"FALSE"               {return LIT_FALSE;}
"bool"                {return KW_BOOL;}
"char"                {return KW_CHAR;}
"if"                  {return KW_IF;}
"else"                {return KW_ELSE;}
"while"               {return KW_WHILE;}
"input"               {return KW_INPUT;}
"output"              {return KW_OUTPUT;}
"return"              {return KW_RETURN;}

  /* Ignora comentários */
"/*"                {BEGIN(COMMENT);}
<COMMENT>"*/"       {BEGIN(INITIAL);}
<COMMENT>.          {}
"//".*              {}
<COMMENT>\n		{scanner_linenumber++;}

  /* Caracteres especiais: retornamos o próprio código ASCII dele */
[,;:\(\)\[\]\{\}\+\-\*\/<>=!&\$]			{return yytext[0];}

  /* Operadores compostos */
"<="                  {return OPERATOR_LE;}
">="                  {return OPERATOR_GE;}
"=="                  {return OPERATOR_EQ;}
"!="                  {return OPERATOR_NE;}
"&&"                  {return OPERATOR_AND;}
"||"                  {return OPERATOR_OR;}

  /*Ignora space e tab*/
[\t ]									{ }

  /* Identificadores */
{alpha}{alphanum}*  	{hash_add(SYMBOL_IDENTIFIER, yytext); return TK_IDENTIFIER;}

  /* Literais */
'.'   								{return LIT_CHAR;}
[0-9]+		    				{hash_add(SYMBOL_LITERAL_INT, yytext); return LIT_INTEGER;}
	/* Literal String: Captura se (i) começar com áspas;
		(ii) conter dentro: qualquer coisa que não seja
				áspas, barra invertida ou quebra de linha
			OU conter dentro: barra invertida seguido de
				caracter áspas ou mais uma barra invertida ou character n; e
		(iii) terminar com áspas. */
\"([^\"\\\n]|\\[\"\\n])*\"	{addStringToSymbolTable(yytext); return LIT_STRING;}

  /* New Line */
\n    		       {scanner_linenumber++;}

^D     		{scanner_running=0;}


  /* Erro léxico */
.+							{return TOKEN_ERROR;}

%%

/* Subroutines */
int yywrap(void) {
  scanner_running = 0;
  return 1;
}

int getLineNumber(void) {
  return scanner_linenumber;
}

int isRunning(void) {
  return scanner_running;
}

void initMe(void) {
  scanner_running = 1;
  scanner_linenumber = 0;
}

void addIdentifierToSymbolTable(char *text) {
	char *identifierName;
	int inputSize;

	// aloca nova string para o nome do identificador
	inputSize = strlen(text);
	identifierName = (char*) malloc(inputSize * sizeof(char));
	strncpy(identifierName, text, inputSize);

	// adiciona à tabela de símbolos
}

void addCharToSymbolTable(char *text) {
	// adiciona à tabela de símbolos
	text[1];
}

void addIntegerToSymbolTable(char *text) {
	int value;

	value = atoi(text);
	// adiciona à tabela de símbolos
}

void addStringToSymbolTable(char *text) {
	char *stringValue;
	int inputSize;

	inputSize = strlen(text);
	// remove áspas
	text[inputSize-1] = '\0';
	text++;
	// aloca nova string para o literal lido
	stringValue = (char*) malloc((inputSize-2) * sizeof(char));

	// trata as barras invertidas
	stripSlashes(stringValue, text);

	// adiciona à tabela de símbolos
}
