#include "logics.h"
#include <stdlib.h>
#include <stdio.h>
#define DEBUG 0

void print(char* s){
  if (DEBUG){
    printf("%s\n",s);
  }
}

Literal* get_literal(Logics* l){
  Stack* s = l->clauses;
  while (s->next != NULL){
    void** ret = get_variable_from_clause(s->e);
    Literal* lit = (Literal*)ret[0];
    int count_undecided = (int)ret[1];
    int count_true = (int)ret[2];
    if (count_true==0 && count_undecided > 0){
      return lit;
    }
    s = s->next;
  }
  return NULL; //Computation ended
}

int deduce(Logics* l,Stack* s){ //Try to find values of new variables by propagation and conflicts
  Stack* s2 = l->clauses;
  while (s2->next != NULL){
    Clause* c = s2->e;
    void** ret = get_variable_from_clause(c);
    Literal* lit = (Literal*)ret[0];
    int count_undecided = (int)ret[1];
    int count_true = (int)ret[2];
    if (count_undecided == 1 && count_true == 0){ //If all are false and one undecided -> set it to true
      Var* v = (Var*)(lit->var);
      v->val = val_to_true(lit);
      append(s,v);
    } else {
      if (evaluate_clause(c) == 0){
	return 1; //Conflict
      }
    }
    s2 = s2->next;
  }
  return 0;
}

int backtrack(Stack* s){
  while (s->next != NULL){
    Var* v = pop(s);
    if (v->decide){
      v->val = 1-v->val;
      append(s,v);
      return 0;
    }
    v->val = -1;
  }
  return 0; //Cannot backtrack more -> Unsatisfiable
}

int step_deduce(Logics* l,Stack* s){
  print("_START DEDUCE_");
  while (1){
    print("LOOP DEDUCE");
    int ret = deduce(l,s);
    if (ret){
      print("CONFLICT FOUND - BACKTRACK");
      int ret2 = backtrack(s); //Conflict
      if (ret2 == 0){
	print("CANNOT BACKTRACK MORE");
	return 1; //Cannot backtrack more -> Unsatisfiable
      }
    } else {
      print("NO CONFLICT");
      break;
    }
  }
  return 0;
}

Stack* cdcl(Logics* l){ //Returns the valuation in a Stack or a NULL pointer if not satisfiable
  Stack* s = empty_stack(); //Stack for variables
  print("_____CDCL_____");
  if (DEBUG){
    print_logics(l);
  }
  step_deduce(l,s); //Handles unitary clauses
  while (1){
    print("--loop step");
    if (DEBUG){
      print_logics(l);
    }
    Literal* lit = get_literal(l);
    if (lit == NULL){
      print("FINISHED THE CDCL");
      return s; //Finished the cdcl -> All variables are defined without conflicts -> Satisfiable
    } else {
      Var* v = lit->var;
      print("Choose variable");
      if (DEBUG){
	printf("%s %d %d\n",v->name,v->val,v->decide);
      }
      v->val = 1-val_to_true(lit); //Arbitrary choice
      v->decide = 1;
      if (DEBUG){
	printf("%s %d %d\n",v->name,v->val,v->decide);
      }
      append(s,v);
      int ret = step_deduce(l,s); //deduce and backtracks if necessary
      if (ret){
	return NULL; //Unsatifiable
      }
    }
  }
}
