#include "Writer.h"
#include <fstream>
#include <iostream>
#include <iomanip>

std::optional<bool> Writer::writeCSV(const std::string& nameFile, const std::vector<std::pair<std::string, int>>& sortWord, int sumWord)
{
    std::ofstream outputFile(nameFile);

    if(!outputFile.is_open())
    {
        std::cerr << "Ошибка записи в файл" << "\n";
        return std::nullopt;
    }

    outputFile << "Слово Частота Частота(%)" << "\n";

    for(const auto& pair : sortWord)
    {
        double freqInPercent = static_cast<double>(pair.second) / sumWord * 100;
        outputFile << pair.first << "   " << pair.second << "   " << freqInPercent << "%" << "\n";
    }

    outputFile.close();
    return true;
}