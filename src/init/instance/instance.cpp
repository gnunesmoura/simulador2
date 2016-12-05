#include <init/instance/instance.hpp>

using namespace sim;

Instance::Instance ( std::vector< std::unique_ptr<Node> > t_nodes, std::vector< std::unique_ptr<Node> > t_anchors,
                     double t_radio_range, double t_noise,double t_start, double t_end ) {
    m_nodes = std::move(t_nodes);
    m_anchors = std::move(t_anchors);
    m_radio_range = t_radio_range;
    m_noise = t_noise;
    m_start = t_start;
    m_end = t_end;
}


std::vector<Node*> Instance::nodes () {
    std::vector<Node*> nodes;
    nodes.reserve (m_nodes.size());
    for (auto& node : m_nodes) {
        nodes.push_back (node.get ()); 
    }
    return nodes;
}