/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 2
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "tree.h"

HASH *symbol_table[HASH_SIZE];

void init_hash()
{
    memset(symbol_table, 0, HASH_SIZE * sizeof(HASH*));
}

int hash_address(char *text)
{
    unsigned int address = 1, i;
    for(i=0; i<strlen(text);i++)
        address = (address * text[i]) % HASH_SIZE + 1;

    return (address - 1);
}

HASH* hash_add(int type, char *text)
{
    int address;
    HASH *node, *insertNode;

    address = hash_address(text);
    insertNode = symbol_table[address];
    // Insere somente se símbolo ainda não existe na tabela
    while (insertNode && (insertNode->type != type || strcmp(insertNode->text, text)))
      insertNode = insertNode->next;

    // Se insertNode é null, então não achou um simbolo igual na lista, pois percorreu até o fim
    if (!insertNode) {
      node = (HASH*)calloc(1, sizeof(HASH));
      node->type = type;
      node->text = text; // text já deve ter sido alocado fora da função
      node->dataType.identifierType = ID_TYPE_UNDEF;
      node->dataType.valueType = -1;
      node->dataType.params = NULL;
      node->name = NULL;

      node->next = symbol_table[address];
      symbol_table[address] = node;
    } else {
      node = insertNode;
    }

    return node;
}

HASH* get_hash_node(char * text)
{
    int i;
    HASH *node;
    for(i=0; i<HASH_SIZE; i++)
        for(node = symbol_table[i]; node; node=node->next)
	    	if(!strcmp(node->text,text))
				return node;

    return NULL;
}

int hash_update_type(char * text, ID_TYPE idType, VAL_TYPE valType, PARAM_LIST *params)
{
    int i;
    HASH *node;
    for(i=0; i<HASH_SIZE; i++)
      for(node = symbol_table[i]; node; node=node->next)
        if(!strcmp(node->text,text))
    			if(node->dataType.identifierType == ID_TYPE_UNDEF)
    			{
    				node->dataType.identifierType = idType;
    				node->dataType.valueType = valType;
        		node->dataType.params = params;
    				return 1;
    			}
    			else
    				return 0;
    return 0;
}

void print_hash()
{
    int i;
    HASH *node;
    for(i=0; i<HASH_SIZE; i++)
        for(node = symbol_table[i]; node; node=node->next) {
            switch (node->type) {
              case SYMBOL_IDENTIFIER:
                printf("Table[%d] = %s is SYMBOL_IDENTIFIER\n", i, node->text);
              break;
              case SYMBOL_LITERAL_REAL:
                printf("Table[%d] = %s is SYMBOL_LITERAL_REAL\n", i, node->text);
              break;
              case SYMBOL_LITERAL_CHAR:
                printf("Table[%d] = %s is SYMBOL_LITERAL_CHAR\n", i, node->text);
              break;
              case SYMBOL_LITERAL_STRING:
                printf("Table[%d] = %s is SYMBOL_LITERAL_STRING\n", i, node->text);
              break;
              case SYMBOL_LITERAL_INT:
                printf("Table[%d] = %s is SYMBOL_LITERAL_INT\n", i, node->text);
              break;
              case SYMBOL_LITERAL_BOOL:
                printf("Table[%d] = %s is SYMBOL_LITERAL_BOOL\n", i, node->text);
              break;
              default:
                printf("Table[%d]. Type not identified\n", i);
            }

            switch (node->dataType.valueType) {
              case VAL_TYPE_INT:
                printf("Table[%d] = %s is int\n", i, node->text);
              break;
              case VAL_TYPE_REAL:
                printf("Table[%d] = %s is real\n", i, node->text);
              break;
              case VAL_TYPE_BOOL:
                printf("Table[%d] = %s is bool\n", i, node->text);
              break;
              case VAL_TYPE_CHAR:
                printf("Table[%d] = %s is char\n", i, node->text);
              break;
              case VAL_TYPE_STRING:
                printf("Table[%d] = %s is string\n", i, node->text);
              break;
              case VAL_TYPE_UNIT:
                printf("Table[%d] = %s is unit\n", i, node->text);
            }
        }
}

HASH* hash_make_temp(void)
{
  static int nextTemp = 0;
  char *buffer;
  HASH* new;

  buffer = (char*)malloc(sizeof(char)*10);
  sprintf(buffer, "_Temp_%d", nextTemp++);
  new = hash_add(SYMBOL_IDENTIFIER, buffer);
  new->dataType.identifierType = ID_TYPE_SCALAR;
  new->dataType.valueType = VAL_TYPE_REAL; /*FIXME: Indicar qual será o tipo do temporário */

  return new;
}

void hash_set_new_name(HASH* node)
{
  static int nextNameIdx = 0;

  node->name = (char*)malloc(sizeof(char)*10);
  sprintf(node->name, "_abs_%d", nextNameIdx++);
}

