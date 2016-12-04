#include <init/instance/node.hpp>


using namespace sim;

Node::Node (int t_id, std::valarray<double> t_pos, Type t_type) {
    m_id = t_id;
    m_pos = t_pos;
    m_type = t_type;
}

const double& Node::operator[] (std::size_t at) {
    if (at < m_pos.size()) return m_pos[at];
    return 0;
}

void Node::add_edge (Node *b, double dist) {
    if(b->type() == anchor) m_anchors.push_back (Edge (b, dist));
}

const std::vector<Edge>& Node::anchors () {
    return m_anchors;
}

// const auto& Node::neighbors ();

// const auto& Node::placeds ();