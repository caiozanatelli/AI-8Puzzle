#ifndef _BOARD_
#define _BOARD_

#include <iostream>
#include <utility>
#include <vector>

#define row first
#define col second

typedef std::vector<std::vector<int> > Matrix;
typedef std::pair<int, int> Position;

class Board {
    private:
        int dimension;
        Position white_position;
        Matrix matrix;
        Matrix goal;

        // Methods
        Position find_white_position();
    public:
        const static int WHITE_POSITION = 0;
        const static int UP    = 1;
        const static int DOWN  = 2;
        const static int LEFT  = 3;
        const static int RIGHT = 4;
        const static std::vector<int> moves;

        Board(const Matrix &matrix, int dimension);
        Board();
        Matrix get_matrix();
        Position get_white_position();
        int get_dimension();
        int get_element_at(int row, int col);
        int get_element_at(Position position);
        void print(); 
        void move(int direction);

        // Overloading operators
        bool operator==(const Board board);
        bool operator!=(const Board board);
};

namespace boardutils {
    struct compare_board_less_than : public std::binary_function<Board, Board, bool> {
        bool operator()(const Board &b1, const Board &b2) const {
            return false; // Always insert element in the end of a set
        }
    };

    int calculate_manhattan_distance(Board &board);
    int calculate_misplaced_nodes(Board &board, Board &goal);
    void swap(int &a, int &b);
}

#endif