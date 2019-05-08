#ifndef _NODE_
#define _NODE_

#include <iostream>
#include <vector>
#include <deque>
#include "board.hpp"

class Node {
    private:
        std::vector<int> moves;
        Board state;
        Node *parent;
        int depth;
        int costfn;
        int cost;
        // Private methods
        void set_cost();
    public:
        // Public methods
        Node(Board &board);
        Node(Board &board, int move);
        Node(Board &board, Node *parent, int move);
        //Node(Board &board, int costfn);
        //Node(Board &board, int costfn, Node *parent);
        std::vector<Node> expand();
        void update(Node **new_parent, int new_depth, int new_cost);
        void print_solution();
        void free();

        // Getters
        int get_costfn();
        int get_cost();
        int get_depth();
        Node *get_parent();
        Board get_state();
        std::deque<Node*> generate_children();
        std::vector<int> get_moves();
        
        // Overloading operators
        bool operator <(Node *node);
        bool operator >(Node *node);
        bool operator ==(Node *node);
        bool operator !=(Node *node);
};

#endif