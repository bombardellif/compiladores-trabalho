#include "assembly.h"

int convert_assembly(TAC* tac, char* filename)
{
      FILE* outfile;
		  int len = strlen(filename);
    	char str[len+2];
		  strcpy(str,filename);
		  strcat(str, ".s" );
	  	if(!(outfile = fopen(str, "w")))
          return(5);

      functionLabelCounter = 0;
      fprintf(outfile, "\t.file	\"");
      fprintf(outfile, "%s", filename);
      fprintf(outfile, "\"\n");

      // Segmento de dados
      fprintf(outfile, "\t.data\n");
      hash_output_assembly(outfile);

      // Segmento de código
      fprintf(outfile, "\t.text\n");
      AssemblyPrintListNext(output_assemblyReverse(tac), outfile);

      fclose(outfile);
      return 1;
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

void assembly_move(HASH *to, HASH* from, FILE* output)
{
  fprintf(output, "\tmovl %s(%%rip), %%eax\n", from?from->name:0);
  fprintf(output, "\tmovl %%eax, %s(%%rip)\n", to?to->name:0);
}

void convert_assembly_single(TAC* tac, FILE* output)
{
      if (!tac)
    return;

  switch (tac->type) {
    case TAC_SYMBOL: /*TODO: AQUELAS QUE AINDA TEM TAC*/
    break;
    case TAC_MOVE:  // MOVE e ARG têm a mesma semântica na nossa linguagem
    case TAC_ARG:
      assembly_move(tac->res, tac->op1, output);
    break;
    case TAC_STRIDX: fprintf(output, "TAC_STRIDX");
    break;
    case TAC_LOADIDX: fprintf(output, "TAC_LOADIDX");
    break;
    case TAC_ADD:
    				fprintf(output, "\tmovl\t_%s(%%rip), %%edx\n",tac->op1->text);
    				fprintf(output, "\tmovl\t_%s(%%rip), %%eax\n",tac->op2->text);
    				fprintf(output, "\taddl\t%%edx, %%eax\n");
    				fprintf(output, "\tmovl\t%%eax, + %s(%%rip)\n",tac->res->text);
    break;
    case TAC_SUB: fprintf(output, "TAC_SUB");
    break;
    case TAC_MUL: fprintf(output, "TAC_MUL");
    break;
    case TAC_DIV: fprintf(output, "TAC_DIV");
    break;
    case TAC_LABEL:
                        fprintf(output, ".%s\n", tac->res->text);
    break;
    case TAC_IFZ: fprintf(output, "TAC_IFZ");
    break;
    case TAC_BEGINFUN:
      fprintf(output, "%s:\n", tac->op1?tac->op1->text:"");
      fprintf(output, ".LFB");
      sprintf(buffer, "%d", functionLabelCounter++);
      fprintf(output, "%s:\n", buffer);
      fprintf(output, "\t.cfi_startproc\n");
      fprintf(output, "\tpushq %%rbp\n");
      fprintf(output, "\tmovq	%%rsp, %%rbp\n");
    break;
    case TAC_ENDFUN:
      fprintf(output, "\tpopq %%rbp\n");
      fprintf(output, "\tret\n");
      fprintf(output, "\t.cfi_endproc\n");
    break;
    case TAC_JUMP:
                        fprintf(output, "\tjmp .");
                        fprintf(output, "%s \n", tac->res->text);
    break;
    case TAC_CALL:
      fprintf(output, "\tmovl $0, %%eax\n");
      fprintf(output, "\tcall %s\n", tac->op1?tac->op1->name:0);
      // move o resultado de %eax para temporário de retorno da função
      fprintf(output, "\tmovl	%%eax, %s(%%rip)\n", tac->res?tac->res->name:0);
    break;
    case TAC_RET:
      // Retorna sempre no %eax
      fprintf(output, "\tmovl	%s(%%rip), %%eax\n", tac->op1?tac->op1->name:0);
      fprintf(output, "\tpopq	%%rbp\n");
      fprintf(output, "\tret\n");
    break;
    case TAC_PRINT:
      // Send parameters depending on the type of the variables
      if (tac->op1 && tac->op2) {
        switch (hash_get_valtype_memsize(tac->op1)) {
          case VAL_TYPE_INT:
            fprintf(output, "\tmovl %s(%%rip), %%esi\n", tac->op1->name);
            fprintf(output, "\tmovl $0, %%eax\n");
          break;
          case VAL_TYPE_STRING:
            fprintf(output, "\tmovl $%s, %%esi\n", tac->op1->name);
            fprintf(output, "\tmovl $0, %%eax\n");
          break;
          case VAL_TYPE_REAL:
          default:
            fprintf(output, "\tmovss %s(%%rip), %%xmm0\n\tunpcklps	%%xmm0, %%xmm0\n\tcvtps2pd	%%xmm0, %%xmm0\n", tac->op1->name);
            fprintf(output, "\tmovl $1, %%eax\n");
        }
        fprintf(output, "\tmovl $%s, %%edi\n", tac->op2?tac->op2->name:""); // The format
        fprintf(output, "\tcall printf\n");
      }
    break;
    case TAC_READ:
      fprintf(output, "\tmovl $%s, %%esi\n", tac->op1?tac->op1->name:0); // Send address of data parameter
      fprintf(output, "\tmovl $%s, %%edi\n", tac->op2?tac->op2->name:0); // The format
      fprintf(output, "\tmovl $0, %%eax\n");
      fprintf(output, "\tcall __isoc99_scanf\n");
    break;
    case TAC_NOP:
      fprintf(output, "\tnop\n");
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
    default: fprintf(output, "TAC_DEFAULT");
  }
}
