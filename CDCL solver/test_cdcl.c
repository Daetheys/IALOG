#include "cdcl.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Logics* create_logics1(){
  Var* v1 = create_var("v1");
  v1->val = -1;
  Var* v2 = create_var("v2");
  v2->val = -1;
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
  return l;
}

Logics* create_logics2(){
  Var* v1 = create_var("v1");
  v1->val = -1;
  Var* v2 = create_var("v2");
  v2->val = -1;
  Var* v3 = create_var("v3");
  v3->val = -1;
  Literal* l1 = create_literal(v1);
  Literal* l2 = create_literal(v2);
  Literal* l3 = create_literal(v3);
  Literal* l10 = create_literal(v1);
  Literal* l20 = create_literal(v2);
  Literal* l30 = create_literal(v3);
  l10->type = 1;
  l20->type = 1;
  l30->type = 1;
  Literal* lc1[3];
  lc1[0] = l3;
  lc1[1] = l20;
  lc1[2] = l10;
  Literal* lc2[3];
  lc2[0] = l2;
  lc2[1] = l1;
  lc2[2] = l30;
  Clause* c1 = create_clause_from_list(lc1,3);
  Clause* c2 = create_clause_from_list(lc2,3);
  Clause* ll[2];
  ll[0] = c1;
  ll[1] = c2;
  Logics* l = create_logics_from_list(ll,2);
  return l;
}

Logics* create_logics3(){
  Var* v1 = create_var("v1");
  v1->val = -1;
  Var* v2 = create_var("v2");
  v2->val = -1;
  Var* v3 = create_var("v3");
  v3->val = -1;
  Literal* l1 = create_literal(v1);
  Literal* l2 = create_literal(v2);
  Literal* l3 = create_literal(v3);
  Literal* l10 = create_literal(v1);
  Literal* l20 = create_literal(v2);
  Literal* l30 = create_literal(v3);
  l10->type = 1;
  l20->type = 1;
  l30->type = 1;
  Literal* lc1[1];
  lc1[0] = l3;
  Literal* lc2[1];
  lc2[0] = l30;
  Clause* c1 = create_clause_from_list(lc1,1);
  Clause* c2 = create_clause_from_list(lc2,1);
  Clause* ll[2];
  ll[0] = c1;
  ll[1] = c2;
  Logics* l = create_logics_from_list(ll,2);
  return l;
}

int test_get_literal(){
  Logics* l = create_logics1();
  Literal* l1 = get_literal(l);
  Var* v1 = l1->var;
  assert(v1->name=="v1");
  v1->val = 1;
  Literal* l2 = get_literal(l);
  Var* v2 = l2->var;
  assert(v2->name=="v3");
  v2->val = -1;
  Literal* l22 = get_literal(l);
  Var* v22 = l22->var;
  assert(v22->name=="v3");
  v22->val = 0;
  Literal* lnull = get_literal(l);
  assert(lnull == NULL);
  return 0;
}

int test_deduce1(){ //standard
  Var* v1 = create_var("v1");
  v1->val = -1;
  Var* v2 = create_var("v2");
  v2->val = -1;
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
  Literal* lit = get_literal(l);
  Var* v = lit->var;
  v->val = 0;
  Stack* s = empty_stack();
  append(s,v);
  int ret = deduce(l,s);
  assert(ret==0);
  assert(v2->val==1);
  return 0;
}

int test_deduce2(){ //conflict
  Var* v1 = create_var("v1");
  v1->val = -1;
  Var* v2 = create_var("v2");
  v2->val = -1;
  Var* v3 = create_var("v3");
  v3->val = -1;
  Literal* l1 = create_literal(v1);
  Literal* l2 = create_literal(v2);
  Literal* l22 = create_literal(v2);
  l22->type = 1;
  Literal* lc1[2];
  lc1[0] = l22;
  lc1[1] = l1;
  Literal* lc2[2];
  lc2[0] = l2;
  lc2[1] = l1;
  Clause* c1 = create_clause_from_list(lc1,1);
  Clause* c2 = create_clause_from_list(lc2,2);
  Clause* ll[2];
  ll[0] = c1;
  ll[1] = c2;
  Logics* l = create_logics_from_list(ll,2);
  Literal* lit = get_literal(l);
  Var* v = lit->var;
  v->val = 0;
  Stack* s = empty_stack();
  append(s,v);
  int ret = deduce(l,s);
  assert(ret==1);
  return 0;
}

int test_backtrack(){
  Stack* s = empty_stack();
  Var* v1 = create_var("v1");
  Var* v2 = create_var("v2");
  Var* v3 = create_var("v3");
  Var* v4 = create_var("v4");
  Var* v5 = create_var("v5");
  v1->decide = 1;
  v3->decide = 1;
  append(s,v1);
  append(s,v2);
  append(s,v3);
  append(s,v4);
  append(s,v5);
  backtrack(s);
  Var* vb = pop(s);
  assert(vb->decide==1);
  assert(vb->name=="v3");
  return 0;
}

int test_cdcl1(){
  Logics* l = create_logics1();
  assert(cdcl(l)==1);
  return 0;
}

int test_cdcl2(){
  Logics* l = create_logics2();
  assert(cdcl(l)==1);
  return 0;
}

int test_cdcl3(){
  Logics* l = create_logics3();
  assert(cdcl(l)==0);
  return 0;
}

int main(int argc,char** argv){
  test_get_literal();
  test_deduce1();
  test_deduce2();
  test_backtrack();
  test_cdcl1();
  test_cdcl2();
  test_cdcl3();
  printf("\033[1;32m"); //Green color
  printf("test_cdcl - PASSED\n");
  printf("\033[0m");
  return 0;
}
