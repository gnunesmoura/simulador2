#pragma once

namespace sim {

class Node;

class Edge {
public:
    Edge (Node *t_node, double t_dist) {  node = t_node; dist = t_dist;   }
    Node *node;
    double dist;
};

} //namespace