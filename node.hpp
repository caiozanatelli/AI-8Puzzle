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
    public:
        // General methods
        Node(Board &board);
        Node(Board &board, Node *parent, int move, int (*f_costfn)(Board), bool is_greedy=true);

        std::deque<Node*> expand(int (*f_heuristic)(Board)=nullptr, bool is_greedy=true);
        void update(Node **new_parent, int new_depth, int new_cost);
        void update(Node *node);
        void print_solution();
        void free();

        // Getters & setters
        int get_costfn();
        int get_cost();
        int get_depth();
        Node *get_parent();
        Board get_state();
        std::vector<int> get_moves();
        void set_cost(int cost);
        void set_costfn(int costfn);
        void set_depth(int depth);
        
        // Overloading operators
        bool operator <(Node &node);
        bool operator >(Node &node);
        bool operator ==(Node &node);
        bool operator !=(Node &node);
};

namespace nodeutils {
    void set_cost_by_heuristic(Node *node, int (*f_heuristic)(Board), bool greedy=true);

    // Overloading comparison between Node pointers 
    struct compare_nodeptr {
        Node *node_ptr;
        compare_nodeptr(Node *node) : node_ptr(node) {}
        bool operator()(Node *cls) {
            return (cls->get_state() == node_ptr->get_state());
        }
    };

    // Overloading comparison between node pointers by lowest path cost
    struct compare_less_by_cost_nodeptr {
        bool operator()(Node *n1, Node *n2) {
            return n1->get_cost() > n2->get_cost(); // Take care, C++ STL implements MAX heap
        }
    };

    // Overloading comparison less than between Node pointers for binary function (set)
    struct compare_node_ptr_less_than : public std::binary_function<Node*, Node*, bool> {
        bool operator()(Node *n1, Node *n2) const {
            return false; // Always insert element in the end of a set
        }
    };
}

#endif