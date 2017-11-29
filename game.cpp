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

Game::Game() { }

void Game::play(Move *m) {
    assert(m != NULL);
    movePlayed.push(m);
    m->perform(&board_);
    board_.switch_player();
}

bool Game::undo() {
    bool b = false;
    if(!movePlayed.empty()){
	Move* m = movePlayed.top();
	movePlayed.pop();
	m->unPerform(&board_);
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
    if(strength==1)
	move = greedyMove();
    return move;
}

/*private*/

Move* Game::randomMove(){
    std::vector<Move*> moves = getAllLegalMoves();
    int choice = rand()%moves.size();
    return moves[choice];
}

Move* Game::greedyMove(){
    std::vector<Move*> moves = getAllLegalMoves();
    Move* finalChoice = randomMove();
    if(board_.getPlayer()==WHITE){
	maximiseHeuristic(moves,&finalChoice);
	    std::cout<<" move : "<<finalChoice<<std::endl;

    }else
	minimiseHeuristic(moves,&finalChoice);
    return finalChoice;
}
/*
Move* Game::minimaxMove(int steps){
    std::vector<Move*> moves = getAllLegalMoves();
    Move* finalChoice = randomMove();
    int k = steps;
    if(k>3)
	k=3;
    if(board_.getPlayer()==WHITE){
	maximiseHeuristic(moves,&finalChoice);
	    std::cout<<" move : "<<finalChoice<<std::endl;

    }else
	minimiseHeuristic(moves,&finalChoice);
    return finalChoice;
}
*/
void Game::maximiseHeuristic(std::vector<Move*> allMoves, Move** finalChoice){
    int valMax = board_.heuristic();
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

void Game::minimiseHeuristic(std::vector<Move*> allMoves, Move** finalChoice){
    int valMin = board_.heuristic();
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
