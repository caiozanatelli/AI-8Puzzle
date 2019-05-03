#include <iostream>
#include <utility>
#include <iomanip>
#include <vector>
#include "board.hpp"

Board::Board(const Matrix &matrix, int dimension) {
    if (dimension != (int) matrix.size()) {
        std::cout << "Selected dimension does not match the matrix." << std::endl;
        exit(1);
    }
    this->matrix = matrix;
    this->dimension = (int) matrix.size();
    this->white_position = this->find_white_position();
}

Board::Board() {}

Position Board::find_white_position() {
    for (int i = 0; i < this->dimension; i++) {
        for (int j = 0; j < this->dimension; j++) {
            if (this->matrix[i][j] == Board::WHITE_POSITION) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);
}

Matrix Board::get_matrix() {
    return this->matrix;
}

Position Board::get_white_position() {
    return this->white_position;
}

int Board::get_dimension() {
    return this->dimension;
}

void Board::print() {
    for (int i = 0; i < this->dimension; i++) {
        for (int j = 0; j < this->dimension; j++) {
            std::cout << std::setfill(' ') << std::setw(5) << this->matrix[i][j];
        }
        std::cout << std::endl;
    }
}

// Overloading operators
bool Board::operator==(const Board board) {
    return this->matrix == board.matrix;
}

bool Board::operator!=(const Board board) {
    return this->matrix != board.matrix;
}
