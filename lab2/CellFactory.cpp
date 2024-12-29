#include "CellFactory.hpp"
#include "LiveCell.hpp"
#include "DeadCell.hpp"

std::unique_ptr<ICell> CellFactory::createCell(bool alive)
{
    if (alive) {
        return std::make_unique<LiveCell>();
    } else {
        return std::make_unique<DeadCell>();
    }
}
