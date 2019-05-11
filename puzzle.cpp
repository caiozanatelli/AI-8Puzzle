#include "puzzle.hpp"
#include "board.hpp"
#include "node.hpp"
#include <algorithm>
#include <utility>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>

/*
A single constructor for solving the N-Puzzle problem with a given initial board state
*/
Puzzle::Puzzle(Board &initial_state) {
    this->initial_state = initial_state;
    this->build_goal(initial_state.get_dimension());
}

/*
Private method for building up the goal for the game (winning final state)
*/
void Puzzle::build_goal(int dimension) {
    Matrix goal_matrix(dimension, std::vector<int>(dimension, 0));
    int count = 1;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            // Empty spot (0) is placed at the last position of the board
            goal_matrix[i][j] = (i != dimension -1 || j != dimension - 1) ? 
                                count++ : Board::WHITE_POSITION;
        }
    }
    this->goal = Board(goal_matrix, dimension);
}

/*
Check whether a given board state is the goal one
*/
bool Puzzle::check_goal(Board &board) {
    return (this->goal == board);
}

/*
General user-accessable method for solving an N-Puzzle problem.
The available algorithms are:
    - Uninformed/Blind Search:
        - Breadth-First Search (BFS)
        - Iterative Deepening Search (IDS)
        - Uniform Cost Search (UCS)
    - Informed Search:
        - A*
        - Best-First Search (Greedy)
    - Local Search:
        - HillClimbing
*/
Node* Puzzle::solve(Algorithm algorithm) {
    Node *solution = nullptr;
    switch (algorithm) {
        case BFS:
            solution = this->bfs();
            break;
        case IDS:
            solution = this->ids();
            break;
        case UniformCost:
            solution = this->uniform_cost();
            break;
        case AStar:
            solution = this->a_star();
            break;
        case BestFirst:
            solution = this->best_first();
            break;
        case HillClimbing:
            solution = this->hill_climbing();
        default:
            std::cout << "This algorithm is not supported." << std::endl;
    }
    return solution;
}

void free_frontier(std::vector<Node*> &frontier) {
    while (!frontier.empty()) {
        Node *node = frontier.back();
        frontier.pop_back();
        delete node;
    }
}

void free_frontier(std::deque<Node*> &frontier) {
    while (!frontier.empty()) {
        Node *node = frontier.front();
        frontier.pop_front();
        delete node;
    }
}

/*
Breadth-First Search (BFS).
*/
Node* Puzzle::bfs() {
    Node *root = new Node(this->initial_state);
    if (this->check_goal(this->initial_state)) {
        return root;
    }
    std::deque<Node*> frontier;
    std::set<Board, compare_board_less_than> explored;
    frontier.push_back(root);

    while (!frontier.empty()) {
        // Choose the shallowest node in the frontier
        Node *node = frontier.front();
        frontier.pop_front();
        explored.insert(node->get_state());

        // Expand the node
        std::deque<Node*> children = node->expand();
        for (Node *child : children) {
            Board state = child->get_state();
            bool is_in_explored = (explored.find(state) != explored.end());
            bool is_in_frontier = (std::find_if(frontier.begin(), frontier.end(), 
                                    compare_nodeptr(child)) != frontier.end());
            // Is this node not in the frontier or explored set? 
            if (!is_in_explored || !is_in_frontier) {
                if (this->check_goal(state)) {
                    return child;
                }
                frontier.push_back(child);
            }
        }
    }
    // We reached the end without finding the solution
    return nullptr;
}

/*
Uniform Cost Search (UCS).
*/
Node* Puzzle::uniform_cost() {
    Node *root = new Node(this->initial_state);
    std::priority_queue<Node*, std::vector<Node*>, compare_less_by_cost_nodeptr> frontier;
    std::set<Board, compare_board_less_than> explored;
    std::set<Node*, compare_node_ptr_less_than> frontier_nodes;
    frontier.push(root);
    frontier_nodes.insert(root);

    while (!frontier.empty()) {
        // Choose the node with lowest cost in frontier
        Node *node = frontier.top();
        frontier.pop();
        auto node_delete = frontier_nodes.find(node);
        frontier_nodes.erase(node_delete);

        // Is this node the solution we are searching for?
        Board node_state = node->get_state();
        if (this->check_goal(node_state)) {
            return node;
        }

        // Add node to explored list and expand it
        explored.insert(node_state);
        std::deque<Node*> children = node->expand();
        for (Node *child : children) {
            Board state = child->get_state();
            auto in_frontier = frontier_nodes.find(child);
            bool is_in_explored = (explored.find(state) != explored.end());
            bool is_in_frontier = in_frontier != frontier_nodes.end();
            // If the node is not in the explored list or frontier, add it to the frontier
            if (!is_in_explored || !is_in_frontier) {
                frontier.push(child);
                frontier_nodes.insert(child);
            }
            // If it is in the frontier, replace it if we found a better partial solution (by cost)
            else if ((*in_frontier)->get_cost() > child->get_cost()) {
                Node *parent = child->get_parent();
                (*in_frontier)->update(&parent, child->get_depth(), child->get_cost());
            }
        }
    }
    // We reached the end without finding the solution
    return nullptr;
}

/*
Depth-Limited Search (DLS).
*/
Node* Puzzle::dls(int max_depth) {
    Node* root = new Node(this->initial_state);
    std::vector<Node*> frontier;
    std::vector<Board> explored;
    frontier.push_back(root);
    int explored_nodes = 0;

    while (!frontier.empty()) {
        Node *curr = frontier.back();
        frontier.pop_back();
        Board state = curr->get_state();
        explored_nodes++;

        if (this->check_goal(state)) {
            free_frontier(frontier);
            return curr;
        }
        if (curr->get_depth() > max_depth) {
            free_frontier(frontier);
            delete curr;
            return nullptr;
        }

        std::cout << "Current node depth: " << curr->get_depth() << std::endl;
        explored.push_back(state);

        std::deque<Node*> children = curr->expand();
        while (!children.empty()) {
            Node *child = children.front();
            std::cout << "Child depth: " << child->get_depth() << std::endl;

            children.pop_front();
            auto alternative = std::find(frontier.begin(), frontier.end(), child);
            bool should_expand = (std::find(explored.begin(), explored.end(), child->get_state()) == explored.end());
            if (should_expand && alternative == frontier.end()) {
                frontier.push_back(child);
            }
            else if (alternative != frontier.end() && (*alternative)->get_cost() > child->get_cost() && (*alternative)->get_depth() <= max_depth) {
                Node *parent = child->get_parent();
                (*alternative)->update(&parent, child->get_depth(), child->get_cost());
            }
            else {
                delete child->get_parent();
                delete child;
            }
        }
    }
    return nullptr;
}

/*
Iterative Deepening Depth-First Search (IDS).
*/
Node* Puzzle::ids() {
    for (int i = 0; i < Puzzle::MAX_DEPTH; i++) {
        std::cout << "Current depth: " << i << std::endl;
        Node *solution = this->dls(i);
        if (solution != nullptr) {
            return solution;
        }
        delete solution;
    }
    return nullptr;
}

/*
A* Search.
*/
Node* Puzzle::a_star() {
    return nullptr;
}

/*
Greedy Best-First Search.
*/
Node* Puzzle::best_first() {
    return nullptr;
}

/*
Hill Climbing Search.
*/
Node* Puzzle::hill_climbing() {
    return nullptr;
}

/*Node* Puzzle::greedy() {
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
*/