#ifndef _BOARD_
#define _BOARD_

#include <utility>
#include <vector>

typedef std::vector<std::vector<int> > Matrix;
typedef std::pair<int, int> Cell;

class Board {
    private:
        int dimension;
        Cell white_position;
        Matrix matrix;
        Matrix goal;

        Cell find_white_position();
    public:
        const static int WHITE_POSITION = 0;
        
        Board(const Matrix &matrix, int dimension);
        Board();
        Matrix get_matrix();
        Cell get_white_position();
        int get_dimension();
        void print();        
};

#endif