#include "assembly.h"

void convert_assembly(TAC* tac, FILE* output, char* filename)
{
      functionLabelCounter = 0;
      fprintf(output, "	.file	\"");
      fprintf(output, "%s", filename);
      fprintf(output, "\"\n");

      AssemblyPrintListNext(output_assemblyReverse(tac), output);

      fprintf(output, "	.cfi_endproc");

}
void AssemblyPrintListNext(TAC* tac, FILE* output)
{
  if (!tac)
    return;

  convert_assembly_single(tac, output);
  AssemblyPrintListNext(tac->next, output);
}

TAC* output_assemblyReverse(TAC* tac)
{
  TAC* t;

  for (t=tac; t->prev; t=t->prev) {
    t->prev->next = t;
  }
  return t;
}

void convert_assembly_single(TAC* tac, FILE* output)
{
      if (!tac)
    return;

  switch (tac->type) {
    case TAC_SYMBOL: fprintf(output, "TAC_SYMBOL");
    break;
    case TAC_MOVE: fprintf(output, "TAC_MOVE");
    break;
    case TAC_STRIDX: fprintf(output, "TAC_STRIDX");
    break;
    case TAC_LOADIDX: fprintf(output, "TAC_LOADIDX");
    break;
    case TAC_ADD: fprintf(output, "TAC_ADD");
    break;
    case TAC_SUB: fprintf(output, "TAC_SUB");
    break;
    case TAC_MUL: fprintf(output, "TAC_MUL");
    break;
    case TAC_DIV: fprintf(output, "TAC_DIV");
    break;
    case TAC_LABEL: fprintf(output, "TAC_LABEL");
    break;
    case TAC_IFZ: fprintf(output, "TAC_IFZ");
    break;
    case TAC_BEGINFUN: 
                        fprintf(output, "	.text\n	.globl	");
                        fprintf(output, "%s", tac->op1->text);
                        fprintf(output, "\n	.type ");
                        fprintf(output, "%s", tac->op1->text);
                        fprintf(output, ", @function\n");
                        fprintf(output, "%s", tac->op1->text);
                        fprintf(output, ":\n.LFB");
                        sprintf (buffer, "%d", functionLabelCounter++);
                        fprintf(output, "%s:\n", buffer);
                        fprintf(output, "	.cfi_startproc\n");

    break;
    case TAC_ENDFUN: fprintf(output, "TAC_ENDFUN");
    break;
    case TAC_JUMP: fprintf(output, "TAC_JUMP");
    break;
    case TAC_CALL: fprintf(output, "TAC_CALL");
    break;
    case TAC_ARG: fprintf(output, "TAC_ARG");
    break;
    case TAC_RET: fprintf(output, "TAC_RET");
    break;
    case TAC_PRINT: fprintf(output, "TAC_PRINT");
    break;
    case TAC_READ: fprintf(output, "TAC_READ");
    break;
    case TAC_NOP: fprintf(output, "TAC_NOP");
    break;
    case TAC_ANEG: fprintf(output, "TAC_ANEG");
    break;
    case TAC_LTZ: fprintf(output, "TAC_LTZ");
    break;
    case TAC_GTZ: fprintf(output, "TAC_GTZ");
    break;
    case TAC_LEZ: fprintf(output, "TAC_LEZ");
    break;
    case TAC_GEZ: fprintf(output, "TAC_GEZ");
    break;
    case TAC_AND: fprintf(output, "TAC_AND");
    break;
    case TAC_OR: fprintf(output, "TAC_OR");
    break;
    case TAC_EQZ: fprintf(output, "TAC_EQZ");
    break;
    case TAC_PUSH: fprintf(output, "TAC_PUSH");
    break;
    case TAC_CLNSTACK: fprintf(output, "TAC_CLNSTACK");
    break;
    default: fprintf(output, "TAC_DEFAULT");
  }
  fprintf(output, ",%s", tac->res ? tac->res->text : "_");
  fprintf(output, ",%s", tac->op1 ? tac->op1->text : "_");
  fprintf(output, ",%s)\n", tac->op2 ? tac->op2->text : "_");

}
