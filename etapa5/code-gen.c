/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 5
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#include "code-gen.h"

#include <stdlib.h>

TAC* makeBinOp(int type, TAC *code0, TAC *code1)
{
  return tacJoin(tacJoin(code0, code1),
            tacCreate(type, hash_make_temp(), code0 ? code0->res : 0, code1 ? code1->res : 0));
}

TAC* makeIfThen(TAC *code0, TAC *code1)
{
  TAC *newIf, *newTarget;
  HASH *newLabel;

  newLabel = hash_make_label();
  newIf = tacCreate(TAC_IFZ, newLabel, code0?code0->res:0, 0);
  newIf->prev = code0;
  code1 = tacJoin(newIf, code1);
  newTarget = tacCreate(TAC_LABEL, newLabel, 0, 0);
  newTarget->prev = code1;

  return newTarget;
}

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
    case TREE_COMM_ASSIG:
      return tacJoin(code[0],
            tacCreate(TAC_MOVE, node->symbol, code[0]?code[0]->res:0, 0));
    case TREE_COMM_IF_ELSE:
      return makeIfThen(code[0], code[1]);
    case TREE_EXPR_ARIT_ADD:
      return makeBinOp(TAC_ADD, code[0], code[1]);
    case TREE_EXPR_ARIT_SUB:
      return makeBinOp(TAC_SUB, code[0], code[1]);
    case TREE_EXPR_ARIT_MUL:
      return makeBinOp(TAC_MUL, code[0], code[1]);
    case TREE_EXPR_ARIT_DIV:
      return makeBinOp(TAC_DIV, code[0], code[1]);
    default:
    break;
  }

  return tacJoin4(code[0], code[1], code[2], code[3]);
}
