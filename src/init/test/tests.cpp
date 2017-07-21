#include "init/test/tests.hpp"

sim::Result run(std::string inst) {
    sim::Instance_reader reader(inst);
    auto instance = reader.read_instance ();
    auto real = reader.read_real_instance ();
    sim::System s(*(instance.get()));
    s.solve_tree ();
    sim::Evaluation r (*(instance.get ()), *(real.get ()));
    reader.print_result_file(*(instance.get()));
    sim::Result res(inst);
    res.add_result(r.m_desv_med, r.m_desv_max, r.m_desv_quad, r.m_rmsd, r.m_par);
    return res;
}

void run_geogebra (std::string inst, double value) {
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
