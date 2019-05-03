#ifndef _PUZZLE_
#define _PUZZLE_

#include "board.hpp"
#include "node.hpp"
#include <vector>

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