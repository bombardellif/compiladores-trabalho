#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include <string.h>

void print_tree(TREE* root, int spaces)
{
	int i;
	if(root != NULL)
	{
		if(! spaces)
			ast_root = root;
		for(i=0; i < spaces; i++)
			fprintf(stderr, "  ");
		fprintf(stderr, "Tree %d: ", root->type);

		switch (root->type)
		{
			case TREE_SYMBOL : 							fprintf(stderr,"SYMBOL ");
							   											break;
			case TREE_EXPR_ARIT_ADD : 			fprintf(stderr,"TREE_EXPR_ARIT_ADD\n");
							   											break;
			case TREE_EXPR_ARIT_SUB : 			fprintf(stderr,"TREE_EXPR_ARIT_SUB\n");
							   											break;
			case TREE_EXPR_ARIT_MUL : 			fprintf(stderr,"TREE_EXPR_ARIT_MUL\n");
							   											break;
			case TREE_EXPR_ARIT_DIV : 			fprintf(stderr,"TREE_EXPR_ARIT_DIV\n");
							   											break;
			case TREE_EXPR_ARIT_VEC_READ:		fprintf(stderr, "TREE_EXPR_ARIT_VEC_READ\n");
																			break;
			case TREE_EXPR_ARIT_FUNCALL:		fprintf(stderr, "TREE_EXPR_ARIT_FUNCALL\n");
																			break;
			case TREE_TYPE_INT:							fprintf(stderr, "TREE_TYPE_INT\n");
																			break;
			case TREE_TYPE_REAL:						fprintf(stderr, "TREE_TYPE_REAL\n");
																			break;
			case TREE_TYPE_BOOL:						fprintf(stderr, "TREE_TYPE_BOOL\n");
																			break;
			case TREE_TYPE_CHAR:						fprintf(stderr, "TREE_TYPE_CHAR\n");
																			break;
			case TREE_VAL_TRUE:							fprintf(stderr, "TREE_VAL_TRUE\n");
																			break;
			case TREE_VAL_FALSE :						fprintf(stderr, "TREE_VAL_FALSE\n");
																			break;
			case TREE_DECL_SINGLE: 					fprintf(stderr, "TREE_DECL_SINGLE\n");
																			break;
			case TREE_DECL_VECT :						fprintf(stderr, "TREE_DECL_VECT\n");
																			break;
			case TREE_DECL_FUNC :						fprintf(stderr, "TREE_DECL_FUNC\n");
																			break;
			case TREE_LIST_SYM :						fprintf(stderr, "TREE_LIST_SYM\n");
																			break;
			case TREE_LIST_ARG :						fprintf(stderr, "TREE_LIST_ARG\n");
																			break;
			case TREE_LIST_COMM :						fprintf(stderr, "TREE_LIST_COMM\n");
																			break;
			case TREE_LIST_EXPR :						fprintf(stderr, "TREE_LIST_EXPR\n");
																			break;
			case TREE_LIST_OUT :						fprintf(stderr, "TREE_LIST_OUT\n");
																			break;
			case TREE_COMM_NOP:							fprintf(stderr, "TREE_COMM_NOP\n");
																			break;
			case TREE_COMM_IN:							fprintf(stderr, "TREE_COMM_IN\n");
																			break;
			case TREE_COMM_OUT :						fprintf(stderr, "TREE_COMM_OUT\n");
																			break;
			case TREE_COMM_RETURN :					fprintf(stderr, "TREE_COMM_RETURN\n");
																			break;
		  case TREE_COMM_ASSIG :					fprintf(stderr, "TREE_COMM_ASSIG\n");
																			break;
			case TREE_COMM_ASSIG_VEC :			fprintf(stderr, "TREE_COMM_ASSIG_VEC\n");
																			break;
			case TREE_COMM_IF_ELSE :				fprintf(stderr, "TREE_COMM_IF_ELSE\n");
																			break;
			case TREE_COMM_WHILE :					fprintf(stderr, "TREE_COMM_WHILE\n");
																			break;
			case TREE_EXPR_BOOL_LT :				fprintf(stderr, "TREE_EXPR_BOOL_LT\n");
																			break;
		  case TREE_EXPR_BOOL_GT :				fprintf(stderr, "TREE_EXPR_BOOL_GT\n");
																			break;
			case TREE_EXPR_BOOL_LE :				fprintf(stderr, "TREE_EXPR_BOOL_LE\n");
																			break;
			case TREE_EXPR_BOOL_GE :				fprintf(stderr, "TREE_EXPR_BOOL_GE\n");
																			break;
			case TREE_EXPR_BOOL_EQ :				fprintf(stderr, "TREE_EXPR_BOOL_EQ\n");
																			break;
			case TREE_EXPR_BOOL_NE :				fprintf(stderr, "TREE_EXPR_BOOL_NE\n");
																			break;
			case TREE_EXPR_BOOL_AND :				fprintf(stderr, "TREE_EXPR_BOOL_AND\n");
																			break;
			case TREE_EXPR_BOOL_OR :				fprintf(stderr, "TREE_EXPR_BOOL_OR\n");
																			break;
			case TREE_PROGRAM : 						fprintf(stderr, "TREE_PROGRAM\n");
																			break;
			default : 											fprintf(stderr,"UNDEFINED\n");
							  											break;
		}
		if(root->symbol)
			fprintf(stderr, "%s\n", root->symbol->text);
		for(i=0;i<MAX_CHILDREN; i++)
			print_tree(root->children[i], spaces + 1);
	}
}

