/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 4
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#include "semantics.h"
#include <stdlib.h>
#include <stdio.h>
int semanticFailure = 0;

void semanticsCheckDeclaration(TREE* node)
{
	int i, nature;
	if(node != NULL)
	{
		/*Anota o tipo do indentificador na tabela hash e avisa em caso de redeclaração.*/
		if( (node->type == TREE_DECL_SINGLE) ||
			(node->type == TREE_DECL_VECT)   ||
			(node->type == TREE_DECL_FUNC)    )
		{
			if(node->children[0]->type == TREE_TYPE_INT)
			{
				if(! hash_update_type( node->children[1]->symbol->text, VAL_TYPE_INT, node->type))
				{
					printf("%s already declared!\n", node->children[1]->symbol->text);
					semanticFailure = 1;
				}
			}
			if(node->children[0]->type == TREE_TYPE_BOOL)
			{
				if(! hash_update_type( node->children[1]->symbol->text, VAL_TYPE_BOOL, node->type))
				{
					printf("%s already declared!\n", node->children[1]->symbol->text);
					semanticFailure = 1;
				}
			}
			if(node->children[0]->type == TREE_TYPE_CHAR)
			{
				if(! hash_update_type( node->children[1]->symbol->text, VAL_TYPE_CHAR, node->type))
				{
					printf("%s already declared!\n", node->children[1]->symbol->text);
					semanticFailure = 1;
				}
			}
			if(node->children[0]->type == TREE_TYPE_REAL)
			{
				if(! hash_update_type( node->children[1]->symbol->text, VAL_TYPE_REAL, node->type))
				{
					printf("%s already declared!\n", node->children[1]->symbol->text);
					semanticFailure = 1;
				}
			}
		}
		for(i=0; i<MAX_CHILDREN; i++)
		{
			semanticsCheckDeclaration(node->children[i]);
		}
	}
}

void semanticsCheckUndeclared(TREE * node)
{

}

void semanticsCheckUsage(TREE* node)
{


}

int semanticsIsCompatible(VAL_TYPE valueType1, VAL_TYPE valueType2)
{
	return 1;
}

int semanticsMatchParameters(PARAM_LIST *paramsDecl, TREE *paramsCall)
{
	for (; paramsDecl && paramsCall; paramsDecl=paramsDecl->next, paramsCall=paramsCall->children[1]) {
		if (! semanticsIsCompatible(paramsDecl->valueType,
															semanticsCheckType(paramsCall->children[0])) ) {
			return 0;
		}
	}
	// If stopped the loop, then at least one of the list has come to the end (== NULL)
	// If both have, then they are equivalent, otherwise they're not
	return (void*)paramsDecl == (void*)paramsCall;
}

int semanticsGreaterNumericType(VAL_TYPE type1, VAL_TYPE type2)
{
	return 1;
}

