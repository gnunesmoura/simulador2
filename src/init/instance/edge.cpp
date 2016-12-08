#include <init/instance/edge.hpp>
#include <init/instance/node.hpp>

using namespace sim;

double edge::dist (const Node& arg0) const {
    if (arg0 == second) return 0;

    std::valarray<double> vec (second.pos () - arg0.pos ());
    vec = std::pow(vec, 2.0);
    double sqr_sum = vec.sum ();

    if(sqr_sum == 0) return 0;
    return std::sqrt(sqr_sum);
}