#pragma once

#include <vector>
#include <valarray>
#include <utility>

namespace sim {

class Node;

using edge = std::pair<double, Node&>;

using edges = std::vector<edge>;

const double dist (const Node& arg0, const Node& arg1) {
    std::valarray<double> vec (arq1.pos () - arg0.pos ());
    vec = std::pow(vec, 2.0);
    double sqr_sum = vec.sum ();

    if(sqr_sum > 0) std::sqrt(sqr_sum);
    return 0;
}

} //namespace