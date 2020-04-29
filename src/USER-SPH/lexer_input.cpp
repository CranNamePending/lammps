#include <string>

#include "lexer_input.h"
#include "Lexer.h"

using namespace LAMMPS_NS;

/*--- Constructor ---*/
LexerInput::LexerInput(LAMMPS *lmp) : Pointers(lmp) {}
/*---             ---*/

void LexerInput::command(int narg, char **arg){
  MPI_Comm_rank(world,&me);
  MPI_Comm_size(world,&nprocs);
  
  string input = "(";
  if(narg == 0){
	  input = "5+2";
  }else{
	  for(int i = 0 ; i < narg ; i++){
		  string s(arg[i]);
		  input += s;
	  }
  }
  input += ")";
  printf("Input: %s\n", input.c_str());
  Formula formula = tokenizer(input);
  for(Token token : formula.tokens){
	  printf("Token: %d\n", (int)token);
  }
  
  Tree t(formula);
  t.printTree();
  tree = t;
  printf("Output if T = 20: %f\n", t.getOutput(0, 20.0));
}

Tree LexerInput::getTree(){
	return tree;
}
