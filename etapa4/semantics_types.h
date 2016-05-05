/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 4
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#ifndef __SEMANTICS_TYPES__
#define __SEMANTICS_TYPES__

typedef int ID_TYPE;
#define ID_TYPE_SCALAR 1
#define ID_TYPE_VECTOR 2
#define ID_TYPE_FUNCTION 3

typedef int VAL_TYPE;
#define VAL_TYPE_INT 11
#define VAL_TYPE_REAL 12
#define VAL_TYPE_BOOL 13
#define VAL_TYPE_CHAR 14
#define VAL_TYPE_STRING 15
#define VAL_TYPE_UNIT 16

typedef struct param_list_node
{
  VAL_TYPE valueType;
  struct param_list_node *next;
} PARAM_LIST;

typedef struct data_type
{
  ID_TYPE identifierType;    /* used for identifier, can be either VECTOR, SCALAR or FUNCTION */
  VAL_TYPE valueType;        /* value of the expression containing the symbol,
                              * e.g. INT if it's a vector of int, or CHAR if it's a function returning char, etc. */
  PARAM_LIST *params;         /* used for functions, stores the types of the params of the function*/
} DATA_TYPE;

#endif
