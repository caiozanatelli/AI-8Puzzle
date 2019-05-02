#ifndef _PUZZLE_
#define _PUZZLE_

#include "board.hpp"

class Node {
    private:
        Board board;
        Board parent;
};

class Puzzle {
    private:
        Board board;
        Board goal;

        // Private methods
        void build_goal(int dimension);
    public:
        Puzzle(Board &initial_state);
};

#endif