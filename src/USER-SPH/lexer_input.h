
#ifdef COMMAND_CLASS

CommandStyle(lexer_input,LexerInput)

#else

#ifndef LMP_LEXER_IN_H
#define LMP_LEXER_IN_H

#include "Tree.h"
#include "pointers.h"

namespace LAMMPS_NS {

class LexerInput : protected Pointers {
 public:
  LexerInput(class LAMMPS *);
  void command(int, char **);
  Tree getTree();
 private:
  int me,nprocs;
  Tree tree;
};

}

#endif
#endif