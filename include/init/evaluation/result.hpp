#pragma once

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <locale>
#include <sstream>
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
        return out /*<< "\tdesvMed\t\tdesvMax\t\tdesvQuad\trmsd\t\tpar\t\tinstancias\n"*/ << r.prefix << "\t" << r.desvMed/r.n  << "\t" << r.desvMax/r.n << "\t" << r.desvQuad/r.n << "\t" << r.rmsd/r.n << "\t" << r.par/r.n << "\t";
    }

    int amount () const { return n; }
    
    std::string prefix; /// Prefix of all tests in the set.

    double desvMed = 0.0;

    double desvMax = 0.0;

    double desvQuad = 0;

    double rmsd = 0;

    double par = 0;

    int n = 0; /// Number of instances in the set.
    
    class WithComma: public std::numpunct<char> // class for decimal numbers using comma instead of point
    {
        protected:
            char do_decimal_point() const { return ','; } // change the decimal separator
    };

};
} // namespace sim
