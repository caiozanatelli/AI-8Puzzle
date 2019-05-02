#include <iostream>
#include "board.hpp"

int main() {
    Matrix matrix(3, std::vector<int>(3, 0));
    Board board(matrix, 3);
    board.print();
    return 0;
}