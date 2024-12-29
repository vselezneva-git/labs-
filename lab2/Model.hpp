#pragma once

#include <vector>
#include <memory>
#include "ICell.hpp"
#include "CellFactory.hpp"

class Model
{
public:
    Model(int width, int height);

    void randomize(double fillProbability);
    void toggleCell(int x, int y);
    void update();

    bool isAlive(int x, int y) const;
    void setAlive(int x, int y, bool alive);

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

private:
    int wrapValue(int v, int vMax) const;
    
    int m_width;
    int m_height;
    std::vector<std::unique_ptr<ICell>> m_cells;
    std::vector<std::unique_ptr<ICell>> m_cellsNext;
};
