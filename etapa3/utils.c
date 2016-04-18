/* INF01147 -­‐ Compiladores -­‐ 2016/1
 * Trabalho Prático - Etapa 2
 * Autores: Fernando Bombardelli da Silva (218324)
 *          Pedro Henrique Arruda Faustini (217432)
 */

#include "utils.h"
#include <string.h>
#include <stdlib.h>

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

char* addSlashes(char *source) {
  char *destination, *pDestination;
  int i, n, extraSpace=0;

  // Conta espaço extra a ser alocado
  n = strlen(source);
  for (i=0; i<n; i++) {
    switch (source[i]) {
      case '\n':case '"':case '\\':
        extraSpace++;
    }
  }
  // Aloca espaço para string destino
  destination = (char*)malloc(sizeof(char)*(n+extraSpace+1));
  if (!destination) {
    return NULL;
  }
  pDestination = destination;

  // Scaneia string source copiando os caracteres1
  for (i=0; i<n; i++) {
    switch (source[i]) {
      case '\n':
        *pDestination = '\\';
        pDestination++;
        *pDestination = 'n';
      break;
      case '"':case '\\':
        *pDestination = '\\';
        pDestination++;
      default:
        *pDestination = source[i];
    }
    pDestination++;
  }
  *pDestination = '\0';

  return destination;
}
