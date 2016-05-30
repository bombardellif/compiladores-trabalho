/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 5
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#include "code-gen.h"

#include <stdlib.h>

TAC* makeBinOp(int type, TAC* code0, TAC* code1)
{

	
  		return tacJoin(tacJoin(code0, code1),
            			tacCreate(type, hash_make_temp(), code0 ? code0->res : 0, code1 ? code1->res : 0));
}

TAC* makeIfThenElse(TAC* codeTest, TAC* codeThen, TAC* codeElse)
{
  TAC *newIf, *targetElse, *targetEndIf;
  HASH *labelElse, *labelEndIf;

  // Create code and label fot the test (IFZ)
  labelElse = hash_make_label();
  newIf = tacCreate(TAC_IFZ, labelElse, codeTest?codeTest->res:0, 0);
  newIf->prev = codeTest;

  // If there's an else, then add the jump at the end of the "then" block
  if (codeElse) {
    labelEndIf = hash_make_label();
    codeThen = tacJoin3(newIf,
      codeThen,
      tacCreate(TAC_JUMP, labelEndIf, 0, 0) );
  } else {
    codeThen = tacJoin(newIf, codeThen);
  }

  // Add the label to jump from the conditional test IFZ
  targetElse = tacCreate(TAC_LABEL, labelElse, 0, 0);
  targetElse->prev = codeThen;

  // If there's "else", append its code after the "then" block and create the label end-if
  if (codeElse) {
    codeElse = tacJoin(targetElse, codeElse);
    targetEndIf = tacCreate(TAC_LABEL, labelEndIf, 0, 0);
    targetEndIf->prev = codeElse;
  } else {
    targetEndIf = targetElse;
  }

  return targetEndIf;
}

TAC* makeWhile(TAC* codeTest, TAC* codeThen)
{
    TAC *newWhile, *targetEndWhile, *targetBeginWhile;
    HASH *labelBeginWhile, *labelEndWhile;

    // Create code and label fot the test (WHILE)
    labelBeginWhile = hash_make_label();
    labelEndWhile = hash_make_label();
    targetBeginWhile = tacCreate(TAC_LABEL, labelBeginWhile, 0, 0);

    //                                                  temp (bool)
    newWhile = tacCreate(TAC_IFZ, labelEndWhile, codeTest?codeTest->res:0, 0);
    newWhile->prev = codeTest;
    //printf("AAAAAAAAAAAAAAAAAAAAAAAAAAA %d\n", codeTest->type); // type: LTZ, GEZ... op1 e op2 are the operands

    // Add the jump at the end of the block back to the test
    codeThen = tacJoin4(targetBeginWhile,
                        newWhile,
                        codeThen,
                        tacCreate(TAC_JUMP, labelBeginWhile, 0, 0) );

    // Add the label to jump from the conditional test WHILE
    targetEndWhile = tacCreate(TAC_LABEL, labelEndWhile, 0, 0);
    targetEndWhile->prev = codeThen;

    return targetEndWhile;
}

TAC* generateCode(TREE* node)
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
    case TREE_VAL_TRUE:
      return tacCreate(TAC_SYMBOL, get_hash_node("_True"), 0, 0);
    case TREE_VAL_FALSE:
      return tacCreate(TAC_SYMBOL, get_hash_node("_False"), 0, 0);
    case TREE_COMM_NOP:
      return tacCreate(TAC_NOP, 0, 0, 0);
    case TREE_COMM_IN:
    case TREE_COMM_OUT:
      //TODO
      break;
    case TREE_COMM_ASSIG:
      return tacJoin(code[1],
            tacCreate(TAC_MOVE, code[0]?code[0]->res:0, code[1]?code[1]->res:0, 0)
      );
    case TREE_COMM_ASSIG_VEC:
      return tacJoin3(code[1],
            code[2],
            tacCreate(TAC_STRIDX, code[0]?code[0]->res:0, code[1]?code[1]->res:0, code[2]?code[2]->res:0)
      );
    case TREE_COMM_IF_ELSE:
      return makeIfThenElse(code[0], code[1], code[2]);
    case TREE_COMM_WHILE:
      return makeWhile(code[0], code[1]);
    case TREE_COMM_RETURN:
      return tacJoin(code[0],
            tacCreate(TAC_RET, get_hash_node("_Return"), code[0]?code[0]->res:0, 0));
    case TREE_EXPR_ARIT_FUNCALL:
    case TREE_EXPR_ARIT_VEC_READ:
      // TODO
      break;
    case TREE_EXPR_ARIT_ADD:
      return makeBinOp(TAC_ADD, code[0], code[1]);
    case TREE_EXPR_ARIT_SUB:
      return makeBinOp(TAC_SUB, code[0], code[1]);
    case TREE_EXPR_ARIT_MUL:
      return makeBinOp(TAC_MUL, code[0], code[1]);
    case TREE_EXPR_ARIT_DIV:
      return makeBinOp(TAC_DIV, code[0], code[1]);
    case TREE_EXPR_BOOL_LT:
    	return makeBinOp(TAC_LTZ, code[0], code[1]);
    case TREE_EXPR_BOOL_GT:
    	return makeBinOp(TAC_GTZ, code[0], code[1]);
    case TREE_EXPR_BOOL_LE:
    	return makeBinOp(TAC_LEZ, code[0], code[1]);
    case TREE_EXPR_BOOL_GE:
    	return makeBinOp(TAC_GEZ, code[0], code[1]);
    case TREE_EXPR_BOOL_EQ:
    	return makeBinOp(TAC_DIV, code[0], code[1]);
    case TREE_EXPR_BOOL_NE:
    	return makeBinOp(TAC_ANEG, code[0],code[1]);
    case TREE_EXPR_BOOL_AND:
    	return makeBinOp(TAC_AND, code[0], code[1]);
    case TREE_EXPR_BOOL_OR:
    	return makeBinOp(TAC_OR, code[0], code[1]);
    default:
    break;
  }

  return tacJoin4(code[0], code[1], code[2], code[3]);
}
