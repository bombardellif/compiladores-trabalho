#ifndef __ASSEMBLY_H__
#define __ASSEMBLY_H__

#include "tac.h"
#include <string.h>
#include <stdio.h>

int functionLabelCounter;
char buffer[50];

void convert_assembly_single(TAC* tac, FILE* output);
void AssemblyPrintListNext(TAC* tac, FILE* output);
TAC* output_assemblyReverse(TAC* tac);
int convert_assembly(TAC* tac, char* filename);

#endif