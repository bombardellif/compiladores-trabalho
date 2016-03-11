#include "hash.h"

void init_hash()
{
    int i;
    for(i=0; i<HASH_SIZE; i++)
        symbol_table[i] = 0;
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
    HASH *node;
    node = (HASH*)calloc(1, sizeof(HASH));
    node->type = type;
    node->text = (char*)calloc(strlen(text)+1,sizeof(char));
    strcpy(node->text,text);
    address = hash_address(text);
    node->next = symbol_table[address];
    symbol_table[address] = node;
    return node;
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
