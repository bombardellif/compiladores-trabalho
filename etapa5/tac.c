/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 5
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#include "tac.h"

#include <stdlib.h>
#include <stdio.h>

TAC* tacCreate(int type, HASH *res, HASH *op1, HASH *op2)
{
  TAC *newTac;

  newTac = (TAC*) calloc(1, sizeof(TAC));
  newTac->type = type;
  newTac->res = res;
  newTac->op1 = op1;
  newTac->op2 = op2;

  return newTac;
}

void tacPrintSingle(TAC* tac)
{
  if (!tac)
    return;

  fprintf(stderr, "TAC(");
  switch (tac->type) {
    case TAC_SYMBOL:
      fprintf(stderr, "TAC_SYMBOL");
    break;
    case TAC_ADD:
      fprintf(stderr, "TAC_ADD");
    break;
    default:
      fprintf(stderr, "TAC_DEFAULT");
  }
  fprintf(stderr, ",%s", tac->res->text);
  fprintf(stderr, ",_");
  fprintf(stderr, ",_)");
}

void tacPrintListPrev(TAC* tac)
{
  if (!tac)
    return;

  tacPrintSingle(tac);
  tacPrintListPrev(tac->prev);
}

TAC* tacJoin(TAC *l1, TAC *l2)
{
  TAC *temp;

  if (!l1)
    return l2;
  if (!l2)
    return l1;

  for (temp=l2; temp->prev; temp = temp->prev) ;

  temp->prev = l1;

  return l2;
}
