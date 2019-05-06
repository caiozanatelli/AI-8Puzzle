#include "puzzle.hpp"
#include "board.hpp"
#include "node.hpp"
#include <vector>

Puzzle::Puzzle(Board &initial_state) {
    this->board = initial_state;
    this->build_goal(initial_state.get_dimension());
}

void Puzzle::build_goal(int dimension) {
    Matrix goal_matrix(dimension, std::vector<int>(dimension, 0));
    int count = 1;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            goal_matrix[i][j] = (i != dimension -1 || j != dimension - 1) ? count++ : Board::WHITE_POSITION;
        }
    }
    this->goal = Board(goal_matrix, dimension);
}
