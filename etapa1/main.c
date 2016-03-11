/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 1
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 *  Função com finalidade exclusiva para testes.
 */

#include <stdio.h>
#include "hash.h"
int main(int argc, int *argv[])
{
		int ret;
		initMe();
		while(isRunning()){
			ret = yylex();
			if(ret > 127) printf("Token lido foi: %i\n",ret);
			else printf("Token lido foi: %c\n",ret);
		}

		printf("Numero de linhas: %i \n\nConteudo na tabela de simbolos:\n",getLineNumber());
		print_hash();
    return 0;
}
