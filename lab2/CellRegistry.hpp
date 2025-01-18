#pragma once

#include "CellFactory.hpp"
#include "ICell.hpp"
#include "CellType.hpp"

extern CellFactory<ICell, CellType> g_cellFactory;
void registerCells();
