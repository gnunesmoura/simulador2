#pragma once

#include <iostream>
#include <stdio.h>
#include <valarray>
#include <algorithm>

#include <init/instance/instance.hpp>
#include <init/instance/node.hpp>

namespace sim {

using vector = std::valarray<double>;

class Evaluation {
public:
    Evaluation (Instance& t_calc, Instance& t_real);

    void show_erro (bool geo, double acceptable_erro);

    double m_desv_max = 0;

    double m_desv_med = 0;

    double m_desv_quad = 0;

    double m_rmsd = 0;

    double m_par = 0;

private:
    void calculate (Instance& t_calc, Instance& t_real);

    inline double norm (Node* a, Node* b);

    Instance& m_calc;
    
    Instance& m_real;
    
};

} //namespace