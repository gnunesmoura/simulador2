#pragma once

#include <iostream>
#include <stdio.h>
#include <string>

#include <init/instance/instance.hpp>
#include <init/dao/instance_da.hpp>
#include <init/system/system.hpp>
#include "init/evaluation/evaluation.hpp"
#include "init/evaluation/result.hpp"

sim::Result run(std::string inst);

void run_geogebra (std::string inst, double value);
