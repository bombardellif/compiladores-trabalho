#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

void print_tree(TREE* root, int spaces)
{
	int i;
	if(root != NULL)
	{
		for(i=0; i < spaces; i++)
			fprintf(stderr, " ");
		fprintf(stderr, "Tree ");

		switch (root->type)
		{
			case TREE_SYMBOL : 							fprintf(stderr,"SYMBOL");
							   											break;
			case TREE_EXPR_ARIT_ADD : 			fprintf(stderr,"TREE_EXPR_ARIT_ADD");
							   											break;
			case TREE_EXPR_ARIT_SUB : 			fprintf(stderr,"TREE_EXPR_ARIT_SUB");
							   											break;
			case TREE_EXPR_ARIT_MUL : 			fprintf(stderr,"TREE_EXPR_ARIT_MUL");
							   											break;
			case TREE_EXPR_ARIT_DIV : 			fprintf(stderr,"TREE_EXPR_ARIT_DIV");
							   											break;
			case TREE_EXPR_ARIT_VEC_READ:		fprintf(stderr, "TREE_EXPR_ARIT_VEC_READ");
																			break;
			case TREE_EXPR_ARIT_FUNCALL:		fprintf(stderr, "TREE_EXPR_ARIT_FUNCALL");
																			break;
			case TREE_TYPE_INT:							fprintf(stderr, "TREE_TYPE_INT");
																			break;
			case TREE_TYPE_REAL:						fprintf(stderr, "TREE_TYPE_REAL");
																			break;
			case TREE_TYPE_BOOL:						fprintf(stderr, "TREE_TYPE_BOOL");
																			break;
			case TREE_TYPE_CHAR:						fprintf(stderr, "TREE_TYPE_CHAR");
																			break;
			case TREE_VAL_TRUE:							fprintf(stderr, "TREE_VAL_TRUE");
																			break;
			case TREE_VAL_FALSE :						fprintf(stderr, "TREE_VAL_FALSE");
																			break;
			case TREE_DECL_SINGLE: 					fprintf(stderr, "TREE_DECL_SINGLE");
																			break;
			case TREE_DECL_VECT :						fprintf(stderr, "TREE_DECL_VECT");
																			break;
			case TREE_DECL_FUNC :						fprintf(stderr, "TREE_DECL_FUNC");
																			break;
			case TREE_LIST_SYM :						fprintf(stderr, "TREE_LIST_SYM");
																			break;
			case TREE_LIST_ARG :						fprintf(stderr, "TREE_LIST_ARG");
																			break;
			case TREE_LIST_COMM :						fprintf(stderr, "TREE_LIST_COMM");
																			break;
			case TREE_LIST_EXPR :						fprintf(stderr, "TREE_LIST_EXPR");
																			break;
			case TREE_LIST_OUT :						fprintf(stderr, "TREE_LIST_OUT");
																			break;
			case TREE_COMM_NOP:							fprintf(stderr, "TREE_COMM_NOP");
																			break;
			case TREE_COMM_IN:							fprintf(stderr, "TREE_COMM_IN");
																			break;
			case TREE_COMM_OUT :						fprintf(stderr, "TREE_COMM_OUT");
																			break;
		  case TREE_COMM_ASSIG :					fprintf(stderr, "TREE_COMM_ASSIG");
																			break;
			case TREE_COMM_ASSIG_VEC :			fprintf(stderr, "TREE_COMM_ASSIG_VEC");
																			break;
			case TREE_COMM_IF_ELSE :				fprintf(stderr, "TREE_COMM_IF_ELSE");
																			break;
			case TREE_COMM_WHILE :					fprintf(stderr, "TREE_COMM_WHILE");
																			break;
			case TREE_EXPR_BOOL_LT :				fprintf(stderr, "TREE_EXPR_BOOL_LT");
																			break;
		  case TREE_EXPR_BOOL_GT :				fprintf(stderr, "TREE_EXPR_BOOL_GT");
																			break;
			case TREE_EXPR_BOOL_LE :				fprintf(stderr, "TREE_EXPR_BOOL_LE");
																			break;
			case TREE_EXPR_BOOL_GE :				fprintf(stderr, "TREE_EXPR_BOOL_GE");
																			break;
			case TREE_EXPR_BOOL_EQ :				fprintf(stderr, "TREE_EXPR_BOOL_EQ");
																			break;
			case TREE_EXPR_BOOL_NE :				fprintf(stderr, "TREE_EXPR_BOOL_NE");
																			break;
			case TREE_EXPR_BOOL_AND :				fprintf(stderr, "TREE_EXPR_BOOL_AND");
																			break;
			case TREE_EXPR_BOOL_OR :				fprintf(stderr, "TREE_EXPR_BOOL_OR");
																			break;
			case TREE_PROGRAM : 						fprintf(stderr, "TREE_PROGRAM");
																			break;
			default : 											fprintf(stderr,"UNDEFINED");
							  											break;
		}
		if(root->symbol)
			fprintf(stderr, "%s", root->symbol->text);
		for(i=0;i<MAX_CHILDREN; i++)
			print_tree(root->children[i], spaces + 1);
	}
	else printf("Null Tree!\n");
}

