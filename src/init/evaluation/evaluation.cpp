#include <init/evaluation/evaluation.hpp>

using namespace sim;

Evaluation::Evaluation (Instance& t_calc, Instance& t_real) : 
                        m_calc(t_calc), m_real(t_real) {
    calculate(t_calc, t_real);
}

void Evaluation::calculate (Instance& t_calc, Instance& t_real) {
    double desv_total = 0, erro, desv_ar = 0, range_quad, erro_quad = 0;
    
    range_quad = t_calc.radio_range ();
    range_quad *= range_quad;

    auto calc = t_calc.nodes ();
    auto real = t_real.nodes ();

    for (int i = 0; i < calc.size (); ++i) {
        erro = norm (calc[i], real[i]);
        desv_total += erro;
        erro_quad = erro * erro;
        m_desv_quad += erro_quad;
        desv_ar += (erro_quad/range_quad);
        if (erro > m_desv_max) m_desv_max = erro;
    }

    m_rmsd = std::sqrt (m_desv_quad/calc.size ());
    m_desv_med = desv_total/calc.size ();
    m_par = (desv_ar/calc.size ())*100;
}

inline double Evaluation::norm (Node* a, Node* b) {
    vector dist = a->pos () - b->pos ();
    dist = std::pow (dist, 2.0);
    double sqr_sum = dist.sum ();

    if(sqr_sum == 0) return 0;
    return std::sqrt (sqr_sum);
}

void Evaluation::show_erro (bool geo, double acceptable_erro) {
    auto re = m_real.nodes ();
    auto calc = m_calc.nodes ();

    int nNodes = calc.size (), cont = 0; 
    std::cout << "\n\n";
    if (!geo) std::cout << "|id\t|tipo\t|Anchor\t|Placed\t|erro\t\t|\n";
    for (int i = 0; i < nNodes; ++i) {
        // std::cout << norm(calc[i], re[i]) << "\n";
        if(norm(calc[i], re[i]) > acceptable_erro) {
            if (!geo) printf("|%d\t|%d\t|%d\t|%d\t|%.10lf\n\n|", calc[i]->id (), calc[i]->type (), calc[i]->anchors_size (), norm(calc[i], re[i]));
            else calc[i]->print_edges_geo ();
            cont ++;
        }
    }
   std::cout << "Nos errados " << cont << "\n";
}