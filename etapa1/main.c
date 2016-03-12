/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 1
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 *  Função com finalidade exclusiva para testes.
 */

#include <stdio.h>
#include "test.c"

int main(int argc, int *argv[])
{
		test_reserved1();

		test_reserved2();

		test_compostos1();

		test_compostos2();

		test_especiais1();

		test_identificadores1();

		test_literais1();

		test_literais2();

		test_comments1();
		
		test_get_hash_node();
    return 0;
}
