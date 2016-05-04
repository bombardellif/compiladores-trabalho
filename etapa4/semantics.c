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
	int i;
	if(node != NULL)
	{	
		if( (node->type == TREE_DECL_SINGLE) || 
			(node->type == TREE_DECL_VECT)   ||
			(node->type == TREE_DECL_FUNC)    )
		{
			if(node->children[0]->type == TREE_TYPE_INT){
				node->symbol->dataType = TYPE_INT;}
			else if(node->children[0]->type == TREE_TYPE_BOOL)
				node->symbol->dataType = TYPE_BOOL;
			else if(node->children[0]->type == TREE_TYPE_REAL)
				node->symbol->dataType = TYPE_REAL;
			else if(node->children[0]->type == TREE_TYPE_CHAR)
				node->symbol->dataType = TYPE_CHAR;
		}

		for(i=0; i<MAX_CHILDREN; i++)
		{
			semanticsCheckDeclaration(node->children[i]);
		}
	}
}
 
void semanticsCheckUndeclared()
{

}

void semanticsCheckUsage(TREE* node)
{


}
