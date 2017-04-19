#pragma once

#include <iostream>
#include <stdio.h>
#include <string>

#include <init/instance/instance.hpp>
#include <init/dao/instance_da.hpp>
#include <init/system/system.hpp>
#include "init/evaluation/evaluation.hpp"
#include "init/evaluation/result.hpp"

sim::Result run(std::string inst) {
    sim::Instance_reader reader(inst);
    auto instance = reader.read_instance ();
    auto real = reader.read_real_instance ();

    sim::System s(*(instance.get()));

    s.solve_tree ();

    sim::Evaluation r (*(instance.get ()), *(real.get ()));


    sim::Result res(inst);
    res.add_result(r.m_desv_med, r.m_desv_max, r.m_desv_quad, r.m_rmsd, r.m_par);
    // std::cout << res;
    return res;
}

void run_geogebra (std::string inst, double value) {
    std::cout << '\n' << inst << '\n';    
    sim::Instance_reader reader(inst);
    auto instance = reader.read_instance ();
    auto real = reader.read_real_instance ();

    sim::System s(*(instance.get()));

    s.solve_tree ();

    sim::Evaluation r (*(instance.get ()), *(real.get ()));
    auto nodes = instance->nodes ();

    r.show_erro(true, value);

    std::cout << '\n';
    std::cout << "[desvMed " << r.m_desv_med << " desvMax " << r.m_desv_max << " desvQuad " << r.m_desv_quad << " rmsd " << r.m_rmsd << " par " << r.m_par << "]\n";

}

std::string Oie () {
    return "oie\n";
}

    // sim::Instance_reader reader(argv[1]);
    // auto instance = reader.read_instance ();
    // auto real = reader.read_real_instance ();

    // sim::System s(*(instance.get()));

    // s.solve_tree ();

    // sim::Evaluation r (*(instance.get ()), *(real.get ()));
    // auto nodes = instance->nodes ();

    // r.show_erro(true, 0.01);

    // cout << '\n';
    // cout << "[desvMed " << r.m_desv_med << " desvMax " << r.m_desv_max << " desvQuad " << r.m_desv_quad << " rmsd " << r.m_rmsd << " par " << r.m_par << "]\n";

    // // reader.print_result_file (*instance);
    
    // // if (argc > 2) {
    // //     string show("python3 instancias/exibe_redes_comparacao.py ");
    // //     show +=  reader.m_result_file + " " + reader.m_rede_file;
    // //     system(show.c_str ());
    // // }
    
