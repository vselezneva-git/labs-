#pragma once
#include "Model.hpp"
#include <string>

class Populator {
public:
    Populator();

    void randomize(Model& model, double fillProbability);
    bool loadFromFile(Model& model, const std::string& filename);
};