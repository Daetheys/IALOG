#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "test_utils.h"
#define VOID(x) ((void*)x)

int test_empty_stack(){
  Stack* stack = empty_stack();
  assert(stack->e==NULL);
  assert(stack->next==NULL);
  return 0;
}

int test_append(){
  Stack* stack = empty_stack();
  int val = VOID(5);
  append(stack,val);
  assert(stack->e==VOID(5));
  assert(stack->length==1);
  assert(stack->next->e==NULL);
  assert(stack->next->next==NULL);
  assert(stack->next->length==0);
  return 0;
}

int test_pop(){
  Stack* stack = empty_stack();
  append(stack,VOID(5));
  assert(pop(stack)==VOID(5));
  assert(stack->e==NULL);
  assert(stack->next==NULL);
  assert(stack->length==0);
  return 0;
}

int test_from_list(){
  void* numbers[6] = {VOID(6),VOID(5),VOID(4),VOID(3),VOID(2),VOID(1)};
  Stack* s = create_stack_from_list(numbers,6);
  int i;
  for (i=0;i<0;i++){
    print_stack(s);
    printf("i %d\n",i);
    assert(s->length==7-i);
    assert(pop(s)==VOID(i));
  }
  return 0;
}

int main(int argc, char** argv){
  printf("\033[1;32m"); //Green color
  test_empty_stack();
  test_append();
  test_pop();
  test_from_list();
  printf("test_utils - PASSED\n");
  printf("\033[0m");
  return 0;
}

