#include <iostream>
#include "puzzle.hpp"

int main() {
    Matrix matrix(3, std::vector<int>(3, 0));
    matrix = {{1, 0, 3}, {4, 2, 5}, {7, 8, 6}};
    //matrix = {{1, 2, 3}, {4, 5, 6}, {7, 0, 8}};
    
    //matrix = {{1, 0, 3}, {4, 2, 5}, {7, 8, 3}};
    Board board(matrix, 3);
    board.print();

    Puzzle puzzle(board);
    Node *final_node = puzzle.solve(puzzleutils::AStar);
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Solution with Breadth-First Search: " << std::endl;

    if (final_node) {
        puzzleutils::Solution solution(final_node, 0, 0);
        solution.print();
    }
    return 0;
}