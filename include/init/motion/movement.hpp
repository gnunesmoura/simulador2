#pragma once

#include <valarray>
#include <vector>
#include <algorithm>
#include <init/instance/node.hpp>
#include <init/instance/edge.hpp>


namespace sim {

using vector = std::valarray<double>;

class Movement {
public:
    Movement (Node * t_node, double t_range, double t_noise);

    bool move (bool placed);

    bool stress ();

    void release_stress ();

    constexpr const static double m_static = 0.000000000000001;

private:
    Node* m_node;

    double m_range;

    double m_noise;

    double m_acceptable_error;

    edge strongest_edge ();

    inline void new_pos (const vector& move);

    inline vector movement (const edge& neighbor);

    inline double norm (const vector& vec);
};

} //namespace