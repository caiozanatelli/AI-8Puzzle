#include <iostream>
#include "puzzle.hpp"

/*
Print algorithm settings for solving an N-Puzzle problem
*/
void print_settings(puzzleutils::Algorithm algorithm, puzzleutils::Heuristic heuristic) {
    std::cout << "*************************************************" << std::endl
              << "*            . : N-Puzzle Solver : .            *" << std::endl
              << "*************************************************" << std::endl
              << "*                                               *" << std::endl
              << "*      Federal University of Minas Gerais       *" << std::endl
              << "*         Author: Caio Felipe Zanatelli         *" << std::endl
              << "*                                               *" << std::endl
              << "*************************************************" << std::endl;
    std::cout << std::endl;
    std::cout << "[+] Selected Algorithm: " 
              << ((algorithm == puzzleutils::BFS) ? "Breadth-First Search" :
                 (algorithm == puzzleutils::IDS) ? "Iterative-Deepening Search" :
                 (algorithm == puzzleutils::UCS) ? "Uniform Cost Search" :
                 (algorithm == puzzleutils::AStar) ? "A* Search" :
                 (algorithm == puzzleutils::BestFirst) ? "Best-First Search" : 
                 "Hill Climbing") << std::endl;
    std::cout << "[+] Selected Heurisitc: "
              << ((heuristic == puzzleutils::ManhattanDistance) ? "Manhattan Distance" : "Misplaced Nodes")
              << std::endl << std::endl;
    std::cout << "*************************************************" << std::endl << std::endl;
}

int main() {
    Matrix matrix(3, std::vector<int>(3, 0));
    matrix = {{1, 0, 3}, {4, 2, 5}, {7, 8, 6}};
    //matrix = {{1, 2, 3}, {4, 5, 6}, {7, 0, 8}};    
    //matrix = {{1, 0, 3}, {4, 2, 5}, {7, 8, 3}};
    Board board(matrix, 3);
    Puzzle puzzle(board);

    // Solver settings
    puzzleutils::Algorithm algorithm = puzzleutils::AStar;
    puzzleutils::Heuristic heuristic = puzzleutils::ManhattanDistance;
    print_settings(algorithm, heuristic);
    // Building solution
    puzzleutils::Solution solution = puzzle.solve(algorithm);
    solution.print();

    return 0;
}