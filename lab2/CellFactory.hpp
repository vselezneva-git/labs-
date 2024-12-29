#pragma once
#include <memory>
#include "ICell.hpp"

class CellFactory
{
public:
    static std::unique_ptr<ICell> createCell(bool alive);
};
