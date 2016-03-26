#ifndef __HASH__
#define __HASH__

#define HASH_SIZE 997
#define SYMBOL_LITERAL_INT 1
#define SYMBOL_LITERAL_REAL 2
#define SYMBOL_LITERAL_CHAR 3
#define SYMBOL_LITERAL_STRING 4
#define SYMBOL_IDENTIFIER 7

typedef struct hash_node
{
  char *text;
  int type;
  struct hash_node *next;

}HASH;

void init_hash();
void print_hash();
int hash_address(char *text);
HASH* get_hash_node(char * text);
HASH* hash_add(int type, char *text);

#endif
