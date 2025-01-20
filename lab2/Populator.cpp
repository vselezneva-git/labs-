#include "Populator.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

Populator::Populator() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Populator::randomize(Model& model, double fillProbability) {
    int width = model.getWidth();
    int height = model.getHeight();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            bool alive = (static_cast<double>(std::rand()) / RAND_MAX) < fillProbability;
            model.setAlive(x, y, alive);
        }
    }
}

bool Populator::loadFromFile(Model& model, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file" << std::endl;
        return false;
    }

    int fileWidth = 0;
    int fileHeight = 0;
    file >> fileWidth >> fileHeight;

    int modeWidth = model.getWidth();
    int modeHeight = model.getHeight();

    if (fileWidth != modeWidth || fileHeight != modeHeight) 
    {
        std::cerr << "The dimensions of the playing field do not match" << std::endl;
        return false;
    }

    for (int y = 0; y < fileHeight; y++)
    {
        std::string line;
        file >> line;

        if (static_cast<int>(line.size()) != fileWidth)
        {
            std::cerr << "incorrect wigth" << std::endl;
            return false;
        }

        for (int x = 0; x < fileWidth; x++)
        {
            char c = line[x];
            if (c == '1')
            {
                model.setAlive(x, y, true);
            }
            else if (c == '0')
            {
                model.setAlive(x, y, false);
            }
            else
            {
                std::cerr << "invalid character" << std::endl;
                return false;
            }
        }
    }
    file.close();
    return true;
}