void hash_output_declaration(FILE* output, HASH* node, char* value, ID_TYPE identifierType, VAL_TYPE valueType)
{
  switch (identifierType) {
    case ID_TYPE_SCALAR:
      fprintf(output, "\t.globl %s\n", node->name);
      fprintf(output, "\t.type %s, @object\n", node->name);
      switch (valueType) {
        case VAL_TYPE_INT:
        case VAL_TYPE_BOOL:
          fprintf(output, "\t.align 4\n");
          fprintf(output, "\t.size %s, 4\n", node->name);
          fprintf(output, "%s:\n\t.long %s\n", node->name, value?value:"0");
        break;
        case VAL_TYPE_REAL:
          fprintf(output, "\t.align 4\n");
          fprintf(output, "\t.size %s, 4\n", node->name);
          fprintf(output, "%s:\n\t.float %s\n", node->name, value?value:"0");
        break;
        case VAL_TYPE_CHAR:
          fprintf(output, "\t.size %s, 1\n", node->name);
          fprintf(output, "%s:\n\t.byte %s\n", node->name, value?value:"0");
        break;
        break;
        case VAL_TYPE_STRING:
          fprintf(output, "\t.size %s, %d\n", node->name, strlen(value)+1);
          fprintf(output, "%s:\n\t.string \"%s\"\n", node->name, value?value:"");
      }
    break;
    case ID_TYPE_FUNCTION:
      fprintf(output, "\t.globl	%s\n", node->name);
      fprintf(output, "\t.type %s, @function\n", node->name);
  }
}

/*Inicialmente, as variaveis (sao todas globais) sao
declaradas no segmento .data com valor provisorio 1.ast
Isso porque a hash nao contem a associacao variavel-valor,
o que so e descoberto ao percorrer a arvore tac*/
void hash_output_assembly(FILE* output)
{
  int i;
  HASH* node;
  for(i=0; i<HASH_SIZE; i++)
    for(node=symbol_table[i]; node; node=node->next) {
      switch (node->type) {
        case SYMBOL_LITERAL_INT:
          // Constantes no código C são declaradas como variáveis em códgo assembly
          hash_set_new_name(node);
          hash_output_declaration(output, node,
            node->text,
            ID_TYPE_SCALAR,
            VAL_TYPE_INT);
        break;
        case SYMBOL_LITERAL_REAL:
          hash_set_new_name(node);
          hash_output_declaration(output, node,
            node->text,
            ID_TYPE_SCALAR,
            VAL_TYPE_REAL);
        break;
        case SYMBOL_LITERAL_CHAR:
          hash_set_new_name(node);
          hash_output_declaration(output, node,
            node->text,
            ID_TYPE_SCALAR,
            VAL_TYPE_CHAR);
        break;
        case SYMBOL_LITERAL_BOOL:
          hash_set_new_name(node);
          hash_output_declaration(output, node,
            node->text,
            ID_TYPE_SCALAR,
            VAL_TYPE_BOOL);
        break;
        case SYMBOL_LITERAL_STRING:
          hash_set_new_name(node);
          hash_output_declaration(output, node,
            node->text,
            ID_TYPE_SCALAR,
            VAL_TYPE_STRING);
        break;
        case SYMBOL_IDENTIFIER:
          // Nome da variável no código assembly é o msm nome da variável no código C
          node->name = node->text;
          hash_output_declaration(output, node,
            find_declaration_value(node->name),
            node->dataType.identifierType,
            node->dataType.valueType);
        }
    }
}

HASH* hash_make_label(void)
{
  static int nextTemp = 0;
  char *buffer;

  buffer = (char*)malloc(sizeof(char)*11);
  sprintf(buffer, "_Label_%d", nextTemp++);
  return hash_add(SYMBOL_LABEL, buffer);
}

HASH* hash_add_absolute(int value)
{
  char *buffer;

  buffer = (char*)malloc(sizeof(char)*5);
  sprintf(buffer, "%d", value);
  return hash_add(SYMBOL_LITERAL_INT, buffer);
}

VAL_TYPE hash_get_valtype_memsize(HASH* node)
{
  switch (node->type) {
    case SYMBOL_LITERAL_INT:
    case SYMBOL_LITERAL_CHAR:
    case SYMBOL_LITERAL_BOOL:
      return VAL_TYPE_INT;
    break;
    case SYMBOL_LITERAL_REAL:
      return VAL_TYPE_REAL;
    case SYMBOL_LITERAL_STRING:
      return VAL_TYPE_STRING;
    case SYMBOL_IDENTIFIER:
      switch (node->dataType.valueType) {
        case VAL_TYPE_INT:
        case VAL_TYPE_CHAR:
        case VAL_TYPE_BOOL:
          return VAL_TYPE_INT;
        case VAL_TYPE_REAL:
          return VAL_TYPE_REAL;
        case VAL_TYPE_STRING:
          return VAL_TYPE_STRING;
      }
  }
  return VAL_TYPE_UNIT;
}
