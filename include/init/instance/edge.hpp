#pragma once

#include <vector>
#include <valarray>
#include <utility>

namespace sim {

class Node;

using edge = std::pair<double, Node&>;

using edges = std::vector<edge>;

const double dist (const Node& arg0, const Node& arg1);

} //namespace