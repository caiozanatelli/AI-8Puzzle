#include <iostream>
#include <vector>
#include <deque>
#include "board.hpp"
#include "node.hpp"

// Private methods
void Node::set_cost() {
    if (this->costfn < 0) {
        this->cost = 0;
    }
    else {
        //this->costfn;
    }
}

// Public methods
Node::Node(Board &board) {
    this->state  = board;
    this->parent = nullptr;
    this->depth  = 0;
    this->cost   = 0;
    this->costfn = -1;
    //this->set_cost();
}

Node::Node(Board &board, Node *parent, int move) {
    this->state  = board;
    this->parent = parent;
    this->moves  = (parent != nullptr) ? parent->moves : this->moves;
    //this->moves.push_back(move);
    //std::cout << "Adding new node... Number of movements: " << this->moves.size() << std::endl;
    if (parent == nullptr) {
        this->moves.push_back(move);
        this->depth = 0;
        this->cost = 0;
    }
    else {
        this->depth = parent->get_depth() + 1;
        this->moves = parent->get_moves();
        this->cost  = parent->get_cost() + 1;
    }
    this->moves.push_back(move);
}

void Node::free() {
    if (this->parent != nullptr) {
        this->parent->free();
    }
    delete this;
}

/*Node::Node(Board &board, int costfn) {
    this->state  = board;
    this->parent = nullptr;
    this->depth  = 0;
    this->costfn = costfn;
    //this->set_cost();
}*/

/*Node::Node(Board &board, int costfn, Node *parent) {
    this->state  = board;
    this->parent = parent;
    this->depth  = (parent != nullptr) ? parent->get_depth() + 1 : 0;
    this->costfn = (parent != nullptr) ? parent->get_costfn() : costfn;
    //this->set_cost();
}*/

std::vector<Node> Node::expand() {
    std::vector<Node> children;
    Position white = this->state.get_white_position();
    if (white.col > 0) {
        //children.push_back(Node())
    }
    return children;
}

std::deque<Node*> Node::generate_children() {
    std::deque<Node*> children;
    for (auto move : Board::moves) {
        Board new_board(this->state);
        new_board.move(move);
        if (this->state != new_board) {
            children.push_back(new Node(new_board, this, move));
        }
    }
    return children;
}

std::vector<int> Node::get_moves() {
    return this->moves;
}

void Node::print_solution() {
    for (int move : this->moves) {
        if (move == Board::UP) std::cout << "UP ";
        else if (move == Board::DOWN) std::cout << "DOWN ";
        else if (move == Board::LEFT) std::cout << "LEFT ";
        else if (move == Board::RIGHT) std::cout << "RIGHT ";
    }
    std::cout << std::endl;
}

void Node::update(Node **new_parent, int new_depth, int new_cost) {
    this->parent = *new_parent;
    this->cost   = new_cost;
    this->depth  = new_depth;
}

// Getters
int Node::get_costfn() {
    return this->costfn;
}

int Node::get_cost() {
    return this->cost;
}

int Node::get_depth() {
    return this->depth;
}

Node* Node::get_parent() {
    return this->parent;
}

Board Node::get_state() {
    return this->state;
}

// Overloading operators
bool Node::operator <(Node *node) {
    return this->cost < node->get_cost();
}

bool Node::operator >(Node *node) {
    return this->cost > node->get_cost();
}

bool Node::operator ==(Node *node) {
    return this->state == node->get_state();
}

bool Node::operator !=(Node *node) {
    return this->state != node->get_state();
}
