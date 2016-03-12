/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 1
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 *  Função com finalidade exclusiva para testes.
 */

#include <stdio.h>
#include "tokens.h"
#include "hash.h"

extern FILE * yyin;

int test_setUp(char* input) {
  initMe();
  return !!(yyin = fopen(input, "r"));
}

void test_tearDown() {
  printf("Numero de linhas: %i \n\nConteudo na tabela de simbolos:\n",getLineNumber());
  print_hash();
}

void test_assertEqual(int result, int expected) {
  if (result != expected)
    printf("FAIL: \n\tExpected: %d\tResult: %d\n", expected, result);
  else
    printf("SUCCESS: %d\n", result);
}

/* Test case reservadas1 */
void test_reserved1() {
  int ret;

  printf("/**** TEST: RESERVADAS 1 ****/\n");
  if (! test_setUp("test-cases/reservadas1") ) {
    printf("Error by opening file %s", "test-cases/reservadas1");
    return;
  }

  while(isRunning()) {
    // int
    ret = yylex();
    test_assertEqual(ret, KW_INT);
    // real
    ret = yylex();
    test_assertEqual(ret, KW_REAL);
    // bool
    ret = yylex();
    test_assertEqual(ret, KW_BOOL);
    // char
    ret = yylex();
    test_assertEqual(ret, KW_CHAR);
    // if
    ret = yylex();
    test_assertEqual(ret, KW_IF);
    // else
    ret = yylex();
    test_assertEqual(ret, KW_ELSE);
    // while
    ret = yylex();
    test_assertEqual(ret, KW_WHILE);
    // input
    ret = yylex();
    test_assertEqual(ret, KW_INPUT);
    // output
    ret = yylex();
    test_assertEqual(ret, KW_OUTPUT);
    // return
    ret = yylex();
    test_assertEqual(ret, KW_RETURN);
    // EOF
    ret = yylex();
    test_assertEqual(ret, 0);
  }

  test_tearDown();
  printf("/****************************/\n");
}

/* Test case reservadas2 */
void test_reserved2() {
  int ret;

  printf("/**** TEST: RESERVADAS 2 ****/\n");
  if (! test_setUp("test-cases/reservadas2") ) {
    printf("Error by opening file %s", "test-cases/reservadas2");
    return;
  }

  while(isRunning()) {
    // input
    ret = yylex();
    test_assertEqual(ret, KW_INPUT);
    test_assertEqual(getLineNumber(), 1);
    // output
    ret = yylex();
    test_assertEqual(ret, KW_OUTPUT);
    test_assertEqual(getLineNumber(), 1);
    // return
    ret = yylex();
    test_assertEqual(ret, KW_RETURN);
    test_assertEqual(getLineNumber(), 1);
    // int
    ret = yylex();
    test_assertEqual(ret, KW_INT);
    test_assertEqual(getLineNumber(), 2);
    // bool
    ret = yylex();
    test_assertEqual(ret, KW_BOOL);
    test_assertEqual(getLineNumber(), 2);
    // realboolchar
    ret = yylex();
    test_assertEqual(ret, TK_IDENTIFIER);
    test_assertEqual(getLineNumber(), 3);
    // real
    ret = yylex();
    test_assertEqual(ret, KW_REAL);
    test_assertEqual(getLineNumber(), 3);
    // bool
    ret = yylex();
    test_assertEqual(ret, KW_BOOL);
    test_assertEqual(getLineNumber(), 3);
    // char
    ret = yylex();
    test_assertEqual(ret, KW_CHAR);
    test_assertEqual(getLineNumber(), 3);
    // if
    ret = yylex();
    test_assertEqual(ret, KW_IF);
    test_assertEqual(getLineNumber(), 4);
    // else
    ret = yylex();
    test_assertEqual(ret, KW_ELSE);
    test_assertEqual(getLineNumber(), 6);
    // while
    ret = yylex();
    test_assertEqual(ret, KW_WHILE);
    test_assertEqual(getLineNumber(), 6);
    // EOF
    ret = yylex();
    test_assertEqual(ret, 0);
    test_assertEqual(getLineNumber(), 7);
  }

  test_tearDown();
  printf("/****************************/\n");
}

