#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <stack>
#include "piece.h"
#include "move.h"
#include "board.h"
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

    bool undo();

    std::vector<Move *> getAllLegalMoves();

    Move *computerSuggestion(int strength);

    void play(Move *);
 
private:

//    AI opponent;
    Board board_;
    std::stack<Move*> movePlayed;

    Move* randomMove();
    Move* greedyMove();

    void maximiseHeuristic(std::vector<Move*> ms,Move** fm);
    void minimiseHeuristic(std::vector<Move*> ms,Move** fm);
};

#endif // GAME_H_
