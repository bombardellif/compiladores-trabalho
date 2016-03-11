/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 1
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 *  Função com finalidade exclusiva para testes.
 */

#include <stdio.h>
#include "tokens.h"

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

/* Test case especiais1 */
void test_especiais1() {
  int ret;

  printf("/**** TEST: ESPECIAIS 1 ****/\n");
  if (! test_setUp("test-cases/especiais1") ) {
    printf("Error by opening file %s", "test-cases/especiais1");
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

/* Test case especiais2 */
void test_especiais2() {
  int ret;

  printf("/**** TEST: ESPECIAIS 2 ****/\n");
  if (! test_setUp("test-cases/especiais2") ) {
    printf("Error by opening file %s", "test-cases/especiais2");
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
