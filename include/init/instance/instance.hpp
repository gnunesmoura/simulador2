#pragma once

#include <vector>
#include <init/instance/node.hpp>

namespace sim {

class Instance {
public:
    Instance ( std::vector<Node*> t_nodes, std::vector<Node*> t_anchors,
               double t_radio_range, double t_noise,double t_start, double t_end );

    Instance () {}

    ~Instance () {}

    const double radio_range () { return m_radio_range; }

    const double noise () { return m_noise; }

    const double start () { return m_start; }

    const double end () { return m_end; }

    std::vector<Node*> nodes ();
    
private:
    std::vector<Node*> m_nodes;

    std::vector<Node*> m_anchors;
    
    double m_radio_range = 0;

    double m_noise = 0;

    double m_start = 0;

    double m_end = 0;
};

} //namespace