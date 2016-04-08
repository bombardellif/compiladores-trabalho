/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 2
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#include "utils.h"
#include <string.h>

void stripSlashes(char *destination, char *source) {
  char *pDestination = destination;
  char *pSource = source;
  char *pCh;
  int sizeToCopy;

  // Enquanto houver backslahes
  while (pCh = strchr(pSource, '\\')) {
    // copia a str source para destination sem a barra
    sizeToCopy = pCh-pSource;
    strncpy(pDestination, pSource, sizeToCopy);
    // avança os ponteiros de detination e source
    pDestination += sizeToCopy;
    pSource += sizeToCopy;
    // verifica o próximo caracter do source
    switch (*(++pSource)) {
      // caso n, coloca uma quebra de linha no destination
      case 'n':
        pDestination[0] = '\n';
      break;
      // caso default, simplesmente copia o caracter
      default:
        pDestination[0] = pSource[0];
    }
    pDestination++;
    pSource++;
  }

  // Não encontrou mais backslashes, copia source para destination até o null-char '\0'
  strcpy(pDestination, pSource);
}
