#include "logics.h"
#include "utils.h"

Literal* get_literal(Logics*);
int deduce(Logics*,Stack*);
int backtrack(Stack*);
void print_var_stack(Stack*);
Stack* cdcl(Logics*);
