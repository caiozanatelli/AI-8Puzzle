#include "puzzle.hpp"
#include "board.hpp"
#include "node.hpp"
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>
#include <set>

Puzzle::Puzzle(Board &initial_state) {
    this->initial_state = initial_state;
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

bool Puzzle::check_goal(Board &board) {
    return (this->goal == board);
}

Node* Puzzle::solve(Algorithm algorithm) {
    Node *solution = nullptr;
    switch (algorithm) {
        case BFS:
            solution = this->bfs();
            break;
        case DFS:
            solution = this->dfs();
            break;
        case AStar:
            solution = this->a_star();
            break;
        case Greedy:
            solution = this->greedy();
            break;
        default:
            std::cout << "This algorithm is not supported." << std::endl;
    }
    return solution;
}

Node* Puzzle::bfs() {
    Node *root = new Node(this->initial_state);
    if (this->check_goal(this->initial_state)) {
        return root;
    }

    std::deque<Node*> frontier;
    std::vector<Board> explored;
    frontier.push_back(root);
    int explored_nodes = 0;

    while (!frontier.empty()) {
        Node *curr = frontier.front();
        frontier.pop_front();
        Board state = curr->get_state();
        explored_nodes++;

        if (this->check_goal(state)) {
            while (!frontier.empty()) {
                Node *node = frontier.front();
                frontier.pop_front();
                //node->free();
                delete node;
            }
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
            else if (alternative != frontier.end() && (*alternative)->get_cost() > child->get_cost()) {
                Node *parent = child->get_parent();
                (*alternative)->update(&parent, child->get_depth(), child->get_cost());
            }
            else {
                delete child;
            }
        }
    }
    return nullptr;
}

Node* Puzzle::dfs() {
    return nullptr;
}

Node* Puzzle::greedy() {
    Node *root = new Node(this->initial_state);
    std::vector<Board> closed;
    std::deque<Node*> leaves;
    leaves.push_back(root);
    
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
    return nullptr;
}

Node* Puzzle::a_star() {
    return nullptr;
}