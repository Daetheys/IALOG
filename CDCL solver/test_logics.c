#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "logics.h"

//Var
int test_create_var(){
  Var* v = create_var("A");
  assert(v->name=="A");
  assert(v->val==-1);
  return 0;
}

//Literal
int test_create_literal(){
  Var* v = create_var("v1");
  v->val = -1;
  Literal* l = create_literal(v);
  assert(((Var*)(l->var))->name=="v1");
  assert(((Var*)(l->var))->val==-1);
  assert(l->type==0);
  return 0;
}

int test_evaluate_literal(){
  Var* v = create_var("v1");
  v->val = -1;
  Literal* l = create_literal(v);
  l->type = 0;
  assert(evaluate_literal(l)==-1);
  l->type = 1;
  assert(evaluate_literal(l)==-1);
  v->val = 0;
  assert(evaluate_literal(l)==1);
  v->val = 1;
  assert(evaluate_literal(l)==0);
  l->type = 0;
  assert(evaluate_literal(l)==1);
  v->val = 0;
  assert(evaluate_literal(l)==0);
  return 0;
}

int test_val_to_true(){
  Var* v = create_var("v1");
  Literal* l = create_literal(v);
  l->type = 0;
  assert(val_to_true(l)==1);
  l->type =1;
  assert(val_to_true(l)==0);
  return 0;
}

//Clause
int test_create_clause(){
  Clause* c = create_clause();
  assert(((Literal*)(c->literals->e)) == NULL);
  assert(c->literals->next == NULL);
  assert(c->literals->length == 0);
  return 0;
}

int test_create_clause_from_list(){
  Var* v1 = create_var("v1");
  v1->val = 1;
  Var* v2 = create_var("v2");
  v2->val = 0;
  Var* v3 = create_var("v3");
  v3->val = -1;
  Literal* l1 = create_literal(v1);
  Literal* l2 = create_literal(v2);
  Literal* l3 = create_literal(v3);
  Literal* l[3];
  l[0] = l1;
  l[1] = l2;
  l[2] = l3;
  Clause* c = create_clause_from_list(l,3);
  assert(((Var*)((Literal*)(c->literals->e))->var)->val == -1);
  assert(((Var*)((Literal*)(c->literals->next->e))->var)->val == 0);
  assert(((Var*)((Literal*)(c->literals->next->next->e))->var)->val == 1);
  return 0;
}

int test_get_variable_from_clause(){
  Var* v1 = create_var("v1");
  v1->val = 1;
  Var* v2 = create_var("v2");
  v2->val = -1;
  Var* v3 = create_var("v3");
  v3->val = -1;
  Literal* l1 = create_literal(v1);
  Literal* l2 = create_literal(v2);
  Literal* l3 = create_literal(v3);
  Literal* l[3];
  l[0] = l1;
  l[1] = l2;
  l[2] = l3;
  Clause* c = create_clause_from_list(l,3);
  void** ret = get_variable_from_clause(c);
  assert((Literal*)ret[0] == l3);
  assert((int)ret[1] == 2);
  assert((int)ret[2] == 1);
  return 0;
}

int test_evaluate_clause(){
  Var* v1 = create_var("v1");
  v1->val = 1;
  Var* v2 = create_var("v2");
  v2->val = -1;
  Var* v3 = create_var("v3");
  v3->val = -1;
  Literal* l1 = create_literal(v1);
  Literal* l2 = create_literal(v2);
  Literal* l3 = create_literal(v3);
  Literal* l[3];
  l[0] = l1;
  l[1] = l2;
  l[2] = l3;
  Clause* c = create_clause_from_list(l,3);
  assert(evaluate_clause(c)==1);
  v1->val = 0;
  v2->val = 0;
  v3->val = 0;
  assert(evaluate_clause(c)==0);
  v1->val = 1;
  v2->val = 0;
  v3->val = 0;
  assert(evaluate_clause(c)==1);
  l2->type = 1;
  l3->type = 1;
  assert(evaluate_clause(c)==1);
  l1->type = 1;
  l2->type = 0;
  l3->type = 0;
  assert(evaluate_clause(c)==0);
  v1->val = -1;
  assert(evaluate_clause(c)==-1);
  return 0;
}

//Logics
int test_create_logics(){
  Logics* l = create_logics();
  assert(l->clauses->next==NULL);
  return 0;
}

int test_create_logics_from_list(){
  Var* v1 = create_var("v1");
  v1->val = 1;
  Var* v2 = create_var("v2");
  v2->val = 0;
  Var* v3 = create_var("v3");
  v3->val = -1;
  Literal* l1 = create_literal(v1);
  Literal* l2 = create_literal(v2);
  Literal* l3 = create_literal(v3);
  Literal* lc1[1];
  lc1[0] = l3;
  Literal* lc2[2];
  lc2[0] = l2;
  lc2[1] = l1;
  Clause* c1 = create_clause_from_list(lc1,1);
  Clause* c2 = create_clause_from_list(lc2,2);
  Clause* ll[2];
  ll[0] = c1;
  ll[1] = c2;
  Logics* l = create_logics_from_list(ll,2);
  assert(((Var*)(((Literal*)(((Clause*)(l->clauses->e))->literals->e))->var))->val==1);
  assert(((Var*)(((Literal*)(((Clause*)(l->clauses->e))->literals->next->e))->var))->val==0);
  assert(((Var*)(((Literal*)(((Clause*)(l->clauses->next->e))->literals->e))->var))->val==-1);
  return 0;
}

int main(int argc,char** argv){
  test_create_var();
  test_create_literal();
  test_evaluate_literal();
  test_val_to_true();
  test_create_clause();
  test_create_clause_from_list();
  test_get_variable_from_clause();
  test_evaluate_clause();
  test_create_logics();
  test_create_logics_from_list();
  printf("\033[1;32m"); //Green color
  printf("test_logics - PASSED\n");
  printf("\033[0m");
  return 0;
}
