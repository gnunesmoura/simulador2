#include <init/system/system.hpp>

using namespace sim;

void System::solve () {
    auto nodes = m_instance.nodes ();

    std::sort (nodes.begin(), nodes.end(), [](const Node *a, const Node* b){
        return *(a) > *(b); 
    });

    for_each (nodes.begin (), nodes.end (), [&](Node * t_node){
        find_place(t_node);
    });

    for (int i = 0; i < 100; i++) {
        for (auto& move: m_moves) {
            if (move.stress ()) move.release_stress ();
            move_until_stop (move, true);
        }
        for_each (nodes.begin (), nodes.end (), [&](Node * t_node){
            if(t_node->type() != placed) find_place(t_node);
        });
    }
}

void System::find_place (Node * t_node) {
    Movement m(t_node, m_instance.radio_range (), m_instance.noise ());
    
    if (t_node->anchors_size () >= 3) 
        move_until_stop (m, false);
    // verificar se é necessario else if
    else if (t_node->anchors_size() + t_node->placeds_size() >= 3)
        move_until_stop (m, true);
    else return;

    if (!m.stress ()) {
        t_node->new_type(placed);
        m_moves.push_back (m);
    } else m.release_stress ();
}
    
void System::move_until_stop (Movement& t_move, bool placed) {
    while (t_move.move (placed));
}