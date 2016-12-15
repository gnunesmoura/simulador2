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
    else {
        m_placeds.push_back (e);
        m_neighbors.push_back (e);
    }
}

void Node::new_type (Type t_new) {
    if (m_type == t_new || m_type == placed || m_type == anchor) return;
    m_type = t_new;
    if(t_new == placed) {
        for (auto& e : m_neighbors) {
            e.second.placement_notice (*this);
        }
    }
}

/* Melhorar tirando o find_if e passando distancia como parametro */
void Node::placement_notice (const Node & node) {
    auto obj = find_if( m_neighbors.begin (), m_neighbors.end (), 
                       [&](const edge& e) { return e.second == node; });

    if (obj != std::end(m_neighbors))
        m_placeds.push_back (*obj);
}

bool Node::trespass_neighbor (const Node& t_node, const double limit) {
    auto res = std::find_if (m_placeds.begin (), m_placeds.end (), 
                             [&](const edge& e){
                                 return e.second != t_node && limit > e.dist (t_node) &&
                                 (!t_node.is_neighbor (e.second)); 
                             });

    if (res != m_placeds.end ()) return true;

    res = std::find_if (m_anchors.begin (), m_anchors.end (), 
                        [&](const edge& e){
                            return limit > e.dist (t_node) && 
                            (!t_node.is_neighbor (e.second)); 
                        });
    
    if (res != m_anchors.end ()) return true;

    return false;
}

bool Node::is_neighbor (const Node& t_node) const{
    auto res = std::find_if( m_neighbors.begin (), m_neighbors.end (), 
                       [&](const edge& e) { return e.second == t_node; });

    if (res != m_neighbors.end ()) return true;

    res = std::find_if( m_anchors.begin (), m_anchors.end (), 
                       [&](const edge& e) { return e.second == t_node; });
    
    if (res != m_anchors.end ()) return true;

    return false;
}

void Node::print_geo () {
    if(m_type == anchor) {
        printf("A_{%d} = (%.15lf, %.15lf)\n", m_id, m_pos[0], m_pos[1]);
    } else printf("N_{%d} = (%.15lf, %.15lf)\n", m_id, m_pos[0], m_pos[1]);
}

void Node::print_edges_geo () {
    print_geo ();

    for (auto e : m_anchors) {
        int idB = e.second.id (); 
        e.second.print_geo ();
        printf("C_{%d,%d} = Circle[A_{%d}, %.15lf]\n", idB, m_id, idB, e.first);
        printf("L_{%d,%d} = Ray[A_{%d}, N_{%d}]\n", idB, m_id, idB, m_id);
        printf("P_{%d,%d} = Intersect[C_{%d,%d}, L_{%d,%d}]\n", idB, m_id, idB, m_id, idB, m_id);
        printf("F_{%d,%d} = Vector[N_{%d}, P_{%d,%d}]\n", m_id, idB, m_id, idB, m_id);
    }
    for (auto e: m_placeds) {
        int idB = e.second.id ();         
        e.second.print_geo ();        
        printf("C_{%d,%d} = Circle[N_{%d}, %.15lf]\n", idB, m_id, idB, e.first);
        printf("L_{%d,%d} = Ray[N_{%d}, N_{%d}]\n", idB, m_id, idB, m_id);
        printf("P_{%d,%d} = Intersect[C_{%d,%d}, L_{%d,%d}]\n", idB, m_id, idB, m_id, idB, m_id);
        printf("F_{%d,%d} = Vector[N_{%d}, P_{%d,%d}]\n", m_id, idB, m_id, idB, m_id);
    }

    printf("F_{%d} = Vector[ N_{%d}, ", m_id, m_id);
    for (auto e : m_anchors) {
        printf (" F_{%d,%d} +", m_id, e.second.id());
    }
    for (auto e : m_placeds) {
        printf (" F_{%d,%d} +", m_id, e.second.id());
    }
    printf(" N_{%d}] \n\n", m_id);

}