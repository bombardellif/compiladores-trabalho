/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 2
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

/* Definitions */
alpha   [A-Za-z]
digit   [0-9]
alphanum  [_0-9A-Za-z]
%{
#include "utils.h"
#include "y.tab.h"
#include "hash.h"
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
int scanner_running;
int scanner_linenumber;

/*O retorno, antes, era void; mudei para HASH*. Assim posso usar a	atribuição para yylval.symbol */
HASH* addIdentifierToSymbolTable(char *text);
HASH* addCharToSymbolTable(char *text);
HASH* addIntegerToSymbolTable(char *text);
HASH* addStringToSymbolTable(char *text);
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
{alpha}{alphanum}*  	{yylval.symbol = addIdentifierToSymbolTable(yytext); return TK_IDENTIFIER;}

  /* Literais */
'.'   								{yylval.symbol = addCharToSymbolTable(yytext); return LIT_CHAR;}
[0-9]+		    				{yylval.symbol = addIntegerToSymbolTable(yytext); return LIT_INTEGER;}
	/* Literal String: Captura se (i) começar com áspas;
		(ii) conter dentro: qualquer coisa que não seja
				áspas, barra invertida ou quebra de linha
			OU conter dentro: barra invertida seguido de
				caracter áspas ou mais uma barra invertida ou character n; e
		(iii) terminar com áspas. */
\"([^\"\\\n]|\\[\"\\n])*\"	{yylval.symbol = addStringToSymbolTable(yytext); return LIT_STRING;}

  /* New Line */
\n    		       {scanner_linenumber++;}

  /* Erro léxico */
.							{printf("error token: %s on line %d\n", yytext, scanner_linenumber);  return TOKEN_ERROR;}

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
  scanner_linenumber = 1;
  init_hash();
}

HASH* addIdentifierToSymbolTable(char *text) {
	char *identifierName;
	int inputSize;
	HASH* node;

	// aloca nova string para o nome do identificador
	inputSize = strlen(text)+1;
	identifierName = (char*) malloc(inputSize * sizeof(char));
	strncpy(identifierName, text, inputSize);

	// adiciona à tabela de símbolos
  	node=hash_add(SYMBOL_IDENTIFIER, identifierName);
  	return node;
}

HASH* addCharToSymbolTable(char *text) {
  char* charValue;
  HASH* node;

  charValue = (char*) malloc(sizeof(char)*2);
  charValue[0] = text[1];
  charValue[1] = '\0';
	// adiciona à tabela de símbolos
  node=hash_add(SYMBOL_LITERAL_CHAR, charValue);
  return node;
}

HASH* addIntegerToSymbolTable(char *text) {
  int inputSize;
  char *integerInStr;
  HASH* node;

  inputSize = strlen(text)+1;
  integerInStr = (char*) malloc(inputSize * sizeof(char));
  strncpy(integerInStr, text, inputSize);

	// adiciona à tabela de símbolos
  node = hash_add(SYMBOL_LITERAL_INT, integerInStr);
  return node;
}

HASH* addStringToSymbolTable(char *text) {
	char *stringValue;
	int inputSize;
	HASH* node;

	inputSize = strlen(text)+1;
	// remove áspas
	text[inputSize-2] = '\0';
	text++;
	// aloca nova string para o literal lido
	stringValue = (char*) malloc((inputSize-2) * sizeof(char));

	// trata as barras invertidas
	stripSlashes(stringValue, text);

	// adiciona à tabela de símbolos
  	node=hash_add(SYMBOL_LITERAL_STRING, stringValue);
  	return node;
}
