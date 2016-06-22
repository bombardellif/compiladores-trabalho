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
    				fprintf(output, "\tmovl \t%s(%%rip), %%edx\n",tac->op1->text);
    				fprintf(output, "\tmovl \t%s(%%rip), %%eax\n",tac->op2->text);
    				fprintf(output, "\taddl \t%%edx, %%eax\n");
    break;
    case TAC_SUB: 
            fprintf(output, "\tmovl \t%s(%%rip), %%edx\n",tac->op1->text);
    				fprintf(output, "\tmovl \t%s(%%rip), %%eax\n",tac->op2->text);
    				fprintf(output, "\tsubl \t%%edx, %%eax\n");
    break;
    case TAC_MUL:
            fprintf(output, "\tmovl \t%s(%%rip), %%edx\n",tac->op1->text);
    				fprintf(output, "\tmovl \t%s(%%rip), %%eax\n",tac->op2->text);
    				fprintf(output, "\timull \t%%edx, %%eax\n");
    break;
    case TAC_DIV: 
            fprintf(output, "\tmovl \t%s(%%rip), %%edx\n",tac->op1->text);
    				fprintf(output, "\tmovl \t%s(%%rip), %%eax\n",tac->op2->text);
    				fprintf(output, "\tidivl \t%%edx, %%eax\n");
    break;
    case TAC_LABEL:
                        fprintf(output, ".%s:\n", tac->res->text);
    break;
    case TAC_IFZ: 
                fprintf(output, ".%s\n", tac->res->text);
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
            fprintf(output, "\tmovl\t%s(%%rip), %%esi\n", tac->op1->name);
            fprintf(output, "\tmovl\t$0, %%eax\n");
          break;
          case VAL_TYPE_STRING:
            fprintf(output, "\tmovl\t$%s, %%esi\n", tac->op1->name);
            fprintf(output, "\tmovl\t$0, %%eax\n");
          break;
          case VAL_TYPE_REAL:
          default:
            fprintf(output, "\tmovss\t%s(%%rip), %%xmm0\n\tunpcklps	%%xmm0, %%xmm0\n\tcvtps2pd	%%xmm0, %%xmm0\n", tac->op1->name);
            fprintf(output, "\tmovl\t$1, %%eax\n");
        }
        fprintf(output, "\tmovl\t$%s, %%edi\n", tac->op2?tac->op2->name:""); // The format
        fprintf(output, "\tcall\tprintf\n");
      }
    break;
    case TAC_READ:
      fprintf(output, "\tmovl\t$%s, %%esi\n", tac->op1?tac->op1->name:""); // Send address of data parameter
      fprintf(output, "\tmovl\t$%s, %%edi\n", tac->op2?tac->op2->name:""); // The format
      fprintf(output, "\tmovl\t$0, %%eax\n");
      fprintf(output, "\tcall\t__isoc99_scanf\n");
    break;
    case TAC_NOP:
      fprintf(output, "\tnop\n");
    break;
    case TAC_ANEG: fprintf(output, "TAC_ANEG");
    break;
    case TAC_LTZ: 
                fprintf(output, "\tcmpl\t$0, -4(%%rbp)\n");
                fprintf(output, "\tjnge\t");
    break;
    case TAC_GTZ: 
                fprintf(output, "\tcmpl\t$0, -4(%%rbp)\n");
                fprintf(output, "\tjnle\t");
    break;
    case TAC_LEZ: 
                fprintf(output, "\tcmpl\t$0, -4(%%rbp)\n");
                fprintf(output, "\tjg\t");
    break;
    case TAC_GEZ: 
                fprintf(output, "\tcmpl\t$0, -4(%%rbp)\n");
                fprintf(output, "\t jge\t");
    break;
    case TAC_AND: fprintf(output, "TAC_AND");
    break;
    case TAC_OR: fprintf(output, "TAC_OR");
    break;
    case TAC_EQZ: 
                fprintf(output, "\tcmpl\t$0, -4(%%rbp)\n");
                fprintf(output, "\tjne\t");
    break;
    default: fprintf(output, "TAC_DEFAULT");
  }
}
