#include <iostream>
#include <vector>
#include <deque>
#include "board.hpp"
#include "node.hpp"

/*
Set the proper path cost taking into account heuristic cost functions (greedy or not)
*/
void nodeutils::set_cost_by_heuristic(Node *node, int (*f_heuristic)(Board), bool greedy) {
    int costfn = f_heuristic(node->get_state());
    node->set_costfn(costfn);
    if (greedy) {
        node->set_cost(costfn);
    }
    else {
        node->set_cost(costfn + node->get_depth());
    }
}

/*
Constructor with only the board as parameter
*/
Node::Node(Board &board) {
    this->state  = board;
    this->parent = nullptr;
    this->depth  = 0;
    this->cost   = 0;
    this->costfn = 0;
}

/*
Constructor with board, parent and performed move as parameters
*/
Node::Node(Board &board, Node *parent, int move, int (*f_heuristic)(Board), bool is_greedy) {
    this->state  = board;
    this->parent = parent;
    this->moves  = (parent != nullptr) ? parent->moves : this->moves;
    if (parent == nullptr) {
        this->moves.push_back(move);
        this->depth  = 0;
        this->cost   = 0;
        this->costfn = 0;
    }
    else {
        this->depth = parent->get_depth() + 1;
        this->moves = parent->get_moves();
        if (!f_heuristic) {
            this->cost  = parent->get_cost() + 1;
        }
        else {
            nodeutils::set_cost_by_heuristic(this, f_heuristic, is_greedy);
        }
    }
    this->moves.push_back(move);
}

/*
Free a node
*/
void Node::free() {
    if (this->parent != nullptr) {
        this->parent->free();
    }
    delete this;
}

/*
Expand a node by performing all the allowed actions to the given state
*/
std::deque<Node*> Node::expand(int (*f_heuristic)(Board), bool is_greedy) {
    std::deque<Node*> children;
    for (auto move : Board::moves) {
        Board new_board(this->state);
        new_board.move(move);
        if (this->state != new_board) {
            children.push_back(new Node(new_board, this, move, f_heuristic, is_greedy));   
        }
    }
    return children;
}

/*
Print the solution
*/
void Node::print_solution() const {
    for (int move : this->moves) {
        if (move == Board::UP) std::cout << "UP ";
        else if (move == Board::DOWN) std::cout << "DOWN ";
        else if (move == Board::LEFT) std::cout << "LEFT ";
        else if (move == Board::RIGHT) std::cout << "RIGHT ";
    }
    std::cout << std::endl;
}

/*
Update a node with new parent, depth and cost values
*/
void Node::update(Node **new_parent, int new_depth, int new_cost) {
    this->parent = *new_parent;
    this->cost   = new_cost;
    this->depth  = new_depth;
}

void Node::update(Node *node) {
    this->parent = node->get_parent();
    this->cost = node->get_cost();
    this->depth = node->get_depth();
    this->state = node->get_state();
    this->moves = node->get_moves();
    this->costfn = node->get_costfn();
}
/*
Return the moves performed so far to get to the current state
*/
std::vector<int> Node::get_moves() const {
    return this->moves;
}

/*
Return the heuristic cost
*/
int Node::get_costfn() const {
    return this->costfn;
}

/*
Set a new value to the heuristic cost
*/
void Node::set_costfn(int costfn) {
    this->costfn = costfn;
}

/*
Return the path cost
*/
int Node::get_cost() const {
    return this->cost;
}

/*
Set a new value to the path cost
*/
void Node::set_cost(int cost) {
    this->cost = cost;
}

/*
Return the node depth with regards to the root state
*/
int Node::get_depth() const {
    return this->depth;
}

/*
Set a new value to the node depth
*/
void Node::set_depth(int depth) {
    this->depth = depth;
}

/*
Return the parent of the current node
*/
Node* Node::get_parent() const {
    return this->parent;
}

/*
Return the state the current node describes
*/
Board Node::get_state() const {
    return this->state;
}

/*
Overloading operator < based on path cost
*/
bool Node::operator <(const Node &node) const {
    return this->cost < node.get_cost();
}

/*
Overloading operator > based on path cost
*/
bool Node::operator >(const Node &node) const {
    return this->cost > node.get_cost();
}

/*
Overloading operator == based on state board
*/
bool Node::operator ==(const Node &node) const {
    return this->state == node.get_state();
}

/*
Overloading operator != based on state board
*/
bool Node::operator !=(const Node &node) const {
    return this->state != node.get_state();
}
