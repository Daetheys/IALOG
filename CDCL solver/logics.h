#include "utils.h"

//Vars
typedef struct Var Var;
struct Var
{
  char* name; //To debug
  int val; // -1 : Undecided / 0 : False / 1 : True
  int decide;
};

Var* create_var(char*);

void print_var(Var*);

//Literals
typedef struct Literal Literal;
struct Literal
{
  Var* var;
  int type;
};

Literal* create_literal(Var*);

void print_literal(Literal*);

int evaluate_literal(Literal*);

int val_to_true(Literal*); //returns the val of the var so that the literal is true

//Clause
typedef struct Clause Clause;
struct Clause
{
  Stack* literals; //List of Var*
};

Clause* create_clause();

void print_clause(Clause*);

Clause* create_clause_from_list(Literal**,int);

void** get_variable_from_clause(Clause*); //Returns an array [var,count] with count the number of undecided Var in Clause and var an undecided Var if count>0

int evaluate_clause(Clause*);

//Logics
typedef struct Logics Logics;
struct Logics
{
  Stack* clauses; // List of Clause
};

Logics* create_logics();

void print_logics(Logics*);

Logics* create_logics_from_list();
