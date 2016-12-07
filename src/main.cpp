#include <iostream>
#include <stdio.h>


#include <init/instance/instance.hpp>
#include <init/dao/instance_da.hpp>
#include <init/system/system.hpp>
#include <init/evaluation/evaluation.hpp>

using namespace std;


int main (int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Para usar o sistema passe como parametro o nome da instancia.\nEx: 4.1-1\n";
        return -1;
    }

    sim::Instance_reader reader(argv[argc-1]);
    auto instance = reader.read_instance ();
    auto real = reader.read_real_instance ();

    sim::System s(*(instance.get()));

    s.solve ();

    sim::Evaluation r (*(instance.get ()), *(real.get ()));

    r.show_erro(true, 0.01);

    printf("[desvMed\t%.10lf\tdesvMax\t%.10lf\tdesvQuad\t%.10lf\trmsd\t%.10lf\tpar\t%.10lf ]\n", r.m_desv_med, r.m_desv_max, r.m_desv_quad, r.m_rmsd, r.m_par);

    reader.print_result_file (*(instance.get ()));

    return 0;
}
    