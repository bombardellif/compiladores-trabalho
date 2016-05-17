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
    case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL");
    break;
    case TAC_ADD: fprintf(stderr, "TAC_ADD");
    break;
    case TAC_SUB: fprintf(stderr, "TAC_SUB");
    break;
    case TAC_MUL: fprintf(stderr, "TAC_MUL");
    break;
    case TAC_DIV: fprintf(stderr, "TAC_DIV");
    break;
    default: fprintf(stderr, "TAC_DEFAULT");
  }
  fprintf(stderr, ",%s", tac->res->text);
  fprintf(stderr, ",%s", tac->op1->text);
  fprintf(stderr, ",%s)\n", tac->op2->text);
}

void tacPrintListPrev(TAC* tac)
{
  if (!tac)
    return;

  tacPrintSingle(tac);
  tacPrintListPrev(tac->prev);
}

void tacPrintListNext(TAC* tac)
{
  if (!tac)
    return;

  tacPrintSingle(tac);
  tacPrintListNext(tac->next);
}

TAC* tacReverse(TAC* tac)
{
  TAC* t;

  for (t=tac; t->prev; t=t->prev) {
    t->prev->next = t;
  }
  return t;
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

TAC* tacJoin4(TAC *l1, TAC *l2, TAC *l3, TAC *l4)
{
  return tacJoin(tacJoin(tacJoin(l1, l2), l3), l4);
}
