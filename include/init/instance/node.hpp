#pragma once

#include <stdio.h>
#include <valarray>
#include <vector>
#include <utility>

#include <init/instance/edge.hpp>

namespace sim {

enum Type { anchor = 0, placed = 1, not_placed = 2, queued = 3 };

using point = std::valarray<double>;

class Node {
public:
    Node (int t_id, point t_pos, Type t_type, point t_limit):
          m_id(t_id), m_pos(t_pos), m_type(t_type), m_limit(t_limit) {};  

    Node() {}

    double operator[] (std::size_t at) const;

    bool operator== (const Node& b) const;

    bool operator!= (const Node& b) const { return !(*this == b); }

    bool operator< (const Node& b) const;

    bool operator> (const Node& b) const { return b < *this; } 
    
    int id () const { return m_id; }

    Type type() const { return m_type; }

    void add_edge (double dist, Node& node);

    const edges& anchors () { return m_anchors; }

    const edges&  neighbors () { return m_neighbors; }

    const edges&  placeds () {return m_placeds; }

    inline std::size_t anchors_size () const { return m_anchors.size (); }

    inline std::size_t neighbors_size () const { return m_neighbors.size (); }
    
    inline std::size_t placeds_size () const { return m_placeds.size (); }

<<<<<<< HEAD
    void new_pos (point t_pos);
=======
    double new_pos (point t_pos);

    void fix_limit();
>>>>>>> fora_area

    void new_type (Type t_new);

    void placement_notice (const Node& node);

    const point& pos () const { return m_pos; }

    void print_geo ();

    void print_edges_geo ();

    bool trespass_neighbor (const Node& t_node, const double limit);

    bool is_neighbor (const Node& t_node) const;

private:
    int m_id = -1;

    point m_pos;

    point m_limit;

    Type m_type = not_placed;

    edges m_anchors;

    edges m_neighbors;

    edges m_placeds;
};

} //namespace