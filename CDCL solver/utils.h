#ifndef UTILS_H_
#define UTILS_H_

typedef struct Stack Stack;
struct Stack
{
  void* e;
  Stack * next;
  int length;
};

Stack* empty_stack();

void print_stack(Stack*);

void* pop(Stack*);

void append(Stack*,void*);

Stack* create_stack_from_list(void**,int);

#endif // UTILS_H
