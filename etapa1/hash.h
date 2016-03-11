#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define HASH_SIZE 997
#define SYMBOL_IDENTIFIER 1
#define SYMBOL_LITERAL_CHAR 2
#define SYMBOL_LITERAL_INT 3
#define SYMBOL_LITERAL_STRING 4

typedef struct hash_node
{
  char *text;
  int type;
  struct hash_node *next;

}HASH;

HASH *symbol_table[HASH_SIZE];

void init_hash();
void print_hash();
int hash_address(char *text);
HASH* hash_add(int type, char *text);
