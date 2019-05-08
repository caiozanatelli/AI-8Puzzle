#ifndef _BOARD_
#define _BOARD_

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
        int get_manhattan_distance();
        void move(int direction);
        void print(); 

        // Overloading operators
        bool operator==(const Board board);
        bool operator!=(const Board board);
};

#endif