#ifndef READER_H
#define READER_H

#include <fstream>
#include <iostream>
#include <string>
#include <optional>

class Reader
{
private:
    std::ifstream inputFile;

public:
    Reader(const std::string& nameFile);
    std::optional<std::string> getLine();
    void close();
    ~Reader();
};

#endif // READER_H
