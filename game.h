#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <stack>
#include "piece.h"
#include "move.h"
#include "board.h"
#include "tree.h"

//#include "artificialIntelligence.h"
// This class defines a game as seen by the 'main' module. It has the following
// roles:
// 1. It is a wrapper to a Board object 
// 2. It maintains the history of the game
// 3. It implements a computer opponent

class Game {
public:
    Game();

    void display();

    void displayValueHeuristic();

//show pieces captured by each player
    void displayCaptured();

//Put the board into the previous state
    bool undo();

    std::vector<Move *> getAllLegalMoves();

//Compute a move. The level of the AI depending on "strength" given. 
    Move *computerSuggestion(int strength);

    void play(Move *);
 
private:

    Board board_;
//Store all moves played to allow to undo them. 
    std::stack<Move*> movePlayed;
//This tree is used to play known openning
    Tree* openings;
//boolean for know if it's possible to use the tree opennings
    bool beginning = true;

//Two differents levels of AI (0 and 1)
    Move* randomMove();
    Move* greedyMove();

//method used for the greedy choice
    void maximiseHeuristic(std::vector<Move*> ms,Move** fm, int boardScore);
    void minimiseHeuristic(std::vector<Move*> ms,Move** fm, int boardScore);

//method used for the minimax algorithm (AI lvl2)
    Move* minimaxMove(int steps);
    int recHeuristicMiniMax(std::vector<Move*> msI,int sR, bool mini);
};

#endif // GAME_H_
