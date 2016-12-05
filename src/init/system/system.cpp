#include <init/system/system.hpp>

using namespace sim;

void System::solve () {
    auto nodes = m_instance.nodes ();

    sort(nodes);

    
}

void System::find_place (Node * t_node);
    
void System::move_until_stop (Movement& t_move);