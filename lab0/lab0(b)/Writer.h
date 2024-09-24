#ifndef WRITER_H
#define WRITER_H

#include <utility>
#include <string>
#include <vector>
#include <optional>

class Writer
{
public:
    std::optional<bool> writeCSV(const std::string& nameFile, const std::vector<std::pair<std::string, int>>& sortWord, int sumWord);
};

#endif
