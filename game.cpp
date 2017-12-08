#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <cassert>
#include "game.h"
#include "board.h"
#include "global.h"
#include "piece.h"
#include "concretepieces.h"
#include "move.h"

#define MOVE_IN_ADVANCE (2)
#define DEFAULT_PATH ("op.txt")

Game::Game(){
    openings = new Tree(DEFAULT_PATH);
}

void Game::play(Move *m) {
    assert(m != NULL);
    movePlayed.push(m);
    m->perform(&board_);
    if((beginning)&&((openings->allMoves()).size())>0&&(openings->isMoveExist(m->toBasicNotation())))
	openings = openings->playMove(m->toBasicNotation());
    else
	beginning=false;
    board_.switch_player();
}

bool Game::undo() {
    bool b = false;
    if(!movePlayed.empty()){
	Move* m = movePlayed.top();
	movePlayed.pop();
	m->unPerform(&board_);
	if(beginning)
    	    openings = openings->unPlayMove();
	board_.switch_player();
	b = true;
    }
    return b;
}

void Game::display() {
    board_.display();
}

void Game::displayValueHeuristic() {
    board_.displayValueHeuristic();
}

void Game::displayCaptured() {
    board_.displayCaptured();
}

std::vector<Move *> Game::getAllLegalMoves() {
    return board_.getAllLegalMoves();
}


Move *Game::computerSuggestion(int strength) {
    Move* move = randomMove();
    std::string nextStrMove;
    Move* nextMove;
    if(beginning){
    	if(movePlayed.size()>0){
	    nextStrMove = openings->checkKnownMove();
    	}else{
	    nextStrMove = openings->giveARandomMove();
    	}
    }
    if(nextStrMove.size() == 0){
	beginning = false;
	if(strength==1)
	    move = greedyMove();
    	if(strength==2)
	    move = minimaxMove(MOVE_IN_ADVANCE);
    }else{
	std::vector<Move*> curMoves = getAllLegalMoves();
	for(auto x : curMoves){
	    std::string s = x->toBasicNotation();
	    if(s==nextStrMove)
		nextMove = x;
}
	move = nextMove;
    }
    return move;
}

/*private*/

Move* Game::randomMove(){
    std::vector<Move*> moves = getAllLegalMoves();
    srand(time(NULL));
    int choice = rand()%moves.size();
    return moves[choice];
}

Move* Game::greedyMove(){
    std::vector<Move*> moves = getAllLegalMoves();
    Move* finalChoice = randomMove();
    finalChoice->perform(&board_);
    int valADepasser = board_.heuristic();
    finalChoice->unPerform(&board_);
    if(board_.getPlayer()==WHITE)
	maximiseHeuristic(moves,&finalChoice,valADepasser);
    else
	minimiseHeuristic(moves,&finalChoice,valADepasser);
    return finalChoice;
}

Move* Game::minimaxMove(int steps){
    std::vector<Move*> moves = getAllLegalMoves();
    std::vector<Move*> movesF;
    if(moves.size()==0)
	return NULL;
    //Init value of the board

    double valRec;
    int k = steps,i=0,val;
    bool minimise = true;
    srand(time(NULL));
    if(board_.getPlayer()==WHITE)
	minimise = !minimise;
    if(k>3)
	k=3;
    for(Move* mT :moves){
	mT->perform(&board_);
	if(i==0){
	    movesF.push_back(moves[i]);
	    i++;
	    val = recHeuristicMiniMax(getAllLegalMoves(),k-1,!minimise);
	}
	valRec = recHeuristicMiniMax(getAllLegalMoves(),k-1,!minimise);
	mT->unPerform(&board_);
	if(minimise){
	    if(valRec<val){
		val = valRec;
		movesF.clear();
		movesF.push_back(mT);
	    }else if(valRec == val)
		movesF.push_back(mT);
	}else{
	    if(valRec>val){
		val = valRec;
		movesF.clear();
		movesF.push_back(mT);
	    }else if(valRec == val)
		movesF.push_back(mT);
	}
    }
    return movesF[rand()%movesF.size()];
}

void Game::maximiseHeuristic(std::vector<Move*> allMoves, Move** finalChoice,int val){
    int valMax = val;
    for(Move* mTemp : allMoves){
	mTemp->perform(&board_);
	int currentScore = board_.heuristic();
	if(valMax < currentScore){
	    valMax = currentScore;
	    *finalChoice = mTemp;
	}
	mTemp->unPerform(&board_);
    }
}

void Game::minimiseHeuristic(std::vector<Move*> allMoves, Move** finalChoice,int val){
    int valMin = val;
    for(Move* mTemp : allMoves){
	mTemp->perform(&board_);
	int currentScore = board_.heuristic();
	if(valMin > currentScore){
	    valMin = currentScore;
	    *finalChoice = mTemp;
	}
	mTemp->unPerform(&board_);
    }
}

int Game::recHeuristicMiniMax(std::vector<Move*> moveStepI,int stepRemaining, bool minimiseHeuristic){
    int valRec;
    if(moveStepI.size() ==0||stepRemaining==0)
	return board_.heuristic();
    int bestVal,i=0;
    for(Move* mT : moveStepI){
        mT->perform(&board_);
	if(i==0){
	    i++;
	    bestVal = recHeuristicMiniMax(board_.getAllLegalMoves(),stepRemaining-1,!minimiseHeuristic);
	}else{
	    valRec = recHeuristicMiniMax(board_.getAllLegalMoves(),stepRemaining-1,!minimiseHeuristic);
	    if(minimiseHeuristic){
	        if(valRec<bestVal)
		    bestVal = valRec;
	    }else{
	        if(valRec>bestVal)
		    bestVal = valRec;
	    }
	}
	mT->unPerform(&board_);
    }
    return bestVal;
}
