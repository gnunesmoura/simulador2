#pragma once

#include <vector>
#include <valarray>
#include <utility>

namespace sim {

class Node;


typedef struct edge {
    constexpr edge (double t_value, Node& t_node) : 
          first(t_value), second(t_node) {};

    double first;
    Node& second;
    inline double dist (const Node& arg0) const;
    constexpr bool operator< (const edge& b) const { return first < b.first; }
}edge;

using edges = std::vector<edge>;

} //namespace