#include "Model.hpp"
#include "CellRegistry.hpp"  
#include <cstdlib>
#include <ctime>

Model::Model(int width, int height)
    : m_width(width)
    , m_height(height)
{
    static bool once = false;
    if (!once) {
        registerCells();
        once = true;
    }

    m_cells.resize(m_width * m_height);
    m_cellsNext.resize(m_width * m_height);

    for (int i = 0; i < m_width * m_height; ++i) {
        m_cells[i]     = g_cellFactory.Create(CellType::Dead);
        m_cellsNext[i] = g_cellFactory.Create(CellType::Dead);
    }
}

void Model::randomize(double fillProbability)
{
    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < m_width * m_height; ++i) {
        bool alive = ((double)rand()/RAND_MAX) < fillProbability;
        m_cells[i] = g_cellFactory.Create(alive ? CellType::Alive : CellType::Dead);
    }
}

void Model::toggleCell(int x, int y)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) return;

    int index = x + y * m_width;
    bool wasAlive = m_cells[index]->isAlive();
    m_cells[index] = g_cellFactory.Create(wasAlive ? CellType::Dead : CellType::Alive);
}

void Model::update()
{
    for (int x = 0; x < m_width; x++) {
        for (int y = 0; y < m_height; y++) {
            int index = x + y * m_width;
            int neighborSum = 0;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int xi = wrapValue(x + i, m_width);
                    int yj = wrapValue(y + j, m_height);
                    if (m_cells[xi + yj * m_width]->isAlive()) {
                        neighborSum++;
                    }
                }
            }
            if (m_cells[index]->isAlive()) {
                neighborSum--;
            }

            bool currAlive = m_cells[index]->isAlive();
            bool nextAlive = currAlive;

            if (currAlive && (neighborSum < 2 || neighborSum > 3)) {
                nextAlive = false;
            } else if (!currAlive && neighborSum == 3) {
                nextAlive = true;
            }
            
            m_cellsNext[index] = g_cellFactory.Create(nextAlive ? CellType::Alive : CellType::Dead);
        }
    }

    for (int i = 0; i < m_width * m_height; ++i) {
        bool alive = m_cellsNext[i]->isAlive();
        m_cells[i] = g_cellFactory.Create(alive ? CellType::Alive : CellType::Dead);
    }
}

bool Model::isAlive(int x, int y) const
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        return false;
    }
    return m_cells[x + y * m_width]->isAlive();
}

void Model::setAlive(int x, int y, bool alive)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        return;
    }
    m_cells[x + y * m_width] = g_cellFactory.Create(alive ? CellType::Alive : CellType::Dead);
}

int Model::wrapValue(int v, int vMax) const
{
    if (v < 0)     return vMax - 1;
    if (v >= vMax) return 0;
    return v;
}
