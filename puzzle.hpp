#ifndef _PUZZLE_
#define _PUZZLE_

#include "board.hpp"
#include "node.hpp"
#include <vector>

namespace puzzleutils {
    // Defining types for search algorithm and heuristics selection
    enum Algorithm {BFS, IDS, UniformCost, AStar, BestFirst, HillClimbing};
    enum Heuristic {ManhattanDistance, MisplacedNodes, None};

    /* 
    Return a function pointer to calculate path cost based on he heuristic chosen
    
    int (*fptr(Heuristic heuristic))(const Board&, const Board&) {
        if (heuristic == ManhattanDistance) return &boardutils::calculate_manhattan_distance;
        if (heuristic == MisplacedNodes) return &boardutils::calculate_misplaced_nodes;
        return nullptr;
    } */
}

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
        Node* a_star(puzzleutils::Heuristic heuristic);
        Node* best_first(puzzleutils::Heuristic heuristic);
        Node* hill_climbing(puzzleutils::Heuristic heuristic);
    public:
        static const int MAX_DEPTH = 10;
        Puzzle(Board &initial_state);
        Node* solve(puzzleutils::Algorithm algorithm, puzzleutils::Heuristic heuristic=puzzleutils::ManhattanDistance);
        bool check_goal(const Board &board) const;
};

#endif