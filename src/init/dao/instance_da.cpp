#include <init/dao/instance_da.hpp>

using namespace sim;

Instance_reader::Instance_reader(std::string t_instance_name) {
    m_instance_name = t_instance_name;

    m_loc_file = "instancias/loc/" + m_instance_name + "_loc.txt";
    m_rede_file = "instancias/rede/" + m_instance_name + "_rede.txt";
}

std::unique_ptr<Instance> Instance_reader::read_instance () {
    std::ifstream arq;
    arq.open (m_loc_file.c_str ());

    int anchors_size, nodes_size, i;
    double start, end, range, noise, size, x, y;

    arq >> start;
    arq >> end;
    arq >> nodes_size;
    arq >> anchors_size;
    arq >> range;
    arq >> noise;

    size = nodes_size + anchors_size;

    std::vector< std::unique_ptr<Node> > nodes;

    std::valarray<double> a;

    for (i = 0; i < anchors_size; ++i) {
        arq >> x >> y;
        a = {x, y};
        nodes.push_back (std::make_unique<Node> (i, a, anchor));
    }

    a = {-1, -1};
    for (; i < size; ++i) 
        nodes.push_back (std::make_unique<Node> (i, a, not_placed));

    int indice, real;
    double dist;
    for(i = 0; i < anchors_size; ++i){
        arq >> indice;
        while(arq >> indice && indice != -1) {
            arq >> dist;
            real = indice + anchors_size;
            nodes[i]->add_edge (dist, *nodes[real]);
            nodes[real]->add_edge (dist, *nodes[i]);
        }
        arq >> indice;
    }

    for(; i < size; ++i){
        arq >> indice;
        while(arq >> indice && indice != -1) {
            arq >> dist;
            real = indice + anchors_size;
            nodes[i]->add_edge (dist, *nodes[real]);
            nodes[real]->add_edge (dist, *nodes[i]);
        }
        arq >> indice;
    }

    std::vector< std::unique_ptr<Node> > commons;
    std::vector< std::unique_ptr<Node> > anchors;
    
    for (i = 0; i < anchors_size; ++i) {
        anchors.push_back (std::move (nodes[i]));
    }

    for (; i < size; ++i) { 
        commons.push_back (std::move (nodes[i]));
    }

    return std::make_unique<Instance>(std::move (commons),
           std::move (anchors), range, noise, start, end);
}

std::unique_ptr<Instance> Instance_reader::read_real_instance () {
    std::ifstream arq;
    arq.open (m_rede_file.c_str ());

    std::vector< std::unique_ptr<Node> > commons;
    std::vector< std::unique_ptr<Node> > anchors;

    int anchors_size, nodes_size, i, id;
    double range, x, y;

    arq >> anchors_size;
    arq >> nodes_size;
    arq >> range;

    int size = nodes_size + anchors_size;

    std::valarray<double> a;

    for (i = 0; i < anchors_size; ++i) {
        arq >> id;
        arq >> x >> y;
        anchors.push_back (std::make_unique<Node> (id, a, anchor));
    }

    for (; i < size; ++i) {
        arq >> id;
        arq >> x >> y;
        a = {x, y};
        commons.push_back (std::make_unique<Node> (id, a, placed));
    }
    return std::make_unique<Instance>(std::move (commons),
           std::move (anchors), range, -1, -1, -1);
}

void Instance_reader::print_result_file () {

}