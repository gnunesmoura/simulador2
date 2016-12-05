#include <init/instance/node.hpp>

using namespace sim;

Node::Node (int t_id, point t_pos, Type t_type) {
    m_id = t_id;
    m_pos = t_pos;
    m_type = t_type;
}

bool Node::operator== (const Node& b) const {
    if(m_id == b.id()) return true;
    return false;
}

double Node::operator[] (std::size_t at) const {
    if (at < m_pos.size()) return m_pos[at];
    return 0;
}

bool Node::operator< (const Node& b) const {
    if (this->m_anchors.size() < b.anchors_size()) return true;
    else if (this->m_anchors.size() == anchors_size()) 
        if (this->m_placeds.size() < placeds_size()) return true;
        else if (this->m_placeds.size() == placeds_size())
            if (this->m_neighbors.size() < neighbors_size()) return true;
    return false;
}

void Node::add_edge (double dist, Node& node) {
    edge e(dist, node);
    if(node.type() == anchor) m_anchors.push_back (e);
    else if (node.type() == not_placed) m_neighbors.push_back (e);
    else m_placeds.push_back (e);
}

void Node::new_type (Type t_new) {
    if (m_type == t_new || m_type != not_placed) return;
    m_type = t_new;
    if(t_new == placed) {
        for (auto& e : m_neighbors) {
            e.second.placement_notice (*this);
        }
    }
}

void Node::placement_notice (const Node & node) {
    auto obj = find_if( m_neighbors.begin (), m_neighbors.end (), 
    [&](const edge& e) { return e.second == node; });
    if (obj != std::end(m_neighbors))
        m_placeds.push_back (*obj);
}


void Node::print_geo () {
    if(m_type == anchor) {
        printf("A_{%d} = (%.5lf, %.5lf)\n", m_id, m_pos[0], m_pos[1]);
    } else printf("N_{%d} = (%.5lf, %.5lf)\n", m_id, m_pos[0], m_pos[1]);
}

void Node::print_edges_geo () {
    
}