#ifndef _BOARD_
#define _BOARD_

#include <utility>
#include <vector>

#define row first
#define col second

typedef std::vector<std::vector<int> > Matrix;
typedef std::pair<int, int> Position;

class Board;

class Board {
    private:
        int dimension;
        Position white_position;
        Matrix matrix;
        Matrix goal;

        Position find_white_position();
    public:
        const static int WHITE_POSITION = 0;

        Board(const Matrix &matrix, int dimension);
        Board();
        Matrix get_matrix();
        Position get_white_position();
        int get_dimension();
        void print();        

        // Overloading operators
        bool operator==(const Board board);
        bool operator!=(const Board board);
};

#endif