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

int semanticsIsCompatible(VAL_TYPE valueType1, VAL_TYPE valueType2);
DATA_TYPE semanticsIsDeclared(char* text);
int semanticsMatchParameters(PARAM_LIST *paramsDecl, TREE *paramsCall);
int semanticsGreaterNumericType(VAL_TYPE type1, VAL_TYPE type2);
PARAM_LIST* semanticsGetParamsTypes(TREE *node);
VAL_TYPE semanticsCheckType(TREE* node);
#endif
