#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>
#include <set>
#include "puzzle.hpp"
#include "board.hpp"
#include "node.hpp"

Node* best_first(Node **root) {
    Matrix matrix(3, std::vector<int>(3, 0));
    matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};    
    Board goal(matrix, 3);

    std::vector<Board> closed;
    std::deque<Node*> leaves;
    leaves.push_back(*root);

    while (true) {
        if (leaves.empty()) return nullptr;
        Node *curr = leaves.front();
        leaves.pop_front();
        Board state = curr->get_state();
        if (state == goal) return curr;
        if (std::find(closed.begin(), closed.end(), state) == closed.end()) {
            closed.push_back(state);
            std::deque<Node*> children = curr->generate_children();
            while (!children.empty()) {
                leaves.push_back(children.front());
                children.pop_front();
            }
        }
    }
}

Node* bfs(Node **root) {
    Matrix matrix(3, std::vector<int>(3, 0));
    matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};    
    Board goal(matrix, 3);

    if ((*root)->get_state() == goal) return *root;

    std::deque<Node*> frontier;
    std::vector<Board> explored;
    frontier.push_back(*root);
    int explored_nodes = 0;

    while (!frontier.empty()) {
        Node *curr = frontier.front();
        Board state = curr->get_state();
        frontier.pop_front();
        explored_nodes++;

        if (state == goal) {
            return curr;
        }
        explored.push_back(state);
        std::deque<Node*> children = curr->generate_children();

        while (!children.empty()) {
            Node *child = children.front();
            children.pop_front();

            auto alternative = std::find(frontier.begin(), frontier.end(), child);
            bool should_expand = (std::find(explored.begin(), explored.end(), child->get_state()) == explored.end());
            if (should_expand && alternative == frontier.end()) {
                frontier.push_back(child);
            }
            if (alternative != frontier.end() && (*alternative)->get_cost() > child->get_cost()) {
                Node *parent = child->get_parent();
                (*alternative)->update(&parent, child->get_depth(), child->get_cost());
            }
        }
    }

    return nullptr;
}

int main() {
    Matrix matrix(3, std::vector<int>(3, 0));
    matrix = {{1, 0, 3}, {4, 2, 5}, {7, 8, 6}};
    Board board(matrix, 3);
    board.print();

    //Puzzle puzzle(board);

    Node *init = new Node(board);
    std::cout << "Solution with Best-First Search: " << std::endl;
    Node *solution = best_first(&init);
    solution->print_solution();
    solution->get_state().print();

    /*std::cout << "---------------------------------------------" << std::endl;
    std::cout << "Solution with Breadth-First Search: " << std::endl;
    solution = bfs(&init);
    solution->print_solution();
    solution->get_state().print(); */
    return 0;
}