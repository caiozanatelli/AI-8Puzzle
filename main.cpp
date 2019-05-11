#include <iostream>
#include "puzzle.hpp"
#include "board.hpp"
#include "node.hpp"

int main() {
    Matrix matrix(3, std::vector<int>(3, 0));
    matrix = {{1, 0, 3}, {4, 2, 5}, {7, 8, 6}};
    
    //matrix = {{1, 0, 3}, {4, 2, 5}, {7, 8, 3}};
    Board board(matrix, 3);
    board.print();

    Puzzle puzzle(board);
    Node *solution = puzzle.solve(IDS);
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Solution with Breadth-First Search: " << std::endl;
    if (solution) {
        solution->print_solution();
        solution->get_state().print();
        std::cout << "Cost:  " << solution->get_cost() << std::endl;
        std::cout << "Depth: " << solution->get_depth() << std::endl;
        solution->free();
    }

    return 0;
}