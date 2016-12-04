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
    Instance_reader(std::string t_instance_name);

    std::unique_ptr<Instance> read_instance ();

    std::unique_ptr<Instance> read_real_instance ();

    void print_result_file ();

private:
    std::string m_instance_name;

    std::string m_loc_file;

    std::string m_rede_file;
};

}