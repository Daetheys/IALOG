#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "logics.h"
#include "parser.h"
#define MAXLENGTH 1024
#define DEBUG 0

void debug(char* txt){
  if (DEBUG){
    printf("%s\n",txt);
  }
}

Literal* parse_char(char* c,Var** vars){
  debug("      parse char");
  int type =0;
  if (c[0] == '-'){
    type = 1;
    c++;
  }
  int index = atoi(c);
  Literal* lit = create_literal(vars[index-1]);
  lit->type = type;
  debug("      parsed char");
  return lit;
}

Clause* parse_line(char* line,Var** vars){
  debug("   Parse line");
  Clause* c = create_clause();
  char delim[] = " ";
  char* ptr = strtok(line,delim);
  while ((strcmp(ptr,"0") && strcmp(ptr,"0\n"))){
    debug("   loop parse char");
    Literal* lit = parse_char(strdup(ptr),vars);
    append(c->literals,lit);
    ptr = strtok(NULL,delim);
  }
  debug("   parsed line");
  return c;
}

Logics* parse_file(char* file){
  debug("Called Parser");
  Logics* l = create_logics();
  Var** vars = NULL;
  FILE* f;
  f = fopen(file,"r");
  debug("Opened file");
  if (f){
    char* r = malloc(sizeof(char)*MAXLENGTH);
    while (fgets(r,MAXLENGTH,f)){
      if (r[0] == 'c'){
	//Commentary
	debug("Commentary");
      } else {
	debug("Creation of vars");
	//Creation of vars
	if (r[0] == 'p'){
	  char delim[] =" ";
	  char* ptr = strtok(r,delim);
	  ptr = strtok(NULL,delim); //"cnf"
	  ptr = strtok(NULL,delim); //what we want
	  int nb = atoi(ptr);
	  //Creation of vars
	  int i;
	  vars = malloc(sizeof(Var*)*nb);
	  for (i=0;i<nb;i++){
	    char* name_var = malloc(10*sizeof(char)); //We assume we won't need 10 digits to write a number
	    sprintf(name_var,"%d",i+1);
	    vars[i] = create_var(name_var);
	  }
	} else {
	  debug("Parsing");
	  //Parses and adds a new Clause
	  Clause* c = parse_line(r,vars);
	  append(l->clauses,c);
	}
      }
    }
  } else {
    printf("Unable to open file %s\n",file);
  }
  fclose(f);
  return l;
}
