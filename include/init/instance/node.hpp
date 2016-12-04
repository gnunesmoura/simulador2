#pragma once

#include <valarray>
#include <vector>
#include <init/instance/edge.hpp>

namespace sim {
enum Type { anchor = 0, placed = 1, not_placed = -1};

class Node {
public:
    Node (int t_id, std::valarray<double> t_pos, Type t_type);

    Node () {}

    const double& operator[] (std::size_t at);

    bool operator< (Node& b) const;
    
    int id () { return m_id; }

    Type type() { return m_type; }

    void add_edge (Node *b, const double dist);

    const std::vector<Edge>& anchors () { return m_anchors; }

    const std::vector<Edge>& neighbors () { return m_neighbors; }

    const std::vector<Edge>& placeds () {return m_placeds; }

    std::size_t anchors_size () const { return m_anchors.size (); }

    std::size_t neighbors_size () const { return m_neighbors.size (); }
    
    std::size_t placeds_size () const { return m_placeds.size (); }

    void new_pos (std::valarray<double> t_pos) { m_pos = t_pos; }

private:
    int m_id = -1;

    std::valarray<double> m_pos;

    Type m_type = not_placed;

    std::vector<Edge> m_anchors;

    std::vector<Edge> m_neighbors;

    std::vector<Edge> m_placeds;
};

} //namespace