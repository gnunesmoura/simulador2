#pragma once

#include <valarray>
#include <vector>
#include <utility>
#include <init/instance/edge.hpp>

namespace sim {

enum Type { anchor = 0, placed = 1, not_placed = -1 };

class Node {
public:
    Node (int t_id, std::valarray<double> t_pos, Type t_type);

    Node() {}

    double operator[] (std::size_t at) const;

    bool operator== (const Node& b) const;

    bool operator< (const Node& b) const;
    
    int id () const { return m_id; }

    Type type() const { return m_type; }

    void add_edge (double dist, Node& node);

    const edges& anchors () { return m_anchors; }

    const edges&  neighbors () { return m_neighbors; }

    const edges&  placeds () {return m_placeds; }

    inline std::size_t anchors_size () const { return m_anchors.size (); }

    inline std::size_t neighbors_size () const { return m_neighbors.size (); }
    
    inline std::size_t placeds_size () const { return m_placeds.size (); }

    void new_pos (std::valarray<double> t_pos) { m_pos = t_pos; }

    void new_type (Type t_new);

    void placement_notice (const Node& node);

    const std::valarray<double>& pos () { return m_pos; }

private:
    int m_id = -1;

    std::valarray<double> m_pos;

    Type m_type = not_placed;

    edges m_anchors;

    edges m_neighbors;

    edges m_placeds;
};

} //namespace