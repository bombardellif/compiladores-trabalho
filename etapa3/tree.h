/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 3
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */
 
#include "hash.h"
#define MAX_CHILDREN 4

#define TREE_ADD 43
#define TREE_MUL 42
#define TREE_SUB 45
#define TREE_DIV 47
#define TREE_SYMBOL 0

typedef struct tree_node
{
	int type;
	HASH*  symbol;
	struct tree_node* children[MAX_CHILDREN];
} TREE;

void print_tree(TREE* root);
TREE* create_tree(int type, TREE* child0, TREE* child1, TREE* child2, TREE* child3);
