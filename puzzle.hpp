#ifndef _PUZZLE_
#define _PUZZLE_

#include "board.hpp"
#include "node.hpp"
#include <vector>

enum Algorithm {BFS, DFS, AStar, Greedy};

class Puzzle {
    private:
        Board initial_state;
        Board goal;

        // Private methods
        void build_goal(int dimension);
        Node* bfs();
        Node* dfs();
        Node* greedy();
        Node* a_star();
    public:
        Puzzle(Board &initial_state);
        Node* solve(Algorithm algorithm);
        bool check_goal(Board &board);
};

#endif