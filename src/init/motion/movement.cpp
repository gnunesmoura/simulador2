#include <init/motion/movement.hpp>

using namespace sim;

#include <iostream>

Movement::Movement (Node * t_node, double t_range, double t_noise) {
    m_node = t_node;
    m_noise = t_noise;
    m_range = t_range;

    m_acceptable_error = m_range * m_noise;
    if (m_acceptable_error < m_static) m_acceptable_error = m_static;
    edge strong = strongest_edge ();
    if(strong.first != 0)
        new_pos ( movement (strong));
}

bool Movement::move (bool placed) {
    std::valarray<double> move(m_node->pos().size());
    
    for (auto& e: m_node-> anchors())
        move += movement(e);

    if (placed)
        for (auto& e: m_node-> placeds())
            move += movement(e);

    if (placed)
        move /= m_node->anchors_size() + m_node->placeds_size();
    else move /= m_node->anchors_size();

    for (auto& m: move) std::cout << m << " ";
    std::cout << "\n";
    new_pos (move);
    return true;
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

    return *strong_a;
}

inline void Movement::new_pos (std::valarray<double> move) {
    m_node->new_pos (m_node->pos () + move);
}

inline std::valarray<double> Movement::movement (const edge& neighbor) {
    std::valarray<double> move = m_node->pos () - neighbor.second.pos ();

    double divider = norm(move)/neighbor.first;
    move = (neighbor.second.pos () - m_node->pos ()) + (move/divider);

    return move;
}

inline double Movement::norm (const std::valarray<double>& vector) {
    std::valarray<double> sqr = std::pow(vector, 2.0);
    double sqr_sum = sqr.sum();
    if (sqr_sum == 0) return 0;
    return std::sqrt(sqr_sum);
} 