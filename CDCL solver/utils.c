#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
Stack* empty_stack(){
  Stack* stack = malloc(sizeof(Stack));
  stack->e = NULL;
  stack->next = NULL;
  stack->length = 0;
  return stack;
}

Stack* copy(Stack* stack){ // It's not a recursive copy !!!
  Stack* s2 = empty_stack();
  s2->e = stack->e;
  s2->next = stack->next;
  s2->length = stack->length;
  return s2;
}

void print_stack(Stack* stack){
  Stack* s2 = stack;
  while (s2->next != NULL){
    printf("%d [e: %d,next: %d, length: %d]\n",s2,s2->e,s2->next,s2->length);
    s2 = s2->next;
  }
  printf("-\n");
}

void append(Stack* stack,void* e){
  Stack* pivot = empty_stack();
  pivot->e = stack->e;
  pivot->next = stack->next;
  pivot->length = stack->length;
  stack->e = e;
  stack->next = pivot;
  stack->length = pivot->length+1;
}

void* pop(Stack* stack){
  void* e = stack->e;
  *stack = *(stack->next);
  return e;
}

Stack* create_stack_from_list(void** list,int length){
  Stack* s = empty_stack();
  int i;
  for (i=0;i<length;i++){
    append(s,list[i]);
  }
  return s;
}
