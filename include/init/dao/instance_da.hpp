#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <valarray>
#include <memory>
#include <init/instance/instance.hpp>
#include <init/instance/node.hpp>

namespace sim {

class Instance_reader {
public:
    Instance_reader(const std::string t_instance_name):
        m_instance_name (t_instance_name), m_loc_file (loc_file ()),
        m_rede_file (rede_file ()), m_result_file (result_file ()) {}

    const std::string m_instance_name;

    const std::string m_loc_file;

    const std::string m_rede_file;

    const std::string m_result_file;

    std::unique_ptr<Instance> read_instance ();

    std::unique_ptr<Instance> read_real_instance ();

    void print_result_file (Instance& t_calc);

    std::string loc_file() const { return "instancias/loc/" + m_instance_name + "_loc.txt"; }
    std::string rede_file() const { return "instancias/rede/" + m_instance_name + "_rede.txt"; }
    std::string result_file() const { return "instancias/result/" + m_instance_name + "_result.txt"; }
};

}