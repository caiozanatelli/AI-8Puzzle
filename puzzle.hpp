#ifndef _PUZZLE_
#define _PUZZLE_

#include "board.hpp"
#include "node.hpp"
#include <vector>

namespace puzzleutils {
    // Defining types for search algorithm and heuristics selection
    enum Algorithm {BFS, IDS, UCS, AStar, BestFirst, HillClimbing};
    enum Heuristic {ManhattanDistance, MisplacedNodes, None};

    class Solution {
        private:
            Node *final_node;
            unsigned int explored;
            unsigned int total_nodes;
            unsigned int steps;
            std::vector<std::string> path;
        public:
            Solution();
            Solution(Node *&node, unsigned int explored, unsigned int frontier);
            void print();
            void trace();
            bool is_valid();
    };

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
        puzzleutils::Solution bfs();
        puzzleutils::Solution dls(const int max_depth);
        puzzleutils::Solution ids();
        puzzleutils::Solution uniform_cost();
        puzzleutils::Solution a_star(puzzleutils::Heuristic heuristic);
        puzzleutils::Solution best_first(puzzleutils::Heuristic heuristic);
        puzzleutils::Solution hill_climbing(puzzleutils::Heuristic heuristic, const int limit=10);
    public:
        static const int MAX_DEPTH = 500;
        Puzzle(Board &initial_state);
        puzzleutils::Solution solve(puzzleutils::Algorithm algorithm, 
                                    puzzleutils::Heuristic heuristic=puzzleutils::ManhattanDistance);
        bool check_goal(const Board &board) const;
};

#endif