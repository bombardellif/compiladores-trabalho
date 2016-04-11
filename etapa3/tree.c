#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

void print_tree(TREE* root)
{
	int i = 0;
	if(root != NULL)
	{
		switch (root->type)
		{
			case TREE_SYMBOL : 		fprintf(stderr,"SYMBOL");
							   		break;
			case TREE_ADD : 		fprintf(stderr,"UNDEFINED");
							   		break;
			case TREE_MUL : 		fprintf(stderr,"UNDEFINED");
							   		break;
			case TREE_SUB : 		fprintf(stderr,"UNDEFINED");
							   		break;
			case TREE_DIV : 		fprintf(stderr,"UNDEFINED");
							   		break;
			default : 				fprintf(stderr,"UNDEFINED");
							  		break;		   
		}
		if(root->symbol)
			fprintf(stderr, "%s", root->symbol->text);
		for(;i<MAX_CHILDREN; i++)
			print_tree(root->children[i]);
	}
}

TREE* create_tree(int type, TREE* child0, TREE* child1, TREE* child2, TREE* child3)
{
	TREE* tree;
	tree = (TREE*) calloc(1,sizeof(TREE*));
	tree->type = type;
	tree->children[0] = child0;
	tree->children[1] = child1;
	tree->children[2] = child2;
	tree->children[3] = child3;
	return tree;
}