/* Test case compostos1 */
void test_compostos1() {
  int ret;

  printf("/**** TEST: COMPOSTOS 1 ****/\n");
  if (! test_setUp("test-cases/compostos1") ) {
    printf("Error by opening file %s", "test-cases/compostos1");
    return;
  }

  while(isRunning()) {
    // le
    ret = yylex();
    test_assertEqual(ret, OPERATOR_LE);
    // ge
    ret = yylex();
    test_assertEqual(ret, OPERATOR_GE);
    // eq
    ret = yylex();
    test_assertEqual(ret, OPERATOR_EQ);
    // ne
    ret = yylex();
    test_assertEqual(ret, OPERATOR_NE);
    // and
    ret = yylex();
    test_assertEqual(ret, OPERATOR_AND);
    // or
    ret = yylex();
    test_assertEqual(ret, OPERATOR_OR);
    // EOF
    ret = yylex();
    test_assertEqual(ret, 0);
  }

  test_tearDown();
  printf("/****************************/\n");
}

/* Test case compostos2 */
void test_compostos2() {
  int ret;

  printf("/**** TEST: COMPOSTOS 2 ****/\n");
  if (! test_setUp("test-cases/compostos2") ) {
    printf("Error by opening file %s", "test-cases/compostos2");
    return;
  }

  while(isRunning()) {
    // id1
    ret = yylex();
    test_assertEqual(ret, TK_IDENTIFIER);
    test_assertEqual(getLineNumber(), 1);
    // le
    ret = yylex();
    test_assertEqual(ret, OPERATOR_LE);
    test_assertEqual(getLineNumber(), 1);
    // id2
    ret = yylex();
    test_assertEqual(ret, TK_IDENTIFIER);
    test_assertEqual(getLineNumber(), 1);
    // id1
    ret = yylex();
    test_assertEqual(ret, TK_IDENTIFIER);
    test_assertEqual(getLineNumber(), 2);
    // ge
    ret = yylex();
    test_assertEqual(ret, OPERATOR_GE);
    test_assertEqual(getLineNumber(), 2);
    // id3
    ret = yylex();
    test_assertEqual(ret, TK_IDENTIFIER);
    test_assertEqual(getLineNumber(), 4);
    // eq
    ret = yylex();
    test_assertEqual(ret, OPERATOR_EQ);
    test_assertEqual(getLineNumber(), 4);
    // id3
    ret = yylex();
    test_assertEqual(ret, TK_IDENTIFIER);
    test_assertEqual(getLineNumber(), 4);
    // 1
    ret = yylex();
    test_assertEqual(ret, LIT_INTEGER);
    test_assertEqual(getLineNumber(), 7);
    // ne
    ret = yylex();
    test_assertEqual(ret, OPERATOR_NE);
    test_assertEqual(getLineNumber(), 7);
    // 0
    ret = yylex();
    test_assertEqual(ret, LIT_INTEGER);
    test_assertEqual(getLineNumber(), 7);
    // true
    ret = yylex();
    test_assertEqual(ret, LIT_TRUE);
    test_assertEqual(getLineNumber(), 8);
    // and
    ret = yylex();
    test_assertEqual(ret, OPERATOR_AND);
    // true
    ret = yylex();
    test_assertEqual(ret, LIT_TRUE);
    test_assertEqual(getLineNumber(), 8);
    // or
    ret = yylex();
    test_assertEqual(ret, OPERATOR_OR);
    test_assertEqual(getLineNumber(), 8);
    // id3
    ret = yylex();
    test_assertEqual(ret, TK_IDENTIFIER);
    test_assertEqual(getLineNumber(), 8);
    // EOF
    ret = yylex();
    test_assertEqual(ret, 0);
  }

  test_tearDown();
  printf("/****************************/\n");
}

/* Test case especiais1 */
void test_especiais1() {
  int ret, i=1, j;
  char symbols[] = {',',';',':','(',')','[',']','{','}','+','-','*','/','<','>','=','!','&','$'};

  printf("/**** TEST: ESPECIAIS 1 ****/\n");
  if (! test_setUp("test-cases/especiais1") ) {
    printf("Error by opening file %s", "test-cases/especiais1");
    return;
  }

  while(isRunning()) {
    for (j=0; j<19; j++) {
      ret = yylex();
      test_assertEqual(ret, symbols[j]);
      test_assertEqual(getLineNumber(), i);
    }

    if (i == 2) {
      // EOF
      ret = yylex();
      test_assertEqual(ret, 0);
    }
    i++;
  }

  test_tearDown();
  printf("/****************************/\n");
}

