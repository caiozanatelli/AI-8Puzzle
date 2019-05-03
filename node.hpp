#include <iostream>
#include <vector>
#include "board.hpp"

class Node {
    private:
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
        Node(Board &board, int costfn);
        Node(Board &board, int costfn, Node *parent);
        std::vector<Node> expand();
        void update(Node *new_parent, int new_depth, int new_cost);
        
        // Getters
        int get_costfn();
        int get_cost();
        int get_depth();
        Node *get_parent();
        Board get_state();
        
        // Overloading operators
        bool operator <(Node *node);
        bool operator >(Node *node);
        bool operator ==(Node *node);
        bool operator !=(Node *node);
};
