#pragma once

#include <vector>
#include <utility>

namespace sim {

class Node;

using edge = std::pair<double, Node&>;

using edges = std::vector<edge>;

} //namespace