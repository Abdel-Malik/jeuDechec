#ifndef ARTIFICIALINTELLIGENCE_H
#define ARTIFICIALINTELLIGENCE_H
#include "move.h"

class AI{
 public:

 Move* aiMove(int strength);

 private:
 Move* randomMove();
 Move* greedyMove();

};
#endif
