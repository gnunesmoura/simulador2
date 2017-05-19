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
    
    for_each (nodes.begin (), nodes.end (), [&](Node * t_node){
        if (t_node->type () != placed) {
            Movement move(t_node, m_instance.radio_range (), m_instance.noise ());
            move_until_stop (move, true);
            if (move.stress ()) {
                move.release_stress ();
                move_until_stop (move, true);
            }
        }
    }); 

    bool move;
    do {
        move = false;

    } while (move);   
}

inline void System::find_place (Node * t_node) {
    Movement m(t_node, m_instance.radio_range (), m_instance.noise ());
    
    // if (t_node->anchors_size () >= 3) 
        move_until_stop (m, false);
    // verificar se é necessario else if
    // else if (t_node->anchors_size() + t_node->placeds_size() >= 3)
        move_until_stop (m, true);
    // else return;

    if (!m.stress ()) {
        t_node->new_type(placed);
        m_moves.push_back (m);
    } else {
        t_node->new_type(not_placed);
        m.release_stress ();
        while (m.stress()){
            m.increment_acceptable ();
            move_until_stop (m, true);
        }
        t_node->new_type(placed);
        m_moves.push_back (m);
    }
}



inline void System::move_until_stop (Movement& t_move, bool placed) {
    while (t_move.move (placed));
}


void System::solve_tree () {
    auto nodes = m_instance.nodes ();
    std::vector<Node*> queue;
    queue.reserve(nodes.size());
    std::for_each (nodes.begin (), nodes.end (), [&](Node * t_node){
        if (t_node->anchors_size() >= 3) {
            queue.push_back(t_node);
            std::cout << t_node->id() << "\n";
        }
    });

    int i = 0;
    while (i != queue.size()) {
        find_place(queue[i]);
        auto neighbors = queue[i]->neighbors();
        std::for_each (neighbors.begin (), neighbors.end (), [&](edge t_edge){
            if(t_edge.second.type() == not_placed && t_edge.second.placeds_size() + t_edge.second.anchors_size() >= 3){
                t_edge.second.new_type(queued);
                queue.push_back(&(t_edge.second));
                std::cout << t_edge.second.id() << "\n";
            }
        });
        for (auto& move: m_moves) {
            move_until_stop (move, true);
        }
        i++;
    }

    bool moved;
    do {
        moved = false;
        for(auto n: nodes) {
            if(n->type() != placed){
                find_place(n);
                moved = true;
            }
        }
    } while (moved);

    for(auto& m:  m_moves) {
        move_until_stop(m, true);
    }
}

void System::solve_test () {
    // auto nodes = m_instance.nodes ();
    
    // Node* node = nodes[0];

    // node->new_pos ({0,0});

    // Movement m(node, m_instance.radio_range (), m_instance.noise ());

    // move_until_stop(m, true);

    // if(m.stress ()) std::cout << "Ta puto\n";

    // m.release_stress ();

    // move_until_stop

    // node->print_edges_geo ();    
}