#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

namespace sim {

/**
 * Class that represents the avarenge result of a set of tests.
 */
class Result {
  public:
    /**
     * Creates an empty result for the set.
     */
    Result(std::string prefix_t) : prefix(prefix_t) {};

    void add_result(double desvMed_t, double desvMax_t, double desvQuad_t, double rmsd_t, double par_t);

    std::vector<double> result () const;

    Result& operator+= (const Result& rhs){
        desvMed += rhs.desvMed;
        desvMax += rhs.desvMax;
        desvQuad += rhs.desvQuad;
        rmsd += rhs.rmsd;
        par += rhs.par;

        n += rhs.n;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Result& r){
        return out << r.prefix << "\t[desvMed " << r.desvMed/r.n << " desvMax " << r.desvMax/r.n << " desvQuad " << r.desvQuad/r.n << " rmsd " << r.rmsd/r.n << " par " << r.par/r.n << " instances " << r.n << "]\n\n";
    }

    int amount () const { return n; }
    
    std::string prefix; /// Prefix of all tests in the set.

    double desvMed = 0;

    double desvMax = 0;

    double desvQuad = 0;

    double rmsd = 0;

    double par = 0;

    int n = 0; /// Number of instances in the set.
};
} // namespace sim
