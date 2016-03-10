/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 1
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 *  Função com finalidade exclusiva para testes.
 */

#include <stdio.h>

int main(int argc, int *argv[])
{
	int ret;
	initMe();
	do{
		ret = yylex();
		if(ret > 127 && ret > -1) printf("Token lido: %i\n",ret);
		else printf("Token lido: %c\n",ret);
	}while(isRunning());

	printf("Numero de linhas: %i \n",getLineNumber());
    return 0;
}
