#ifndef _PUZZLE_
#define _PUZZLE_

#include "board.hpp"
#include "node.hpp"
#include <vector>

enum Algorithm {BFS, IDS, AStar, Greedy};
enum Heuristic {ManhattanDistance};

class Puzzle {
    private:
        Board initial_state;
        Board goal;

        // Private methods
        void build_goal(int dimension);
        Node* bfs();
        Node* dfs();
        Node* dls(int max_depth);
        Node* ids();
        Node* greedy();
        Node* a_star();
    public:
        static const int MAX_DEPTH = 10;
        Puzzle(Board &initial_state);
        Node* solve(Algorithm algorithm);
        bool check_goal(Board &board);
};

#endif