#include <iostream>
#include <vector>
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
    this->costfn = -1;
    this->set_cost();
}

Node::Node(Board &board, int costfn) {
    this->state  = board;
    this->parent = nullptr;
    this->depth  = 0;
    this->costfn = costfn;
    this->set_cost();
}

Node::Node(Board &board, int costfn, Node *parent) {
    this->state  = board;
    this->parent = parent;
    this->depth  = (parent != nullptr) ? parent->get_depth() + 1 : 0;
    this->costfn = (parent != nullptr) ? parent->get_costfn() : costfn;
    this->set_cost();
}

std::vector<Node> Node::expand() {
    std::vector<Node> children;
    Position white = this->state.get_white_position();
    if (white.col > 0) {
        //children.push_back(Node())
    }
    return children;
}

void Node::update(Node *new_parent, int new_depth, int new_cost) {
    this->parent = new_parent;
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
