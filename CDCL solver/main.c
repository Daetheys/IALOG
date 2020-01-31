#include <stdio.h>
#include <stdlib.h>
#include "printer.h"

int main(int argc, char** argv){ //Call the program like ./main input_file output_file
  printf("running main\n");
  Logics* l = parse_file(argv[1]);
  print_logics(l);
  Stack* s = cdcl(l);
  if (s==NULL){
    printf("no solution\n");
  } else {
    printf("solution printed in %s\n",argv[2]);
    print_valuation(s,argv[2]);
  }
  return 0;
}
