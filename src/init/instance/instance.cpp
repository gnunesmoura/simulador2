#include <init/instance/intance.hpp>

Instance ( std::vector<Node*> t_nodes, std::vector<Node*> t_anchors,
           double t_radio_range, double t_noise,double t_start, double t_end ) {
    m_nodes = t_nodes;
    m_anchors = t_anchors;
    m_radio_range = t_radio_range;
    m_noise = t_noise;
    m_start = t_start;
    m_end = t_end;
}