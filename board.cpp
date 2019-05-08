#include <iostream>
#include <utility>
#include <iomanip>
#include <vector>
#include <cmath>
#include "board.hpp"

const std::vector<int> Board::moves({UP, DOWN, LEFT, RIGHT});

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

int Board::get_manhattan_distance() {
    int count = 0;
    int dimension = this->dimension;

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            int cell = matrix[i][j];
            int row = (cell != 0) ? std::floor((cell - 1) / dimension) : dimension - 1;
            int col = (cell % dimension != 0) ? (cell % dimension) - 1 : dimension - 1;
            count += std::abs(i - row) + std::abs(j - col);
        }
    }
    return count;
}

void swap(int &x, int &y) {
    int aux = x;
    x = y;
    y = aux;
}

void Board::move(int direction) {
    int row  = this->white_position.row;
    int col  = this->white_position.col;
    int size = this->dimension;

    if (row < 0 || row >= this->dimension || col < 0 || col >= this->dimension) {
        return;
    }
    if (direction == Board::UP && row > 0) {
        swap(this->matrix[row][col], this->matrix[row - 1][col]);
        this->white_position.row = row - 1;
    }
    else if (direction == Board::DOWN && row < size - 1) {
        swap(this->matrix[row][col], this->matrix[row + 1][col]);
        this->white_position.row = row + 1;
    }
    else if (direction == Board::LEFT && col > 0) {
        swap(this->matrix[row][col], this->matrix[row][col - 1]);
        this->white_position.col = col - 1;
    }
    else if (direction == Board::RIGHT && col < size - 1) {
        swap(this->matrix[row][col], this->matrix[row][col + 1]);
        this->white_position.col = col + 1;
    }
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
