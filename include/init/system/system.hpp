#pragma once 

#include <vector>
#include <algorithm>
#include <iostream>

#include <init/instance/node.hpp>
#include <init/instance/instance.hpp>
#include <init/instance/edge.hpp>
#include <init/motion/movement.hpp>

namespace sim {

class System {
public:
    System (Instance& t_instance): m_instance (t_instance) {
        m_moves.reserve(m_instance.nodes().size());
    }

    void solve ();

    void solve_tree ();

    void solve_test ();
    
private:
    Instance& m_instance;

    std::vector<Movement> m_moves;

    void find_place (Node * t_node);
    
    inline void move_until_stop (Movement& t_move, bool placed);

};

}//namespace