TREE* create_tree(TREE_TYPE type, HASH* hash_symbol, TREE* child0, TREE* child1, TREE* child2, TREE* child3)
{
	TREE* tree;
	tree = (TREE*) calloc(1,sizeof(TREE*));
	tree->type = type;
	tree->symbol = hash_symbol;
	tree->children[0] = child0;
	tree->children[1] = child1;
	tree->children[2] = child2;
	tree->children[3] = child3;
	return tree;
}

TREE* create_leaf(TREE_TYPE type)
{
	return create_tree(type, NULL, NULL, NULL, NULL, NULL);
}

TREE* create_leaf_symbol(HASH* hash_symbol)
{
	return create_tree(TREE_SYMBOL, hash_symbol, NULL, NULL, NULL, NULL);
}

void print_commands(TREE *node, int(*output)(const char*)) {
	// Se for bloco (look forward)
	if (node->children[1]) {
		printf("{\n");
		decompile(node, output);
		printf("\n}");
	} else {
		decompile(node, output);
	}
}

void decompile(TREE *node, int(*output)(const char*))
{
	if (node) {
		switch (node->type) {
			case TREE_SYMBOL:
				if (node->symbol)
					printf("%s", node->symbol->text);
				else
					printf(TREE_TOKEN_ERROR);
			break;
			case TREE_TYPE_INT:
				printf("int");
			break;
			case TREE_TYPE_REAL:
				printf("real");
			break;
			case TREE_TYPE_BOOL:
				printf("bool");
			break;
			case TREE_TYPE_CHAR:
				printf("char");
			break;
			case TREE_VAL_TRUE:
				printf("TRUE");
			break;
			case TREE_VAL_FALSE:
				printf("FALSE");
			break;
			case TREE_DECL_SINGLE:
				decompile(node->children[0], output);
				printf(" ");
				decompile(node->children[1], output);
				// Se tem inicialização de valores
				if (node->children[2]) {
					printf(": ");
					decompile(node->children[2], output);
					printf(";");
				}
			break;
			case TREE_DECL_VECT:
				decompile(node->children[0], output);
				printf(" ");
				decompile(node->children[1], output);
				printf("[");
				decompile(node->children[2], output);
				printf("]");
				// Se tem inicialização de valores
				if (node->children[3]) {
					printf(": ");
					decompile(node->children[3], output);
					printf(";");
				}
			break;
			case TREE_DECL_FUNC:
				decompile(node->children[0], output);
				printf(" ");
				decompile(node->children[1], output);
				printf("(");
				decompile(node->children[2], output);
				printf(") ");

				print_commands(node->children[3], output);
				printf(";");
			break;
			case TREE_LIST_SYM:case TREE_LIST_EXPR:case TREE_LIST_OUT:
				decompile(node->children[0], output);
				if (node->children[1]) {
					printf(", ");
					decompile(node->children[1], output);
				}
			break;
			case TREE_LIST_ARG:
				decompile(node->children[0], output);
				printf(" ");
				decompile(node->children[1], output);
				if (node->children[2]) {
					printf(", ");
					decompile(node->children[2], output);
				}
			break;
			case TREE_PROGRAM: case TREE_LIST_COMM:
				decompile(node->children[0], output);
				if (node->children[1]) {
					printf("\n");
					decompile(node->children[1], output);
				}
			break;
			case TREE_COMM_NOP:
				printf(";");
			break;
			case TREE_COMM_IN:
				printf("input ");
				decompile(node->children[0], output);
			break;
			case TREE_COMM_OUT:
				printf("output ");
				decompile(node->children[0], output);
			break;
			case TREE_COMM_ASSIG:
				decompile(node->children[0], output);
				printf(" = ");
				decompile(node->children[1], output);
			break;
			case TREE_COMM_ASSIG_VEC:
				decompile(node->children[0], output);
				printf("[");
				decompile(node->children[1], output);
				printf("] = ");
				decompile(node->children[2], output);
			break;
			case TREE_COMM_IF_ELSE:
				printf("if (");
				decompile(node->children[0], output);
				printf(") ");

				print_commands(node->children[1], output);

				// Se tem ELSE
				if (node->children[2]) {
					printf(" else ");
					print_commands(node->children[2], output);
				}
			break;
			case TREE_COMM_WHILE:
				printf("while (");
				decompile(node->children[0], output);
				printf(") ");

				print_commands(node->children[1], output);
			break;
			case TREE_EXPR_ARIT_FUNCALL:
				decompile(node->children[0], output);
				printf("(");
				decompile(node->children[1], output);
				printf(")");
			break;
			case TREE_EXPR_ARIT_VEC_READ:
				decompile(node->children[0], output);
				printf("[");
				decompile(node->children[1], output);
				printf("]");
			break;
			case TREE_EXPR_ARIT_ADD:
				printf("(");
				decompile(node->children[0], output);
				printf(" + ");
				decompile(node->children[1], output);
				printf(")");
			break;
			case TREE_EXPR_ARIT_SUB:
				printf("(");
				decompile(node->children[0], output);
				printf(" - ");
				decompile(node->children[1], output);
				printf(")");
			break;
			case TREE_EXPR_ARIT_MUL:
				printf("(");
				decompile(node->children[0], output);
				printf(" * ");
				decompile(node->children[1], output);
				printf(")");
			break;
			case TREE_EXPR_ARIT_DIV:
				printf("(");
				decompile(node->children[0], output);
				printf(" / ");
				decompile(node->children[1], output);
				printf(")");
			break;
			case TREE_EXPR_BOOL_LT:
				decompile(node->children[0], output);
				printf(" < ");
				decompile(node->children[1], output);
			break;
			case TREE_EXPR_BOOL_GT:
				decompile(node->children[0], output);
				printf(" > ");
				decompile(node->children[1], output);
			break;
			case TREE_EXPR_BOOL_LE:
				decompile(node->children[0], output);
				printf(" <= ");
				decompile(node->children[1], output);
			break;
			case TREE_EXPR_BOOL_GE:
				decompile(node->children[0], output);
				printf(" >= ");
				decompile(node->children[1], output);
			break;
			case TREE_EXPR_BOOL_EQ:
				decompile(node->children[0], output);
				printf(" == ");
				decompile(node->children[1], output);
			break;
			case TREE_EXPR_BOOL_NE:
				decompile(node->children[0], output);
				printf(" != ");
				decompile(node->children[1], output);
			break;
			case TREE_EXPR_BOOL_AND:
				decompile(node->children[0], output);
				printf(" && ");
				decompile(node->children[1], output);
			break;
			case TREE_EXPR_BOOL_OR:
				decompile(node->children[0], output);
				printf(" || ");
				decompile(node->children[1], output);
			break;
			default:
				printf(TREE_TOKEN_ERROR);
		}
	}
}
