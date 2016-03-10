/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 1
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 * Compilação: lex scanner.l && gcc lex.yy.c
 * Uso1:       ./a.out
 * Uso2:       ./a.out < file
 */

/* Definitions */
alpha   [A-Za-z]
digit   [0-9]
alphanum  [_0-9A-Za-z]
%{
#include "tokens.h"
#include<stdio.h>
#define END_OF_FILE -1
int scanner_running, scanner_linenumber = 0;
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
[\,|\;|\:|\(\|\)|\[|\]|\{|\}|\+|\-|\*|\/|\<|\>|\=|\!|\&|\$]			{return yytext[0];}

  /* Operadores compostos */
"<="                  {return OPERATOR_LE;}
">="                  {return OPERATOR_GE;}
"=="                  {return OPERATOR_EQ;}
"!="                  {return OPERATOR_NE;}
"&&"                  {return OPERATOR_AND;}
"||"                  {return OPERATOR_OR;}

  /*Ignora space e tab*/
[\ |\	]                { }
  /* Identificadores */
{alpha}{alphanum}*  {return TK_IDENTIFIER;}
  /* Literais */
'.'   {/*fazer algo */}
[0-9]+		    {return LIT_INTEGER;}

\"[0-9|a-z|A-Z|\\n|"\""]*\"	    {return LIT_STRING;}


	/*\"([^\"\\\n]|\\[\"\\n])*\"  printf("Match: %s|", yytext); // O que eh isso? */
  /* Comentários */
  /* New Line */
\n    		       {scanner_linenumber++;}

<<EOF>>     		{scanner_running=0; return END_OF_FILE;}

  /* Erro léxico */
.                   {return TOKEN_ERROR;}



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

#include "main.c"
