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
    std::cout << "not yet implemented" << std::endl;
    return NULL;
}