/* Test case identificadores1 */
void test_identificadores1() {
  int ret, i=1;

  printf("/**** TEST: IDENTIFICADORES 1 ****/\n");
  if (! test_setUp("test-cases/identificadores1") ) {
    printf("Error by opening file %s", "test-cases/identificadores1");
    return;
  }

  while(isRunning()) {
    if (i<=7) {
      ret = yylex();
      test_assertEqual(ret, TK_IDENTIFIER);
      test_assertEqual(getLineNumber(), i);
    } else if (i == 8) {
      // EOF
      ret = yylex();
      test_assertEqual(ret, TK_IDENTIFIER);
      test_assertEqual(getLineNumber(), i);

      ret = yylex();
      test_assertEqual(ret, TK_IDENTIFIER);
      test_assertEqual(getLineNumber(), i);
    } else if (i==9) {

    } else if (i <= 10) {
      ret = yylex();
      test_assertEqual(ret, TOKEN_ERROR);
      test_assertEqual(getLineNumber(), i);

      ret = yylex();
      test_assertEqual(ret, TK_IDENTIFIER);
      test_assertEqual(getLineNumber(), i);
    } else if (i <= 12) {
      ret = yylex();
      test_assertEqual(ret, LIT_INTEGER);
      test_assertEqual(getLineNumber(), i);

      ret = yylex();
      test_assertEqual(ret, TK_IDENTIFIER);
      test_assertEqual(getLineNumber(), i);
    } else if (i <= 13) {
      ret = yylex();
      test_assertEqual(ret, LIT_INTEGER);
      test_assertEqual(getLineNumber(), i);

      ret = yylex();
      test_assertEqual(ret, TOKEN_ERROR);
      test_assertEqual(getLineNumber(), i);
    } else if (i <= 14) {
      ret = yylex();
      test_assertEqual(ret, TK_IDENTIFIER);
      test_assertEqual(getLineNumber(), i);

      ret = yylex();
      test_assertEqual(ret, '-');
      test_assertEqual(getLineNumber(), i);

      ret = yylex();
      test_assertEqual(ret, TK_IDENTIFIER);
      test_assertEqual(getLineNumber(), i);

      ret = yylex();
      test_assertEqual(ret, ';');
      test_assertEqual(getLineNumber(), i);
    } else if (i <= 15) {
      ret = yylex();
      test_assertEqual(ret, TK_IDENTIFIER);
      test_assertEqual(getLineNumber(), i);

      ret = yylex();
      test_assertEqual(ret, TOKEN_ERROR);
      test_assertEqual(getLineNumber(), i);

      ret = yylex();
      test_assertEqual(ret, TK_IDENTIFIER);
      test_assertEqual(getLineNumber(), i);
    } else
      break;
    i++;
  }

  test_tearDown();
  printf("/****************************/\n");
}

/* Test case literais1 */
void test_literais1() {
  int ret, j=0;

  printf("/**** TEST: LITERAIS 1 ****/\n");
  if (! test_setUp("test-cases/literais1") ) {
    printf("Error by opening file %s", "test-cases/literais1");
    return;
  }

  while(isRunning()) {
    ret = yylex();
    if (j==0) {
      test_assertEqual(ret, LIT_TRUE);
    } else if (j==1) {
      test_assertEqual(ret, LIT_FALSE);
    } else if (j<=4) {
      test_assertEqual(ret, LIT_CHAR);
    } else if (j<=13) {
      test_assertEqual(ret, LIT_STRING);
    } else if (j<=15) {
      test_assertEqual(ret, LIT_INTEGER);
    } else if (j<=17) {
      test_assertEqual(ret, TK_IDENTIFIER);
    } else
      test_assertEqual(ret, 0);
    j++;
  }

  test_tearDown();
  printf("/****************************/\n");
}

/* Test case literais2 */
void test_literais2() {
  int ret, j=0, i=1;

  printf("/**** TEST: LITERAIS 2 ****/\n");
  if (! test_setUp("test-cases/literais2") ) {
    printf("Error by opening file %s", "test-cases/literais2");
    return;
  }

  while(isRunning()) {
    ret = yylex();
    if (j<=2) {
      test_assertEqual(ret, TK_IDENTIFIER);
      test_assertEqual(getLineNumber(), i);
      if (j == 2) i++;
    } else if (j<=5) {
      test_assertEqual(ret, LIT_STRING);
      test_assertEqual(getLineNumber(), i);
      if (j == 4) i++;
    } else if (j<=6) {
      test_assertEqual(ret, TK_IDENTIFIER);
      test_assertEqual(getLineNumber(), i);
    } else if (j<=7) {
      test_assertEqual(ret, TOKEN_ERROR);
      test_assertEqual(getLineNumber(), i);
      i++;
    } else if (j<=10) {
      test_assertEqual(ret, LIT_CHAR);
      test_assertEqual(getLineNumber(), i);
      if (j == 9) i++;
    } else if (j<=11) {
      test_assertEqual(ret, LIT_INTEGER);
      test_assertEqual(getLineNumber(), i);
    } else if (j<=12) {
      test_assertEqual(ret, TOKEN_ERROR);
      test_assertEqual(getLineNumber(), i);
      i++;
    } else if (j<=13) {
      test_assertEqual(ret, LIT_STRING);
      test_assertEqual(getLineNumber(), i);

      ret = yylex();
      test_assertEqual(ret, '+');
      ret = yylex();
      test_assertEqual(ret, LIT_INTEGER);
      ret = yylex();
      test_assertEqual(ret, '*');
      ret = yylex();
      test_assertEqual(ret, TOKEN_ERROR);
      ret = yylex();
      test_assertEqual(ret, TOKEN_ERROR);
      ret = yylex();
      test_assertEqual(ret, ';');
      ret = yylex();
      test_assertEqual(ret, LIT_STRING);
      ret = yylex();
      test_assertEqual(ret, TOKEN_ERROR);
      ret = yylex();
      test_assertEqual(ret, TOKEN_ERROR);
    } else
      test_assertEqual(ret, 0);
    j++;
  }

  test_tearDown();
  printf("/****************************/\n");
}

