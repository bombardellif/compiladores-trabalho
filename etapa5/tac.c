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
    case TAC_MOVE: fprintf(stderr, "TAC_MOVE");
    break;
    case TAC_STRIDX: fprintf(stderr, "TAC_STRIDX");
    break;
    case TAC_LOADIDX: fprintf(stderr, "TAC_LOADIDX");
    break;
    case TAC_ADD: fprintf(stderr, "TAC_ADD");
    break;
    case TAC_SUB: fprintf(stderr, "TAC_SUB");
    break;
    case TAC_MUL: fprintf(stderr, "TAC_MUL");
    break;
    case TAC_DIV: fprintf(stderr, "TAC_DIV");
    break;
    case TAC_LABEL: fprintf(stderr, "TAC_LABEL");
    break;
    case TAC_IFZ: fprintf(stderr, "TAC_IFZ");
    break;
    case TAC_BEGINFUN: fprintf(stderr, "TAC_BEGINFUN");
    break;
    case TAC_ENDFUN: fprintf(stderr, "TAC_ENDFUN");
    break;
    case TAC_JUMP: fprintf(stderr, "TAC_JUMP");
    break;
    case TAC_CALL: fprintf(stderr, "TAC_CALL");
    break;
    case TAC_ARG: fprintf(stderr, "TAC_ARG");
    break;
    case TAC_RET: fprintf(stderr, "TAC_RET");
    break;
    case TAC_PRINT: fprintf(stderr, "TAC_PRINT");
    break;
    case TAC_READ: fprintf(stderr, "TAC_READ");
    break;
    case TAC_NOP: fprintf(stderr, "TAC_NOP");
    break;
    case TAC_ANEG: fprintf(stderr, "TAC_ANEG");
    break;
    case TAC_LTZ: fprintf(stderr, "TAC_LTZ");
    break;
    case TAC_GTZ: fprintf(stderr, "TAC_GTZ");
    break;
    case TAC_LEZ: fprintf(stderr, "TAC_LEZ");
    break;
    case TAC_GEZ: fprintf(stderr, "TAC_GEZ");
    break;
    case TAC_AND: fprintf(stderr, "TAC_AND");
    break;
    case TAC_OR: fprintf(stderr, "TAC_OR");
    break;
    case TAC_EQZ: fprintf(stderr, "TAC_EQZ");
    break;
    case TAC_PUSH: fprintf(stderr, "TAC_PUSH");
    break;
    case TAC_CLNSTACK: fprintf(stderr, "TAC_CLNSTACK");
    break;
    default: fprintf(stderr, "TAC_DEFAULT");
  }
  fprintf(stderr, ",%s", tac->res ? tac->res->text : "_");
  fprintf(stderr, ",%s", tac->op1 ? tac->op1->text : "_");
  fprintf(stderr, ",%s)\n", tac->op2 ? tac->op2->text : "_");
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

TAC* tacJoin(TAC* l1, TAC* l2)
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

TAC* tacJoin3(TAC* l1, TAC* l2, TAC* l3)
{
  return tacJoin(tacJoin(l1, l2), l3);
}

TAC* tacJoin4(TAC* l1, TAC* l2, TAC* l3, TAC* l4)
{
  return tacJoin(tacJoin(tacJoin(l1, l2), l3), l4);
}
