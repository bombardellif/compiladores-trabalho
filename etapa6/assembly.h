#ifndef __ASSEMBLY_H__
#define __ASSEMBLY_H__

#include "tac.h"
#include <string.h>
#include <stdio.h>

void convert_assembly_single(TAC* tac, FILE* output);
void AssemblyPrintListNext(TAC* tac, FILE* output);
TAC* output_assemblyReverse(TAC* tac);
void convert_assembly(TAC* tac, FILE* output, char* filename);

#endif