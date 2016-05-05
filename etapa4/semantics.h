/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 4
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#ifndef __SEMANTICS__
#define __SEMANTICS__

#include "semantics_types.h"
#include "tree.h"

extern int semanticFailure;

void semanticsCheckDeclaration(TREE* node);
void semanticsCheckUndeclared(TREE* node);
void semanticsCheckUsage(TREE* node);
void semanticsCheckUsage(TREE* node);
VAL_TYPE semanticsCheckType(TREE* node);

#endif
