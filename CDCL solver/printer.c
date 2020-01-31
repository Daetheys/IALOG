#include "printer.h"
#include <stdio.h>
#include <stdlib.h>

void print_valuation(Stack* s,char* out){
  Stack* s2 = s;
  FILE* f;
  f = fopen(out,"w");
  if (f == NULL){
    printf("Cannot open output file");
    exit(1);
  }
  fprintf(f,"SAT\n");
  while (s2->next != NULL){
    Var* var = (Var*)(s2->e);
    if (!var->val){
      fprintf(f,"-");
    }
    fprintf(f,"%s ",var->name);
    s2 = s2->next;
  }
  fprintf(f,"0");
  fclose(f);
}
