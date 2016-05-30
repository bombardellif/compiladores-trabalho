/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 5
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#ifndef __TAC_H__
#define __TAC_H__

#include "hash.h"
                            // $res       $op1        $op2
#define TAC_SYMBOL 1        // symbol
#define TAC_MOVE 2          // to         from
#define TAC_STRIDX 25       // to         index       from
#define TAC_LOADIDX 26      // temp_symbol from       index
#define TAC_ADD 3           // result     left_op     right_op
#define TAC_SUB 4           // result     left_op     right_op
#define TAC_MUL 5           // result     left_op     right_op
#define TAC_DIV 6           // result     left_op     right_op
#define TAC_LABEL 7         // new_label_symbol
#define TAC_BEGINFUN 8      // symbol ??
#define TAC_ENDFUN 9        // symbol ??
#define TAC_IFZ 10          // label_symbol test_symbol
#define TAC_JUMP 11         // label_symbol
#define TAC_CALL 12         // symbol
#define TAC_ARG 13          // to         from
#define TAC_RET 14          // temp_symbol symbol
#define TAC_PRINT 15
#define TAC_READ 16
#define TAC_ANEG 17         // temp_symbol  test_symbol
#define TAC_LTZ 18          // temp_symbol  test_symbol
#define TAC_GTZ 19          // temp_symbol  test_symbol
#define TAC_LEZ 20          // temp_symbol  test_symbol
#define TAC_GEZ 21          // temp_symbol  test_symbol
#define TAC_AND 22          // temp_symbol  left_op   right_op
#define TAC_OR 23           // temp_symbol  left_op   right_op
#define TAC_NOP 24
#define TAC_EQZ 27			// temp_symbol  test_symbol

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
void tacPrintListNext(TAC* tac);
TAC* tacReverse(TAC* tac);
TAC* tacJoin(TAC* l1, TAC* l2);
TAC* tacJoin3(TAC* l1, TAC* l2, TAC* l3);
TAC* tacJoin4(TAC* l1, TAC* l2, TAC* l3, TAC* l4);

#endif
