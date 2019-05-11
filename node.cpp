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

/*
Constructor with only the board as parameter
*/
Node::Node(Board &board) {
    this->state  = board;
    this->parent = nullptr;
    this->depth  = 0;
    this->cost   = 0;
    this->costfn = 0;
    //this->set_cost();
}

/*
Constructor with board, parent and performed move as parameters
*/
Node::Node(Board &board, Node *parent, int move) {
    this->state  = board;
    this->parent = parent;
    this->moves  = (parent != nullptr) ? parent->moves : this->moves;
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

/*
Free a node
*/
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

/*
Expand a node by performing all the allowed actions to the given state
*/
std::deque<Node*> Node::expand() {
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

/*
Print the solution
*/
void Node::print_solution() {
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

/*
Return the moves performed so far to get to the current state
*/
std::vector<int> Node::get_moves() {
    return this->moves;
}

/*
Return the heuristic cost
*/
int Node::get_costfn() {
    return this->costfn;
}

/*
Return the path cost
*/
int Node::get_cost() {
    return this->cost;
}

/*
Return the node depth with regards to the root state
*/
int Node::get_depth() {
    return this->depth;
}

/*
Return the parent of the current node
*/
Node* Node::get_parent() {
    return this->parent;
}

/*
Return the state the current node describes
*/
Board Node::get_state() {
    return this->state;
}

/*
Overloading operator < based on path cost
*/
bool Node::operator <(Node &node) {
    return this->cost < node.get_cost();
}

/*
Overloading operator > based on path cost
*/
bool Node::operator >(Node &node) {
    return this->cost > node.get_cost();
}

/*
Overloading operator == based on state board
*/
bool Node::operator ==(Node &node) {
    return this->state == node.get_state();
}

/*
Overloading operator != based on state board
*/
bool Node::operator !=(Node &node) {
    return this->state != node.get_state();
}