/* Test case comments1 */
void test_comments1() {
  int ret, j=0, i;

  printf("/**** TEST: COMMENTS 1 ****/\n");
  if (! test_setUp("test-cases/comments1") ) {
    printf("Error by opening file %s", "test-cases/comments1");
    return;
  }

  i=5;
  while(isRunning()) {
    ret = yylex();
    test_assertEqual(ret, KW_REAL);
    test_assertEqual(getLineNumber(), i);
    ret = yylex();
    test_assertEqual(ret, TK_IDENTIFIER);
    test_assertEqual(getLineNumber(), i);
    ret = yylex();
    test_assertEqual(ret, '=');
    test_assertEqual(getLineNumber(), i);
    ret = yylex();
    test_assertEqual(ret, LIT_INTEGER);
    test_assertEqual(getLineNumber(), i);
    ret = yylex();
    test_assertEqual(ret, ',');
    test_assertEqual(getLineNumber(), i);
    ret = yylex();
    test_assertEqual(ret, LIT_INTEGER);
    test_assertEqual(getLineNumber(), i);
    ret = yylex();
    test_assertEqual(ret, ';');
    test_assertEqual(getLineNumber(), i);

    //EOF
    ret = yylex();
    test_assertEqual(ret, 0);
    test_assertEqual(getLineNumber(), 11);
  }

  test_tearDown();
  printf("/****************************/\n");
}

void test_get_hash_node()
{
	HASH *node;
	printf("/**** TEST: HASH_GET_NODE ****/\n");
  	if (! test_setUp("test-cases/literais_identificadores") ) {
    	printf("Error by opening file %s", "test-cases/comments1");
    	return;
 	}
 	while(isRunning())
 	{
 		yylex();
 	}
 		node = get_hash_node("sentence");
 		printf("Getting sentence with get_hash_node(\"sentence\"):        ");
 		test_assertEqual(node->type, SYMBOL_LITERAL_STRING);
 		
 		node = get_hash_node("ident12334");
 		printf("Getting ident12334 with get_hash_node(\"ident12334\"):    ");
 		test_assertEqual(node->type, SYMBOL_IDENTIFIER);
 		
 		node = get_hash_node("2331");
 		printf("Getting 2331 with get_hash_node(\"2331\"):		");
 		test_assertEqual(node->type, SYMBOL_LITERAL_INT);
 		
 		node = get_hash_node("number");
 		printf("Getting number with get_hash_node(\"number\"):	  	");
 		test_assertEqual(node->type, SYMBOL_IDENTIFIER);
 		
 		node = get_hash_node("ident12334");
 		printf("Getting ident12334 with get_hash_node(\"ident12334\"):    ");
 		test_assertEqual(node->type, SYMBOL_IDENTIFIER);
 		
 		node = get_hash_node("c");
 		printf("Getting c with get_hash_node(\"c\"):	  	  	");
 		test_assertEqual(node->type, SYMBOL_LITERAL_CHAR);
 		
 		node = get_hash_node("02");
 		printf("Getting 02 with get_hash_node(\"02\"):	  	  	");
 		test_assertEqual(node->type, SYMBOL_LITERAL_INT);
 		
 		node = get_hash_node("naoExiste");
 		printf("Getting naoExiste with get_hash_node(\"naoExiste\"): 	");
 		if(node==NULL)	printf("SUCCESS: Key inexistente na hash\n");
 		
 		node = get_hash_node("string");
 		printf("Getting string with get_hash_node(\"string\"): 		");
 		test_assertEqual(node->type, SYMBOL_LITERAL_STRING);		 		
 		
  	test_tearDown();
  	printf("/****************************/\n");
}



