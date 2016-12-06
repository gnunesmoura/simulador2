#include <init/motion/movement.hpp>

using namespace sim;

#include <iostream>

Movement::Movement (Node * t_node, double t_range, double t_noise) {
    m_node = t_node;
    m_noise = t_noise;
    m_range = t_range;

    m_acceptable_error = m_range * m_noise;
    if (m_acceptable_error < m_static) m_acceptable_error = 0.0000001;
    
    edge strong = strongest_edge ();

    if(strong.second != *m_node)
        new_pos ( movement (strong));
}

bool Movement::move (bool placed) {
    vector move(m_node->pos().size());
    
    for (auto& e: m_node-> anchors())
        move += movement(e);

    if (placed)
        for (auto& e: m_node-> placeds())
            move += movement(e);

    if (placed)
        move /= m_node->anchors_size() + m_node->placeds_size();
    else move /= m_node->anchors_size();

    new_pos (move);
    if(norm(move) > m_static) return true;
    return false;
}

bool Movement::stress () {
    auto anchors = m_node->anchors ();
    auto st = std::find_if(anchors.begin(), anchors.end(), 
            [&](const edge& e){ return norm(movement(e)) > m_acceptable_error; } );

    if (st != anchors.end()) return true;

    auto placeds = m_node->placeds ();
    st = std::find_if(placeds.begin(), placeds.end(), 
            [&](const edge& e){ return norm(movement(e)) > m_acceptable_error; } );

    if (st != placeds.end()) return true;
    return false;
}

void Movement::release_stress () {
    edge strong = strongest_edge ();
    if(strong.first == 0) return;
    new_pos (movement(strong));
    new_pos ((strong.second.pos() - m_node->pos ())*2);
}

edge Movement::strongest_edge () {
    auto anchors = m_node-> anchors();
    auto placeds = m_node-> placeds();

    auto strong_a = std::min_element( anchors.begin (), anchors.end () );
    auto strong_p = std::min_element( placeds.begin (), placeds.end () );

    if ( strong_a != anchors.end () && strong_p != placeds.end () )
        return std::min(*strong_a, *strong_p);
    
    if ( strong_p != placeds.end () ) return *strong_p;
    if ( strong_a != anchors.end () ) return *strong_a;

    edge e(0, *m_node);
    return e;
}

inline void Movement::new_pos (const vector& move) {
    m_node->new_pos (m_node->pos () + move);
}

inline vector Movement::movement (const edge& neighbor) {
    vector move = m_node->pos () - neighbor.second.pos ();
    
    double move_norm = norm(move);
    if (move_norm == 0) return move;

    double divider = move_norm/neighbor.first;

    move = (neighbor.second.pos () - m_node->pos ()) + (move/divider);

    return move;
}

inline double Movement::norm (const vector& vec) {
    vector sqr = std::pow(vec, 2.0);
    double sqr_sum = sqr.sum();
    if (sqr_sum == 0) return 0;
    return std::sqrt(sqr_sum);
} 