VAL_TYPE semanticsCheckType(TREE* node)
{
	DATA_TYPE symbolDataType;
	VAL_TYPE rightValueType;
	VAL_TYPE conditionValueType;
	VAL_TYPE indexValueType;
	VAL_TYPE leftExprType;
	VAL_TYPE rightExprType;

	if (!node) {
		return VAL_TYPE_UNIT;
	}

	switch (node->type) {
		case TREE_SYMBOL:
			switch (node->symbol->type) {
				case SYMBOL_LITERAL_INT:
					return VAL_TYPE_INT;
				case SYMBOL_LITERAL_REAL:
					return VAL_TYPE_REAL;
				case SYMBOL_LITERAL_CHAR:
					return VAL_TYPE_CHAR;
				case SYMBOL_LITERAL_STRING:
					return VAL_TYPE_STRING;
				case SYMBOL_IDENTIFIER:
					// Identifier alone in an expression can only appear if it's a scalar
					if (node->symbol->dataType.identifierType == ID_TYPE_SCALAR)
						return node->symbol->dataType.valueType;
					else {
						semanticFailure = 1;
						return -1;
					}
				default:
					// This case should not happen
					semanticFailure = 1;
					return -1;
			}
		case TREE_TYPE_INT:
		case TREE_TYPE_REAL:
		case TREE_TYPE_BOOL:
		case TREE_TYPE_CHAR:
		case TREE_TYPE_STRING:
			// This case should not happen
			return;
		case TREE_VAL_TRUE:
			return VAL_TYPE_BOOL;
		case TREE_VAL_FALSE:
			return VAL_TYPE_BOOL;
		case TREE_DECL_FUNC:
			// Check the type of the function body, the function returns the type of
			// the "return" commands in the body, now we must check it
			symbolDataType = node->children[1]->symbol->dataType;
			VAL_TYPE returnType = semanticsCheckType(node->children[3]);
			if (returnType == symbolDataType.valueType)
				return VAL_TYPE_UNIT;
			else {
				semanticFailure = 1;
				return -1;
			}
		case TREE_DECL_SINGLE:
		case TREE_DECL_VECT:
		case TREE_LIST_SYM:
		case TREE_LIST_ARG:
			// This case should not happen
			return;
		case TREE_LIST_COMM:
			// Check the type of the command (first), note: single command doesn't have a type
			if (semanticsCheckType(node->children[0]) != -1)
				// Then call recursively for the next command (rest)
				return semanticsCheckType(node->children[1]);
			else
				return -1;
		case TREE_LIST_EXPR:
			// Check the type of the expression (first), note: the type of an expression in a
			// list is irrelevant, it should just be well typed
			if (semanticsCheckType(node->children[0]) != -1)
				// Then call recursively for the next expression (rest)
				return semanticsCheckType(node->children[1]);
			else
				return -1;
		case TREE_LIST_OUT:
			// Check the type of the element (first)
			if (semanticsCheckType(node->children[0]) != -1)
				// Then call recursively for the next element (rest)
				return semanticsCheckType(node->children[1]);
			else
				return -1;
		case TREE_COMM_NOP:
			return VAL_TYPE_UNIT;
		case TREE_COMM_IN:
			// Check the type of the list of input
			if (semanticsCheckType(node->children[0]) != -1)
				return VAL_TYPE_UNIT;
			else
				return -1;
		case TREE_COMM_OUT:
			// Check the type of the list of output
			if (semanticsCheckType(node->children[0]) != -1)
				return VAL_TYPE_UNIT;
			else
				return -1;
		case TREE_COMM_ASSIG:
			symbolDataType = node->children[0]->symbol->dataType;
			rightValueType = semanticsCheckType(node->children[1]);

			// Left side must be scalar and of a type compatible with the right side
			if (rightValueType != -1
			&& symbolDataType.identifierType == ID_TYPE_SCALAR
			&& semanticsIsCompatible(symbolDataType.valueType, rightValueType)) {
				return VAL_TYPE_UNIT;
			} else {
				semanticFailure = 1;
				return -1;
			}
		case TREE_COMM_ASSIG_VEC:
			symbolDataType = node->children[0]->symbol->dataType;
			indexValueType = semanticsCheckType(node->children[1]);
			rightValueType = semanticsCheckType(node->children[2]);

			// Left side must be a vector, the index expression an integer, and the vector
			// type must be compatible with the right side
			if (rightValueType != -1
			&& symbolDataType.identifierType == ID_TYPE_VECTOR
			&& indexValueType == VAL_TYPE_INT
			&& semanticsIsCompatible(symbolDataType.valueType, rightValueType)) {
				return VAL_TYPE_UNIT;
			} else {
				semanticFailure = 1;
				return -1;
			}
		case TREE_COMM_IF_ELSE:
			conditionValueType = semanticsCheckType(node->children[0]);

			// The condition expression should be compatible with int, because it'll be tested for zero
			if (semanticsIsCompatible(VAL_TYPE_INT, conditionValueType)) {

				// Check the type of the Then-Command and the Else-Command
				VAL_TYPE thenCommandType = semanticsCheckType(node->children[1]);
				VAL_TYPE elseCommandType = semanticsCheckType(node->children[2]);
				if (thenCommandType != -1 && elseCommandType != -1) {
					// If the Then-Command has no type (no "return" command), then the type
					// of the If-Command will be the type of the Else-command, and vice-versa
					if (thenCommandType == VAL_TYPE_UNIT) {
						return elseCommandType;
					} else if (elseCommandType == VAL_TYPE_UNIT) {
						return thenCommandType;
					} else if (thenCommandType == elseCommandType) {
					// If both command have any type (they have "return" commands), then
					// both types must be equal and this will be the type of the If-Command
							return thenCommandType;
					} else {
						semanticFailure = 1;
						return -1;
					}
				} else
					return -1;
			} else {
				semanticFailure = -1;
				return -1;
			}
		case TREE_COMM_WHILE:
			conditionValueType = semanticsCheckType(node->children[0]);

			// The condition expression should be compatible with int, because it'll be tested for zero
			if (semanticsIsCompatible(VAL_TYPE_INT, conditionValueType)) {

				// Check the type of the loop body
				return semanticsCheckType(node->children[1]);
			} else {
				semanticFailure = -1;
				return -1;
			}
		case TREE_COMM_RETURN:
			return semanticsCheckType(node->children[0]);
		case TREE_EXPR_ARIT_FUNCALL:
			symbolDataType = node->children[0]->symbol->dataType;

			// Identifier must be function and the call must match the declaration
			if (symbolDataType.identifierType == ID_TYPE_FUNCTION
			&& semanticsMatchParameters(symbolDataType.params, node->children[1])) {
				return symbolDataType.valueType;
			} else {
				semanticFailure = -1;
				return -1;
			}
		case TREE_EXPR_ARIT_VEC_READ:
			symbolDataType = node->children[0]->symbol->dataType;
			indexValueType = semanticsCheckType(node->children[1]);

			// Left side must be a vector, the index expression an integer, and the vector
			// type must be compatible with the right side
			if (symbolDataType.identifierType == ID_TYPE_VECTOR
			&& indexValueType == VAL_TYPE_INT) {
				return symbolDataType.valueType;
			} else {
				semanticFailure = 1;
				return -1;
			}
		case TREE_EXPR_ARIT_ADD:
		case TREE_EXPR_ARIT_SUB:
		case TREE_EXPR_ARIT_MUL:
		case TREE_EXPR_ARIT_DIV:
			leftExprType = semanticsCheckType(node->children[0]);
			rightExprType = semanticsCheckType(node->children[1]);

			// Only numeric type can be operands
			if ((leftExprType == VAL_TYPE_INT || leftExprType == VAL_TYPE_CHAR || leftExprType == VAL_TYPE_REAL)
			&&  (rightExprType == VAL_TYPE_INT || rightExprType == VAL_TYPE_CHAR || rightExprType == VAL_TYPE_REAL)) {
				// Division returns always a real type
				if (node->type == TREE_EXPR_ARIT_DIV) {
					return VAL_TYPE_REAL;
				} else {
				// Other operations return the greater type of both operands
					return semanticsGreaterNumericType(leftExprType, rightExprType);
				}
			} else {
				semanticFailure = 1;
				return -1;
			}
		case TREE_EXPR_BOOL_LT:
		case TREE_EXPR_BOOL_GT:
		case TREE_EXPR_BOOL_LE:
		case TREE_EXPR_BOOL_GE:
		case TREE_EXPR_BOOL_EQ:
		case TREE_EXPR_BOOL_NE:
			leftExprType = semanticsCheckType(node->children[0]);
			rightExprType = semanticsCheckType(node->children[1]);

			// Only numeric type can be operands
			if ((leftExprType == VAL_TYPE_INT || leftExprType == VAL_TYPE_CHAR || leftExprType == VAL_TYPE_REAL)
			&&  (rightExprType == VAL_TYPE_INT || rightExprType == VAL_TYPE_CHAR || rightExprType == VAL_TYPE_REAL)) {
				return VAL_TYPE_BOOL;
			} else {
				semanticFailure = 1;
				return -1;
			}
		case TREE_EXPR_BOOL_AND:
		case TREE_EXPR_BOOL_OR:
			leftExprType = semanticsCheckType(node->children[0]);
			rightExprType = semanticsCheckType(node->children[1]);

			// Both expressions should be compatible with int, because they'll be tested for zero
			if (semanticsIsCompatible(VAL_TYPE_INT, leftExprType)
			&& semanticsIsCompatible(VAL_TYPE_INT, rightExprType)) {
				return VAL_TYPE_BOOL;
			} else {
				semanticFailure = 1;
				return -1;
			}
		case TREE_PROGRAM:
			// Check this declaration node (first), then check the rest of the program
			if (semanticsCheckType(node->children[0]) != -1)
				return semanticsCheckType(node->children[1]);
			else
				return -1;
		default:
			// This node should not exist
			semanticFailure = 1;
			return -1;
	}
}
