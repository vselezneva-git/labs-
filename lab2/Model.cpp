#include "Model.hpp"
#include <cstdlib>
#include <ctime>

Model::Model(int width, int height)
    : m_width(width)
    , m_height(height)
{
    m_cells.resize(m_width * m_height);
    m_cellsNext.resize(m_width * m_height);

    for (int i = 0; i < m_width * m_height; ++i) {
        m_cells[i] = CellFactory::createCell(false);
        m_cellsNext[i] = CellFactory::createCell(false);
    }
}


void Model::randomize(double fillProbability)
{
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < m_width * m_height; ++i) {
        bool alive = (static_cast<double>(rand()) / RAND_MAX < fillProbability);
        m_cells[i] = CellFactory::createCell(alive);
    }
}

void Model::toggleCell(int x, int y)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return;

    int index = x + y * m_width;
    bool alive = !m_cells[index]->isAlive();
    m_cells[index] = CellFactory::createCell(alive);
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


            bool currentAlive = m_cells[index]->isAlive();
            bool nextAlive = currentAlive;
            if (currentAlive && (neighborSum < 2 || neighborSum > 3)) {
                nextAlive = false;
            } else if (!currentAlive && neighborSum == 3) {
                nextAlive = true;
            }
            m_cellsNext[index] = CellFactory::createCell(nextAlive);
        }
    }

    for (int i = 0; i < m_width * m_height; ++i) {
        m_cells[i] = CellFactory::createCell(m_cellsNext[i]->isAlive());
    }
}

bool Model::isAlive(int x, int y) const
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return false;
    return m_cells[x + y * m_width]->isAlive();
}

void Model::setAlive(int x, int y, bool alive)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return;
    m_cells[x + y * m_width] = CellFactory::createCell(alive);
}

int Model::wrapValue(int v, int vMax) const
{
    if (v < 0) return vMax - 1;
    if (v >= vMax) return 0;
    return v;
}
