/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 5
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#include "code-gen.h"

#include <stdlib.h>

TAC* generateCode(TREE *node)
{
  int i;
  TAC *code[MAX_CHILDREN];

  if (!node)
    return NULL;

  for (i=0; i<MAX_CHILDREN; i++) {
    if (node->children[i])
      code[i] = generateCode(node->children[i]);
    else
      code[i] = 0;
  }

  switch (node->type) {
    case TREE_SYMBOL:
      return tacCreate(TAC_SYMBOL, node->symbol, 0, 0);
    case TREE_EXPR_ARIT_ADD:
      // TODO Join it all
      return tacJoin(
        tacJoin(code[0], code[1]),
        tacCreate(TAC_ADD, makeTemp(), code[0] ? code[0]->res : 0, code[1] ? code[1]->res : 0)
      );
  }

  return tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]), code[3]);
}