char* get_value(TREE* root, char* varname)
{	
	int i, arrayLength, symbolLength=0;
	char* buffer = NULL, *temp = NULL;
	if(root != NULL)
	{
		switch (root->type)
		{
			case TREE_DECL_SINGLE:
				if(!strcmp(varname, root->children[1]->symbol->text))
					return root->children[2]->symbol->text;
			break;
			case TREE_DECL_VECT:
				if(!strcmp(varname, root->children[1]->symbol->text))
				{
					arrayLength = atoi(root->children[2]->symbol->text);
					root = root->children[3];
					for(i = 0; i < arrayLength; i++)
					{
						symbolLength += 1+strlen(root->children[0]->symbol->text);
						temp = realloc(buffer, (symbolLength) * sizeof *temp);
						buffer = temp;
						strcat(buffer, root->children[0]->symbol->text);
						if( i != arrayLength -1) strcat(buffer, ",");
						root = root->children[1];
					}
					return buffer;
				}
			break;
		}
		for(i=0;i<MAX_CHILDREN; i++)
			if(buffer = get_value(root->children[i], varname))
				return buffer;
    }
	return NULL;
    
}

char* find_declaration_value(char* varname)
{
	return get_value(ast_root,varname);
}


TREE* create_tree(TREE_TYPE type, HASH* hash_symbol, TREE* child0, TREE* child1, TREE* child2, TREE* child3)
{
	TREE* tree;
	tree = (TREE*) calloc(8,sizeof(TREE*)); // Valgrind acusava 'Invalid write of size 8' na função create_tree (estava 1 no calloc antes)
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

void print_commands(TREE *node, FILE* outfile) {
	// Se for bloco (look forward)
	if (node->children[1]) {
		fprintf(outfile, "{\n");
		decompile(node, outfile);
		fprintf(outfile, "\n}");
	} else {
		decompile(node, outfile);
	}
}

void decompile(TREE *node, FILE* outfile)
{
	if (node) {
		switch (node->type) {
			case TREE_SYMBOL:
				if (node->symbol) {
					switch (node->symbol->type) {
						case SYMBOL_LITERAL_STRING:
							fprintf(outfile, "\"%s\"", node->symbol->text);
						break;
						case SYMBOL_LITERAL_CHAR:
							fprintf(outfile, "'%s'", node->symbol->text);
						break;
						default:
							fprintf(outfile, "%s", node->symbol->text);
					}
				}
				else
					fprintf(outfile, TREE_TOKEN_ERROR);
			break;
			case TREE_TYPE_INT:
				fprintf(outfile, "int");
			break;
			case TREE_TYPE_REAL:
				fprintf(outfile, "real");
			break;
			case TREE_TYPE_BOOL:
				fprintf(outfile, "bool");
			break;
			case TREE_TYPE_CHAR:
				fprintf(outfile, "char");
			break;
			case TREE_VAL_TRUE:
				fprintf(outfile, "TRUE");
			break;
			case TREE_VAL_FALSE:
				fprintf(outfile, "FALSE");
			break;
			case TREE_DECL_SINGLE:
				decompile(node->children[0], outfile);
				fprintf(outfile, " ");
				decompile(node->children[1], outfile);
				// Se tem inicialização de valores
				if (node->children[2]) {
					fprintf(outfile, ": ");
					decompile(node->children[2], outfile);
				}
				fprintf(outfile, ";");
			break;
			case TREE_DECL_VECT:
				decompile(node->children[0], outfile);
				fprintf(outfile, " ");
				decompile(node->children[1], outfile);
				fprintf(outfile, "[");
				decompile(node->children[2], outfile);
				fprintf(outfile, "]");
				// Se tem inicialização de valores
				if (node->children[3]) {
					fprintf(outfile, ": ");
					decompile(node->children[3], outfile);
				}
				fprintf(outfile, ";");
			break;
			case TREE_DECL_FUNC:
				decompile(node->children[0], outfile);
				fprintf(outfile, " ");
				decompile(node->children[1], outfile);
				fprintf(outfile, "(");
				decompile(node->children[2], outfile);
				fprintf(outfile, ") ");

				print_commands(node->children[3], outfile);
				fprintf(outfile, ";");
			break;
			case TREE_LIST_SYM:
				decompile(node->children[0], outfile);
				if (node->children[1]) {
					fprintf(outfile, " ");
					decompile(node->children[1], outfile);
				}
			break;
			case TREE_LIST_EXPR:case TREE_LIST_OUT:
				decompile(node->children[0], outfile);
				if (node->children[1]) {
					fprintf(outfile, ", ");
					decompile(node->children[1], outfile);
				}
			break;
			case TREE_LIST_ARG:
				decompile(node->children[0], outfile);
				fprintf(outfile, " ");
				decompile(node->children[1], outfile);
				if (node->children[2]) {
					fprintf(outfile, ", ");
					decompile(node->children[2], outfile);
				}
			break;
			case TREE_PROGRAM: case TREE_LIST_COMM:
				decompile(node->children[0], outfile);
				if (node->children[1]) {
					fprintf(outfile, "\n");
					decompile(node->children[1], outfile);
				}
			break;
			case TREE_COMM_NOP:
				fprintf(outfile, ";");
			break;
			case TREE_COMM_IN:
				fprintf(outfile, "input ");
				decompile(node->children[0], outfile);
			break;
			case TREE_COMM_OUT:
				fprintf(outfile, "output ");
				decompile(node->children[0], outfile);
			break;
			case TREE_COMM_RETURN:
				fprintf(outfile, "return ");
				decompile(node->children[0], outfile);
			break;
			case TREE_COMM_ASSIG:
				decompile(node->children[0], outfile);
				fprintf(outfile, " = ");
				decompile(node->children[1], outfile);
			break;
			case TREE_COMM_ASSIG_VEC:
				decompile(node->children[0], outfile);
				fprintf(outfile, "[");
				decompile(node->children[1], outfile);
				fprintf(outfile, "] = ");
				decompile(node->children[2], outfile);
			break;
			case TREE_COMM_IF_ELSE:
				fprintf(outfile, "if (");
				decompile(node->children[0], outfile);
				fprintf(outfile, ") ");

				print_commands(node->children[1], outfile);

				// Se tem ELSE
				if (node->children[2]) {
					fprintf(outfile, " else ");
					print_commands(node->children[2], outfile);
				}
			break;
			case TREE_COMM_WHILE:
				fprintf(outfile, "while (");
				decompile(node->children[0], outfile);
				fprintf(outfile, ") ");

				print_commands(node->children[1], outfile);
			break;
			case TREE_EXPR_ARIT_FUNCALL:
				decompile(node->children[0], outfile);
				fprintf(outfile, "(");
				decompile(node->children[1], outfile);
				fprintf(outfile, ")");
			break;
			case TREE_EXPR_ARIT_VEC_READ:
				decompile(node->children[0], outfile);
				fprintf(outfile, "[");
				decompile(node->children[1], outfile);
				fprintf(outfile, "]");
			break;
			case TREE_EXPR_ARIT_ADD:
				fprintf(outfile, "(");
				decompile(node->children[0], outfile);
				fprintf(outfile, " + ");
				decompile(node->children[1], outfile);
				fprintf(outfile, ")");
			break;
			case TREE_EXPR_ARIT_SUB:
				fprintf(outfile, "(");
				decompile(node->children[0], outfile);
				fprintf(outfile, " - ");
				decompile(node->children[1], outfile);
				fprintf(outfile, ")");
			break;
			case TREE_EXPR_ARIT_MUL:
				fprintf(outfile, "(");
				decompile(node->children[0], outfile);
				fprintf(outfile, " * ");
				decompile(node->children[1], outfile);
				fprintf(outfile, ")");
			break;
			case TREE_EXPR_ARIT_DIV:
				fprintf(outfile, "(");
				decompile(node->children[0], outfile);
				fprintf(outfile, " / ");
				decompile(node->children[1], outfile);
				fprintf(outfile, ")");
			break;
			case TREE_EXPR_BOOL_LT:
				decompile(node->children[0], outfile);
				fprintf(outfile, " < ");
				decompile(node->children[1], outfile);
			break;
			case TREE_EXPR_BOOL_GT:
				decompile(node->children[0], outfile);
				fprintf(outfile, " > ");
				decompile(node->children[1], outfile);
			break;
			case TREE_EXPR_BOOL_LE:
				decompile(node->children[0], outfile);
				fprintf(outfile, " <= ");
				decompile(node->children[1], outfile);
			break;
			case TREE_EXPR_BOOL_GE:
				decompile(node->children[0], outfile);
				fprintf(outfile, " >= ");
				decompile(node->children[1], outfile);
			break;
			case TREE_EXPR_BOOL_EQ:
				decompile(node->children[0], outfile);
				fprintf(outfile, " == ");
				decompile(node->children[1], outfile);
			break;
			case TREE_EXPR_BOOL_NE:
				decompile(node->children[0], outfile);
				fprintf(outfile, " != ");
				decompile(node->children[1], outfile);
			break;
			case TREE_EXPR_BOOL_AND:
				decompile(node->children[0], outfile);
				fprintf(outfile, " && ");
				decompile(node->children[1], outfile);
			break;
			case TREE_EXPR_BOOL_OR:
				decompile(node->children[0], outfile);
				fprintf(outfile, " || ");
				decompile(node->children[1], outfile);
			break;
			default:
				fprintf(outfile, TREE_TOKEN_ERROR);
		}
	}
}
