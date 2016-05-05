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

VAL_TYPE semanticsCheckType(TREE* node)
{
	DATA_TYPE result;
	if (!node) {
		return VAL_TYPE_UNIT;
	}

	//TODO
}
