#include <iostream>

#include <init/instance/node.hpp>
#include <init/instance/instance.hpp>
#include <init/dao/instance_read.hpp>
#include <init/motion/movement.hpp>

using namespace std;

int main (int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Para usar o sistema passe como parametro o nome da instancia.\nEx: 4.1-1\n";
        return -1;
    }

    sim::Instance_reader reader(argv[argc-1]);
    auto instance = reader.read_instance ();

    auto nodes = instance->nodes ();

    sim::Movement m (nodes[0], 0, 0);
    
    cout << m.m_static << endl;

    while (m.move(false));

    m.release_stress ();
    
    for (auto axiss: nodes[0]->pos()) cout << axiss << " ";
    cout << endl;

    
    return 0;
}