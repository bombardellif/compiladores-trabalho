/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 5
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#ifndef __TAC_H__
#define __TAC_H__

#include "hash.h"

#define TAC_SYMBOL 1
#define TAC_ADD 2

typedef struct tac_node {
  int type;
  HASH *res;
  HASH *op1;
  HASH *op2;
  struct tac_node *prev;
  struct tac_node *next;
} TAC;

TAC* tacCreate(int type, HASH *res, HASH *op1, HASH *op2);
void tacPrintSingle(TAC* tac);
void tacPrintListPrev(TAC* tac);
TAC* tacJoin(TAC *l1, TAC *l2);

#endif
