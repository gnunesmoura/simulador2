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

bool Node::operator< (Node& b) const {
    if (this->m_anchors.size() < b.anchors_size()) return true;
    else if (this->m_anchors.size() == anchors_size()) 
        if (this->m_placeds.size() < placeds_size()) return true;
        else if (this->m_placeds.size() == placeds_size())
            if (this->m_neighbors.size() < neighbors_size()) return true;
    return false;
}

void Node::add_edge (Node *b, double dist) {
    if(b->type() == anchor) m_anchors.push_back (Edge (b, dist));
    else if (b->type() == not_placed) m_neighbors.push_back (Edge (b, dist));
    else m_placeds.push_back (Edge (b, dist));
}
