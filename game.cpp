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
    m->perform(&board_);
    board_.switch_player();
}

bool Game::undo() {
    std::cout << "not yet implemented" << std::endl;
    return false;
}

void Game::display() {
    board_.display();
}

std::vector<Move *> Game::getAllLegalMoves() {
    return board_.getAllLegalMoves();
}


Move *Game::computerSuggestion(int strength) {
    std::cout << "not yet implemented" << std::endl;
    return NULL;
}