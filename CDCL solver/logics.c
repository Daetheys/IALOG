#include <stdlib.h>
#include <stdio.h>
#include "logics.h"
#include "utils.h"

//Variables
Var* create_var(char* name){
  Var* v = malloc(sizeof(Var));
  v->name = name;
  v->val = -1;
  v->decide = 0;
  return v;
}

void print_var(Var* v){
  printf("VAR(%d Var(%s %d))",v,v->name,v->val);
}

//Literal
Literal* create_literal(Var* v){
  Literal* l = malloc(sizeof(Literal));
  l->var = v;
  l->type = 0;
  return l;
}

void print_literal(Literal* l){
  printf("LITERAL(%d var:");
  print_var(l->var);
  printf(" type: %d",l->type);
}

int evaluate_literal(Literal* l){
  int val = ((Var*)(l->var))->val;
  if (val==-1){
    return -1;
  } else {
    if (l->type){
      return 1-val;
    } else {
      return val;
    }
  }
}

int val_to_true(Literal* l){
  return 1-(l->type);
}

//Clauses
Clause* create_clause(){
  Clause* c = malloc(sizeof(Clause));
  c->literals = empty_stack();
  return c;
}

void print_clause(Clause* c){
  Stack* s = c->literals;
  printf("CLAUSE(%d\n");
  while (s->next != NULL){
    printf("[e:",s);
    print_literal(s->e);
    printf(",next : %d, length: %d)\n",s->next,s->length);
    s = s->next;
  }
  printf("\n");
}

Clause* create_clause_from_list(Literal** l,int length){
  Stack* s = create_stack_from_list((void**)l,length);
  Clause* c = create_clause();
  c->literals = s;
  return c;
}

void** get_variable_from_clause(Clause* c){
  Stack* s = c->literals;
  int count_undecided = 0;
  int count_true = 0;
  Literal* literal;
  while (s->next != NULL){
    int eval = evaluate_literal(((Literal*)(s->e)));
    if (eval == -1){ //Find an undecided variable
      if (count_undecided==0){ //Find the first one -> limits assignments of too many variables
	literal = s->e;
      }
      count_undecided++; //Count the number of undecided
    } else {
      if (eval == 1){ //Count the number of true literals
	count_true++;
      }
    }
    s = s->next;
  }
  //Returns those 3 informations
  void** ret = malloc(sizeof(Literal*)+2*sizeof(int*));
  ret[0] = literal;
  ret[1] = count_undecided;
  ret[2] = count_true;
  return ret;
}

int evaluate_clause(Clause* c){
  Stack* s = c->literals;
  int undecided = 0;
  while (s->next != NULL){
    int val = evaluate_literal(((Literal*)(s->e)));
    if (val==1){
      return 1;
    } else {
      if (val == -1){
	undecided = 1;
      }
    }
    s=s->next;
  }
  return -undecided;
  }

//Logics
Logics* create_logics(){
  Logics* l = malloc(sizeof(Logics));
  l->clauses = empty_stack();
  return l;
}

void print_logics(Logics* l){
  Stack* s = l->clauses;
  printf("LOGICS(%d\n");
  while (s->next != NULL){
    printf("[e:\n",s);
    print_clause(s->e);
    printf(",next : %d, length: %d)\n",s->next,s->length);
    s = s->next;
  }
  printf("\n");
}

Logics* create_logics_from_list(Clause** lc,int length){
  Stack* s = create_stack_from_list((void**)lc,length);
  Logics* l = create_logics();
  l->clauses = s;
  return l;
}
