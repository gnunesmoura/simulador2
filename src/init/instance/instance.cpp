#include <init/instance/instance.hpp>

using namespace sim;

Instance::Instance ( std::vector< std::unique_ptr<Node> > t_nodes, std::vector< std::unique_ptr<Node> > t_anchors,
                     double t_radio_range, double t_noise,double t_start, double t_end, std::string t_name) {
    m_nodes = std::move(t_nodes);
    m_anchors = std::move(t_anchors);
    m_radio_range = t_radio_range;
    m_noise = t_noise;
    m_start = t_start;
    m_end = t_end;
    name = t_name;

    set_anchors();
}

void Instance::set_anchors () {
    int size = m_anchors.size();
    double dist;

    for (int i = 0; i < size; ++i) {
        edge nova(0, *m_anchors[i]);
        for(int j = i+1; j < size; j++) {
            dist = nova.dist (*m_anchors[j]);
            m_anchors[i]->add_edge(dist, *m_anchors[j]);
            m_anchors[j]->add_edge(dist, *m_anchors[i]);
        }
    }
}

std::vector<Node*> Instance::nodes () {
    std::vector<Node*> nodes;
    nodes.reserve (m_nodes.size());
    for (auto& node : m_nodes) {
        nodes.push_back (node.get ());
    }
    return nodes;
}