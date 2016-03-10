/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 1
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Faustini ()
 */

/* Definitions */
alpha   [A-Za-z]
digit   [0-9]
alphanum  [_0-9A-Za-z]
%{
#include "tokens.h"
int scanner_running, scanner_linenumber;
%}
/* Rules */
%%
  /* Palavras reservadas */
int   {/*fazer algo, simplesmente: return KW_INT; ??? */}
real  {/*fazer algo */}
TRUE  {/*fazer algo */}
FALSE {/*fazer algo */}
  /* Caracteres especiais */
,     {/*fazer algo */}
;     {/*fazer algo */}
  /* Operadores Compostos */
=    {/*fazer algo */}
  /* Identificadores */
{alpha}{alphanum}*  {/*fazer algo */}
  /* Literais */
'.'   {/*fazer algo */}
\"([^\"\\\n]|\\[\"\\n])*\"  printf("Match: %s|", yytext);
  /* Comentários */
  /* New Line */
\n    {/*fazer algo */}
  /* Erro léxico */
.     {/*fazer algo */}
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
