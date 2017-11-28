#include <cassert>
#include <climits>
#include "concretepieces.h"
#include "global.h"
#include "board.h"
#include "move.h"

/*Pawn class implementation*/

Pawn::Pawn(Position pos, Color color) : Piece(pos,color,1) {}

void Pawn::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Color color = getColor();
    Position pos = getPosition(); 
    int di = 0;
    int dj = 0;
    int max = 0;

    if (color == WHITE) {
        std::vector<Position> rel = {{1,1},{1,-1}};
        g.filter(pos, rel, color, true, poss);
        di = 1;
        max = (pos.first == 1)?2:1;
    } else {
        std::vector<Position> rel = {{-1,1},{-1,-1}};
        g.filter(pos, rel, color, true, poss);
        di = -1;
        max = (pos.first == 6)?2:1;
    }
    g.reachablePositionsAlongStraightLine(pos, di, dj, max, color, false, poss);
    positionsToMoves(g, pos, poss, res);
}

char Pawn::notation() const {
    return ' ';
}

char Pawn::toChar() const {
    return getColor()?'P':'p';
}


/*Rook class implementation*/

Rook::Rook(Position pos, Color color) : Piece(pos, color,5) {}

void Rook::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Position pos = getPosition(); 
    int di[] = {-1, 0, 1, 0};
    int dj[] = {0, 1, 0, -1}; 
    int max = 8;
    for (int i = 0; i < 4; i++) {
        g.reachablePositionsAlongStraightLine(pos, di[i], dj[i], max, getColor(), true, poss);
    }
    positionsToMoves(g, pos, poss, res);
}

char Rook::toChar() const {
    return (getColor())?'R':'r';
}

char Rook::notation() const {
    return 'R';
}

/*Knight class implementation*/
Knight::Knight(Position pos, Color color) : Piece(pos, color,3){}


void Knight::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Position pos = getPosition(); 
    int di[] = {-2, -2, 2, 2, -1, 1, -1, 1};
    int dj[] = {-1, 1, -1, 1, -2, -2, 2, 2};
    int max = 1;
    for (int i = 0; i < 8; i++) {
        g.reachablePositionsAlongStraightLine(pos, di[i], dj[i], max, getColor(), true, poss);
    }
    positionsToMoves(g, pos, poss, res);
}

char Knight::toChar() const {
    return (getColor())?'N':'n';
}

char Knight::notation() const {
    return 'N';
}

/*Bishop class implementation*/
Bishop::Bishop(Position pos, Color color) : Piece(pos,color,3){}

void Bishop::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Position pos = getPosition();
    int di[] = {-1, 1, 1, -1};
    int dj[] = {-1, 1, -1, 1};
    int max = 8;
    for (int i = 0; i < 4; i++) {
        g.reachablePositionsAlongStraightLine(pos, di[i], dj[i], max, getColor(), true, poss);
    }
    positionsToMoves(g, pos, poss, res);
}

char Bishop::toChar() const {
    return (getColor())?'B':'b';
}

char Bishop::notation() const {
    return 'B';
}

/*King class implementation*/

King::King(Position pos, Color color) : Piece(pos,color,INT_MAX){}

void King::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Position pos = getPosition(); 
    int di[] = {-1, 1, 1, -1,-1,0,1,0};
    int dj[] = {-1, 1, -1, 1,0,-1,0,1}; 
    int max = 1;
    for (int i = 0; i < 8; i++) {
        g.reachablePositionsAlongStraightLine(pos, di[i], dj[i], max,  getColor(), true, poss);
    }
    positionsToMoves(g, pos, poss, res);
}

char King::toChar() const {
    return (getColor())?'K':'k';
}

char King::notation() const {
    return 'K';
}

/*Queen class implementation*/

Queen::Queen(Position pos, Color color) : Piece(pos,color,10){}

void Queen::getMoves(const Board &g, std::vector<Move *> &res) const {
    std::vector<Position> poss;
    Position pos = getPosition(); 
    int di[] = {-1, 1, 1, -1,-1,0,1,0};
    int dj[] = {-1, 1, -1, 1,0,-1,0,1}; 
    int max = 8;
    for (int i = 0; i < 8; i++) {
        g.reachablePositionsAlongStraightLine(pos, di[i], dj[i], max,  getColor(), true, poss);
    }
    positionsToMoves(g, pos, poss, res);
}

char Queen::toChar() const {
    return (getColor())?'Q':'q';
}

char Queen::notation() const {
    return 'Q';
}


