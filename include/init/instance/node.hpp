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

    ~Node () {}

    const double& operator[] (std::size_t at);

    int id () { return m_id;    }

    Type type() { return m_type;    }

    void add_edge (Node *b, const double dist);

    const std::vector<Edge>& anchors ();

    // const auto& neighbors ();

    // const auto& placeds ();

private:
    int m_id = -1;

    std::valarray<double> m_pos;

    Type m_type = not_placed;

    std::vector<Edge> m_anchors;

    std::vector<Edge> m_neighbors;

    std::vector<Edge> m_placeds;
};

} //namespace