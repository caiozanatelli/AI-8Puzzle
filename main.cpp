#include <algorithm>
#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include "puzzle.hpp"

#define POS_ALGORITHM   1
#define POS_HEURISTIC   2
#define POS_DIMENSION   3
#define POS_INPUT_FILE  4

/*
Print algorithm settings for solving an N-Puzzle problem
*/
void print_settings(puzzleutils::Algorithm algorithm, puzzleutils::Heuristic heuristic) {
    std::cout << "*************************************************" << std::endl
              << "*            . : N-Puzzle Solver : .            *" << std::endl
              << "*************************************************" << std::endl
              << "*                                               *" << std::endl
              << "*      Federal University of Minas Gerais       *" << std::endl
              << "*         Author: Caio Felipe Zanatelli         *" << std::endl
              << "*                                               *" << std::endl
              << "*************************************************" << std::endl;
    std::cout << std::endl;
    std::cout << "[+] Selected Algorithm: " 
              << ((algorithm == puzzleutils::BFS) ? "Breadth-First Search" :
                 (algorithm == puzzleutils::IDS) ? "Iterative-Deepening Search" :
                 (algorithm == puzzleutils::UCS) ? "Uniform Cost Search" :
                 (algorithm == puzzleutils::AStar) ? "A* Search" :
                 (algorithm == puzzleutils::BestFirst) ? "Best-First Search" : 
                 "Hill Climbing") << std::endl;
    std::cout << "[+] Selected Heurisitc: "
              << ((heuristic == puzzleutils::ManhattanDistance) ? "Manhattan Distance" : "Misplaced Nodes")
              << std::endl << std::endl;
    std::cout << "*************************************************" << std::endl << std::endl;
}

void exit_error(std::string msg) {
    std::cerr << msg << std::endl;
    exit(1);
}

char* get_cmd_option(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return 0;
}

bool cmd_option_exists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}

int main(int argc, char **argv) {
    //if (argc != 5) exit_error("Incorrect parameters.");

    puzzleutils::Algorithm algorithm = puzzleutils::AStar;
    puzzleutils::Heuristic heuristic = puzzleutils::ManhattanDistance;
    int dimension = 3;

    char *param_file_name = get_cmd_option(argv, argv + argc, "--file");
    char *param_dimension = get_cmd_option(argv, argv + argc, "--dimension");
    char *param_algorithm = get_cmd_option(argv, argv + argc, "--algorithm");
    char *param_heuristic = get_cmd_option(argv, argv + argc, "--heuristic");

    if (!param_file_name) {
        exit_error("You must inform the input board.");
    }
    if (param_dimension) {
        sscanf(param_dimension, "%d", &dimension);
    }
    
    // Selecting algorithm
    if (param_algorithm) {
        std::string in_algorithm(param_algorithm);
        if (in_algorithm == "BFS") algorithm = puzzleutils::BFS;
        else if (in_algorithm == "UCS") algorithm = puzzleutils::UCS;
        else if (in_algorithm == "IDS") algorithm = puzzleutils::IDS;
        else if (in_algorithm == "AStar") algorithm = puzzleutils::AStar;
        else if (in_algorithm == "BestFirst") algorithm = puzzleutils::BestFirst;
        else if (in_algorithm == "HillClimbing") algorithm = puzzleutils::HillClimbing;
        else exit_error("Selected algorithm is not supported.");
    }

    // Selecting heuristic
    if (param_heuristic) {
        std::string in_heuristic(param_heuristic);
        if (in_heuristic == "ManhattanDistance") heuristic = puzzleutils::ManhattanDistance;
        else if (in_heuristic == "MisplacedNodes") heuristic = puzzleutils::MisplacedNodes;
        else exit_error("Selected heuristic is not supported.");
    }

    // Reading board from file
    std::ifstream fp(param_file_name);
    std::string line;
    std::string token;
    Matrix matrix(dimension, std::vector<int>(dimension, 0));
    int row = 0;
    int col = 0;
    while (getline(fp, line)) {
        std::istringstream ss(line);
        while (getline(ss, token, ',')) {
            if (row >= dimension || col >= dimension) exit_error("Dimension does not match input board.");
            std::istringstream(token) >> matrix[row][col++];
        }
        col = 0; row++;
    }

    // Building puzzle from input board
    Board board(matrix, dimension);
    Puzzle puzzle(board);
    board.print();
    puzzleutils::Solution solution = puzzle.solve(algorithm, heuristic);
    solution.print();

    return 0;
}