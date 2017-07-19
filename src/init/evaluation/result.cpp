#include "init/evaluation/result.hpp"

using namespace sim;


void Result::add_result (double desvMed_t, double desvMax_t, double desvQuad_t, double rmsd_t, double par_t) {
    desvMed += desvMed_t;
    desvMax += desvMax_t;
    desvQuad += desvQuad_t;
    rmsd += rmsd_t;
    par += par_t;
    
    n++;
}

std::vector<double> Result::result () const {
    std::vector<double> retorno = {desvMed/n, desvMax/n, desvQuad/n, rmsd/n, par/n};
    return retorno;
}

