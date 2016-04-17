/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 3
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#ifndef __TREE__
#define __TREE__

#include "hash.h"
#define MAX_CHILDREN 4

#define TREE_TOKEN_ERROR "__"

typedef int TREE_TYPE;
// Leaf nodes (0-9)
#define TREE_SYMBOL 0               //Has the Pointer to Sym table
#define TREE_TYPE_INT 1
#define TREE_TYPE_REAL 2
#define TREE_TYPE_BOOL 3
#define TREE_TYPE_CHAR 4
#define TREE_VAL_TRUE 5
#define TREE_VAL_FALSE 6
#define TREE_TYPE_STRING 7

// Declarations (10-14)              #CHILD-1#    #CHILD-2#   #CHILD-3#       #CHILD-4#
#define TREE_DECL_SINGLE 10           //TYPE        SYMBOL      SYMBOL(ou NULL)
#define TREE_DECL_VECT 11             //TYPE        SYMBOL      SYMBOL        LIST_SYM(ou NULL)
#define TREE_DECL_FUNC 12             //TYPE        SYMBOL  LIST_ARG(ou NULL) LIST_COMM

// Lists (15-19)                     #CHILD-1#    #CHILD-2#           #CHILD-3#
#define TREE_LIST_SYM 15              //SYMBOL      LIST_SYM(ou NULL)
#define TREE_LIST_ARG 16              //TYPE        SYMBOL            LIST_ARG(ou NULL)
#define TREE_LIST_COMM 17             //COMMAND     LIST_COMM(ou NULL)
#define TREE_LIST_EXPR 18             //EXPR        LIST_EXPR(ou NULL)
#define TREE_LIST_OUT 19      		  //EXPR_ARIT(ou)SYMBOL LIST_OUT(ou NULL)

// Commands (20-29)                  #CHILD-1#    #CHILD-2#    #CHILD-3#
#define TREE_COMM_NOP 20
#define TREE_COMM_IN 21               //LIST_SYM
#define TREE_COMM_OUT 22              //LIST_OUT
#define TREE_COMM_ASSIG 23            //SYMBOL      EXPR
#define TREE_COMM_ASSIG_VEC 24        //SYMBOL      EXPR        EXPR
#define TREE_COMM_IF_ELSE 25          //EXPR        LIST_COMM   LIST_COMM(ou NULL)
#define TREE_COMM_WHILE 26            //EXPR        LIST_COMM
#define TREE_COMM_RETURN 27			  		//EXPR

// Aritmetics (30-39)                #CHILD-1#      #CHILD-2#
#define TREE_EXPR_ARIT_FUNCALL 30     //SYMBOL      LIST_EXPR
#define TREE_EXPR_ARIT_VEC_READ 31    //SYMBOL      EXPR_ARIT
#define TREE_EXPR_ARIT_ADD 32         //EXPR_ARIT   EXPR_ARIT
#define TREE_EXPR_ARIT_SUB 33         //EXPR_ARIT   EXPR_ARIT
#define TREE_EXPR_ARIT_MUL 34         //EXPR_ARIT   EXPR_ARIT
#define TREE_EXPR_ARIT_DIV 35         //EXPR_ARIT   EXPR_ARIT

// Boolean (40-49)                   #CHILD-1#      #CHILD-2#
#define TREE_EXPR_BOOL_LT 40          //EXPR_BOOL   EXPR_BOOL
#define TREE_EXPR_BOOL_GT 41          //EXPR_BOOL   EXPR_BOOL
#define TREE_EXPR_BOOL_LE 42          //EXPR_BOOL   EXPR_BOOL
#define TREE_EXPR_BOOL_GE 43          //EXPR_BOOL   EXPR_BOOL
#define TREE_EXPR_BOOL_EQ 44          //EXPR_BOOL   EXPR_BOOL
#define TREE_EXPR_BOOL_NE 45          //EXPR_BOOL   EXPR_BOOL
#define TREE_EXPR_BOOL_AND 46         //EXPR_BOOL   EXPR_BOOL
#define TREE_EXPR_BOOL_OR 47          //EXPR_BOOL   EXPR_BOOL

//The Program                        #CHILD-1#      #CHILD-2#
#define TREE_PROGRAM 50             //DECLARATION    PROGRAM(ou NULL)

typedef struct tree_node
{
	int type;
	HASH*  symbol;
	struct tree_node* children[MAX_CHILDREN];
} TREE;

void print_tree(TREE* root, int spaces);
TREE* create_tree(TREE_TYPE type, HASH* hash_symbol, TREE* child0, TREE* child1, TREE* child2, TREE* child3);
TREE* create_leaf(TREE_TYPE type);
TREE* create_leaf_symbol(HASH* hash_symbol);
void decompile(TREE* node, int(*output)(const char*));

#endif
