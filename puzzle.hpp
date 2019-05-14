#ifndef _PUZZLE_
#define _PUZZLE_

#include "board.hpp"
#include "node.hpp"
#include <vector>

// Defining types for search algorithm and heuristics selection
enum Algorithm {BFS, IDS, UniformCost, AStar, BestFirst, HillClimbing};
enum Heuristic {ManhattanDistance};

class Puzzle {
    private:
        Board initial_state;
        Board goal;

        // Private methods
        void build_goal(const int dimension);
        Node* bfs();
        Node* dls(const int max_depth);
        Node* ids();
        Node* uniform_cost();
        Node* a_star();
        Node* best_first();
        Node* hill_climbing();
    public:
        static const int MAX_DEPTH = 10;
        Puzzle(Board &initial_state);
        Node* solve(Algorithm algorithm);
        bool check_goal(const Board &board) const;
};

#endif