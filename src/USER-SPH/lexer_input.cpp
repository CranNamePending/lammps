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
  
  string input;
  if(narg == 0){
	  input = "5+2";
  }else{
	  for(int i = 0 ; i < narg ; i++){
		  string s(arg[i]);
		  input += s;
	  }
  }
  Formula formula = tokenizer(input);
}

Tree LexerInput::getTree(){
	return tree;
}
