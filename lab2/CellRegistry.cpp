#include "CellRegistry.hpp"
#include "LiveCell.hpp"
#include "DeadCell.hpp"

CellFactory<ICell, CellType> g_cellFactory;

void registerCells()
{
    g_cellFactory.Register(
        CellType::Alive,
        []() -> std::unique_ptr<ICell> {
            return std::make_unique<LiveCell>();
        }
    );

    g_cellFactory.Register(
        CellType::Dead,
        []() -> std::unique_ptr<ICell> {
            return std::make_unique<DeadCell>();
        }
    );
}
