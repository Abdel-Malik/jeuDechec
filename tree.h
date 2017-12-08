// This is a simple implementation of a "prefix tree" 
// https://en.wikipedia.org/wiki/Trie
// used to represent and play openings in chess.
//
// An *opening* is a sequence of move. For instance, the following openings
// 1. a, f  
// 2. a, b
// 3. a, b, h
// 4. a, c
// 5. e, f, g
// correspond the tree
//                   
//   --a--*-f--*
//   |    |--b-*-h-*
// *-|    |--c-----*
//   |   
//    -e--*-f-*-g--*


#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cassert>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "move.h"
class Tree;

void print_vector(const std::vector<std::string> &v);
void tokenize(const std::string &s, std::vector<std::string> &tokens);

class Tree {
    public:

    Tree();
    Tree(std::string path);
    // add the opening given in `opening` vector starting from index i
    // ...exercise to the reader: use an iterator instead
    void addOpening(const std::vector<std::string> &opening, int i);

    // print all possible moves from current node/tree
    std::vector<std::string> allMoves();

    // return node/tree after playing move s
    // from current node/tree
    Tree *playMove(const std::string &s);

//return the tree above the current if it exist. (previous state)
    Tree* unPlayMove();

//return if the given string correspond to a known move
    bool isMoveExist(const std::string &s);

//Use to return a random move in all known ones. 
    std::string checkKnownMove();
    std::string giveARandomMove();

private:
    // a tree is a map from string (ie. move) to trees
    std::map<std::string, Tree *> children_;

//Used for navigation through the whole tree
    Tree* father = NULL;
    std::string currentNode;

//
    void initializeTree(std::string path);
};

// print a vector of string on one line
void print_vector(const std::vector<std::string> &v);

#endif
