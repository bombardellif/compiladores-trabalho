/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 2
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

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

    node = (HASH*)calloc(1, sizeof(HASH));
    node->type = type;
    node->text = text; // text já deve ter sido alocado fora da função

    address = hash_address(text);
    insertNode = symbol_table[address];
    // Insere somente se símbolo ainda não existe na tabela
    while (insertNode && (insertNode->type != type || strcmp(insertNode->text, text)))
      insertNode = insertNode->next;
    // Se insertNode é null, então não achou um simbolo igual na lista, pois percorreu até o fim
    if (!insertNode) {
      node->next = symbol_table[address];
      symbol_table[address] = node;
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

void print_hash()
{
    int i;
    HASH *node;
    for(i=0; i<HASH_SIZE; i++)
        for(node = symbol_table[i]; node; node=node->next)
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
              default:
                printf("Table[%d]. Type not identified\n", i);
            }
}
